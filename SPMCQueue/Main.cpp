#include "SPMCQueue.h"

#include <catch2/catch_test_macros.hpp>
#include <thread>

template <typename QueueType>
void WriteString(QueueType& queue, const std::string& msg)
{
    queue.Write(msg.data(), static_cast<MessageSize>(msg.size()));
}

template <typename QueueType>
std::string ReadString(const QueueType& queue, uint64_t index)
{
    char buffer[1024] = {0};
    size_t bufferSize = 0;
    return queue.Read(index, buffer, bufferSize) ? std::string(buffer, bufferSize) : std::string();
}

TEST_CASE("SPMCQueue basic write and read", "[SPMCQueue]") {
    SPMCQueue<4> queue;

    WriteString(queue, "Hello");
    REQUIRE(ReadString(queue, 0) == "Hello");
}

TEST_CASE("SPMCQueue supports multicast read", "[SPMCQueue]") {
    SPMCQueue<4> queue;

    WriteString(queue, "World");

    std::string c1 = ReadString(queue, 0);
    std::string c2 = ReadString(queue, 0);
    std::string c3 = ReadString(queue, 0);

    REQUIRE(c1 == "World");
    REQUIRE(c2 == "World");
    REQUIRE(c3 == "World");
}

TEST_CASE("SPMCQueue overwrites old entries", "[SPMCQueue]") {
    constexpr size_t QueueSize = 4;
    SPMCQueue<QueueSize> queue;

    for(int i = 0; i < QueueSize + 2; ++i)
    {
        WriteString(queue, "Msg" + std::to_string(i));
        REQUIRE(ReadString(queue, i) == "Msg" + std::to_string(i));
    }
}

TEST_CASE("SPMCQueue concurrent readers", "[SPMCQueue]")
{
    SPMCQueue<1> queue;
    WriteString(queue, "Concurrent");

    std::atomic<int> successCount = 0;

    auto reader = [&]()
    {
        if(ReadString(queue, 0) == "Concurrent")
        {
            ++successCount;
        }
    };

    std::vector<std::thread> threads;
    for(int i = 0; i < 10; ++i)
    {
        threads.emplace_back(reader);
    }

    for(auto& t : threads)
    {
        t.join();
    }

    REQUIRE(successCount == 10);
}