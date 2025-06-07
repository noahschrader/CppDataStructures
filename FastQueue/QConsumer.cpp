#include "QConsumer.h"

int32_t QConsumer::TryRead(std::span<std::byte> buffer)
{
    if(m_localCounter == mQ->m_readCounter.load(std::memory_order_acquire))
    {
        return 0;
    }

    int32_t payloadSize;
    std::memcpy(&payloadSize, m_nextElement, sizeof(int32_t));

    int32_t writeCounter = mQ->m_writeCounter.load(std::memory_order_acquire);
    if(payloadSize > buffer.size())
    {
        return 0;
    }
    if(writeCounter - m_localCounter > QUEUE_BUFFER_SIZE)
    {
        return 0;
    }

    std::memcpy(buffer.data(), m_nextElement + sizeof(payloadSize), payloadSize);

    const int32_t readSize = sizeof(payloadSize) + payloadSize;
    m_localCounter += readSize;
    m_nextElement += payloadSize;

    writeCounter = mQ->m_writeCounter.load(std::memory_order_acquire);
    if(writeCounter - m_localCounter > QUEUE_BUFFER_SIZE) {
        return 0;
    }

    return readSize;
};