#include <atomic>

using BlockSize = uint32_t;
using MessageSize = uint32_t;

struct alignas(64) Block 
{
    std::atomic<BlockSize> version{0};
    std::atomic<MessageSize> size{0};
    uint8_t data[];
};

struct Header 
{
    alignas(64) std::atomic<uint64_t> blockCounter{0};
    alignas(64) Block blocks[];
};

template <size_t QueueSize>
class SPMCQueue {
public:
    SPMCQueue()
    {
        m_blocks = reinterpret_cast<Block*>(malloc(QueueSize * (sizeof(Block) + 1024)));

        for (size_t i = 0; i < QueueSize; ++i)
        {
            Block* block = GetBlock(i);
            block->version.store(0, std::memory_order_relaxed);
        }
    }

    ~SPMCQueue()
    {
        std::free(m_blocks);
    }

    void Write(const void* data, MessageSize size)
    {
        Block* block = GetBlock(m_blockCounter % QueueSize);
        block->version.fetch_add(1, std::memory_order_relaxed);

        block->size.store(size, std::memory_order_relaxed);
        std::memcpy(block->data, data, size);

        block->version.fetch_add(1, std::memory_order_release);
        ++m_blockCounter;
    }

    bool Read(uint64_t index, void* outBuffer, size_t& outSize) const
    {
        Block* block = GetBlock(index % QueueSize);

        const uint64_t currentVersion = block->version.load(std::memory_order_acquire);
        if((currentVersion & 1) != 0)
        {
            return 0;
        }
        
        MessageSize size = block->size.load(std::memory_order_relaxed);
        std::memcpy(outBuffer, block->data, size);
        outSize = size;

        return currentVersion == block->version.load(std::memory_order_acquire);
    }

private:
    Block* GetBlock(size_t i) const
    {
        return reinterpret_cast<Block*>(reinterpret_cast<uint8_t*>(m_blocks) + i * (sizeof(Block) + 1024));
    }

    Block* m_blocks = nullptr;
    std::atomic<uint64_t> m_blockCounter = 0;
};