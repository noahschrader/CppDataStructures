#include <vector>
#include <boost/container/static_vector.hpp>

template <class T, size_t ChunkSize>
struct StableVector
{
    static_assert(ChunkSize % 2 == 0, "ChunkSize needs to be a multiplier of 2");

    void push_back(const T& t)
    {
        if(m_chunks.empty() || m_chunks.back()->size() == ChunkSize)
        {
            m_chunks.push_back(std::make_unique<Chunk>());
        }
        ++m_size;
        m_chunks.back()->push_back(t);
    }

    T& operator[](size_t i)
    {
        return (*m_chunks[i / ChunkSize])[i % ChunkSize];
    }

    size_t size()
    {
        return m_size;
    }

    using Chunk = boost::container::static_vector<T, ChunkSize>;
    std::vector<std::unique_ptr<Chunk>> m_chunks;
    size_t m_size = 0;
};