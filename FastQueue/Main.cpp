#include "QConsumer.h"
#include "QProducer.h"
#include <iostream>

int main()
{
    void* raw = std::aligned_alloc(CACHE_LINE_SIZE, sizeof(FastQueue) + QUEUE_BUFFER_SIZE);
    auto* queue = new (raw) FastQueue;
    queue->m_readCounter = 0;
    queue->m_writeCounter = 0;

    QProducer producer{0, queue->m_buffer, queue};
    QConsumer consumer1{0, queue->m_buffer, queue};
    QConsumer consumer2{0, queue->m_buffer, queue};

    std::vector<std::string> messages = { "Hello", "from", "FastQueue", "broadcast!" };
    for(const auto& msg : messages)
    {
        std::vector<std::byte> data(msg.size());
        std::memcpy(data.data(), msg.data(), msg.size());
        producer.Write(std::span<std::byte>(data.data(), data.size()));
    }

    auto consume = [](QConsumer& c, const std::string& name)
    {
        std::vector<std::byte> buffer(256);
        while(true)
        {
            int size = c.TryRead(std::span<std::byte>(buffer.data(), buffer.size()));
            if (size <= 0) break;

            std::string msg(reinterpret_cast<char*>(buffer.data()), size);
            std::cout << name << " read: " << msg << "\n";
        }
    };

    consume(consumer1, "[Consumer1]");
    consume(consumer2, "[Consumer2]");

    std::free(raw);
    return 0;
}