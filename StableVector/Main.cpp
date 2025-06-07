#include "StableVector.h"

#include <list>
#include <benchmark/benchmark.h>

int Sum(StableVector<int, 4 * 4096>& sv)
{
    int sum = 0;
    for(size_t i = 0; i < sv.size(); ++i)
    {
        sum += sv[i];
    }
    return sum;
}

int Sum(std::unordered_map<int, int>& um)
{
    int sum = 0;
    for(const auto& [k, v] : um)
    {
        sum += v;
    }
    return sum;
}

static void BM_StableVector(benchmark::State& state)
{
    StableVector<int, 4 * 4096> sv;
    std::list<int> l;
    for(int i = 0; i < 100000; ++i)
    {
        for(int j = 0; j < 1000; ++j)
        {
            l.push_back(j);
        }
        sv.push_back(i);
    }
    for (auto _ : state)
    {
     int sum = Sum(sv);
        benchmark::DoNotOptimize(sum);
    }
}

static void BM_UnorderedMap(benchmark::State& state)
{
    std::unordered_map<int, int> um;
    std::list<int> l;
    for(int i = 0; i < 100000; ++i)
    {
        for(int j = 0; j < 1000; ++j)
        {
            l.push_back(j);
        }
        um.emplace(i, i);
    }

    for (auto _ : state)
    {
        int sum = Sum(um);
        benchmark::DoNotOptimize(sum);
    }
}

BENCHMARK(BM_StableVector);
BENCHMARK(BM_UnorderedMap);
BENCHMARK_MAIN();