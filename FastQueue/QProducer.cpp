#include "QProducer.h"

void QProducer::Write(std::span<std::byte> buffer)
{
    const int32_t payloadSize = sizeof(int32_t) + buffer.size();
    m_localCounter += payloadSize;

    mQ->m_writeCounter.store(m_localCounter, std::memory_order_release);

    std::memcpy(m_nextElement, &payloadSize, sizeof(int32_t));
    std::memcpy(m_nextElement + sizeof(int32_t), buffer.data(), buffer.size());

    mQ->m_readCounter.store(m_localCounter, std::memory_order_release);

    m_nextElement += payloadSize;
}