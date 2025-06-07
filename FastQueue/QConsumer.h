#include "FastQueue.h"
#include <span>

struct QConsumer
{
    int32_t TryRead(std::span<std::byte> buffer);

    uint64_t m_localCounter{0};
    uint8_t* m_nextElement;
    FastQueue* mQ;
};