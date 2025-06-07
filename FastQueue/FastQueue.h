#pragma once
#include <atomic>

constexpr size_t CACHE_LINE_SIZE = 64;
constexpr size_t QUEUE_BUFFER_SIZE = 1024 * 1024;

struct FastQueue
{
    alignas(CACHE_LINE_SIZE) std::atomic<uint64_t> m_readCounter;
    alignas(CACHE_LINE_SIZE) std::atomic<uint64_t> m_writeCounter;
    alignas(CACHE_LINE_SIZE) uint8_t m_buffer[0];
};