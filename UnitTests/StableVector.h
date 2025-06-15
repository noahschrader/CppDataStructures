#include "StableVector/StableVector.h"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Empty", "[StableVector]")
{
    StableVector<int, 2> sv;
    REQUIRE(sv.size() == 0);
    REQUIRE(sv.m_chunks.empty());
}

TEST_CASE("ChunkGrow", "[StableVector]")
{
    constexpr size_t ChunkSize = 4;
    StableVector<Constructable, ChunkSize> sv;

    for(int i = 0; i < ChunkSize * 3; ++i) 
    {
        sv.push_back(Constructable(i));
    }

    REQUIRE(sv.size() == ChunkSize * 3);

    for(int i = 0; i < ChunkSize * 3; ++i)
    {
        REQUIRE(sv[i].GetValue() == i);
    }
}

TEST_CASE("StableReferencesWithGrow", "[StableVector]")
{
    StableVector<Constructable, 2> sv;

    sv.push_back(Constructable(1));
    auto reference = &sv[0];

    sv.push_back(Constructable(2));
    sv.push_back(Constructable(3));

    REQUIRE(reference == &sv[0]);
    REQUIRE(sv[0].GetValue() == 1);

    for(int i = 3; i < 12; ++i)
    {
        sv.push_back(Constructable(i));
    }

    REQUIRE(reference == &sv[0]);
    REQUIRE(sv[0].GetValue() == 1);
}