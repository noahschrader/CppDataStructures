#include "SmallVector/SmallVector.h"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Empty", "[SmallVector]")
{
    Constructable::Reset();
    SmallVector<Constructable> sv;
    REQUIRE(sv.size() == 0);
    REQUIRE(sv.capacity() == 1);
    REQUIRE(Constructable::GetConstructorCalls() == 0);
    REQUIRE(Constructable::GetDestructorCalls() == 0);
}

TEST_CASE("PushPop", "[SmallVector]")
{
    Constructable::Reset();
    SmallVector<Constructable, 3> sv;

    REQUIRE(sv.capacity() == 3);

    sv.push_back(Constructable(1));
    REQUIRE(sv.size() == 1);
    REQUIRE(sv[sv.size() - 1].GetValue() == 1);

    sv.push_back(Constructable(2));
    REQUIRE(sv.size() == 2);
    REQUIRE(sv[sv.size() - 1].GetValue() == 2);

    sv.push_back(Constructable(3));
    REQUIRE(sv.size() == 3);
    REQUIRE(sv[sv.size() - 1].GetValue() == 3);

    for(size_t i = 0; i < sv.size(); ++i) 
    {
        REQUIRE(sv[i].GetValue() == i + 1);
    }

    sv.pop_back();
    REQUIRE(sv.size() == 2);
    for(size_t i = 0; i < sv.size(); ++i) 
    {
        REQUIRE(sv[i].GetValue() == i + 1);
    }

    sv.pop_back();
    REQUIRE(sv.size() == 1);

    sv.pop_back();
    REQUIRE(sv.size() == 0);

    REQUIRE(Constructable::GetConstructorCalls() == 6);
    REQUIRE(Constructable::GetDestructorCalls() == 6);
}

TEST_CASE("PushPopWithGrow", "[SmallVector]")
{
    Constructable::Reset();
    SmallVector<Constructable, 2> sv;

    REQUIRE(sv.capacity() == 2);

    sv.push_back(Constructable(1));
    REQUIRE(sv.size() == 1);
    REQUIRE(sv[sv.size() - 1].GetValue() == 1);

    sv.push_back(Constructable(2));
    REQUIRE(sv.size() == 2);
    REQUIRE(sv[sv.size() - 1].GetValue() == 2);

    sv.push_back(Constructable(3));
    REQUIRE(sv.size() == 3);
    REQUIRE(sv[sv.size() - 1].GetValue() == 3);

    for(size_t i = 0; i < sv.size(); ++i) 
    {
        REQUIRE(sv[i].GetValue() == i + 1);
    }

    sv.pop_back();
    REQUIRE(sv.size() == 2);
    for(size_t i = 0; i < sv.size(); ++i) 
    {
        REQUIRE(sv[i].GetValue() == i + 1);
    }

    sv.pop_back();
    REQUIRE(sv.size() == 1);

    sv.pop_back();
    REQUIRE(sv.size() == 0);

    REQUIRE(Constructable::GetConstructorCalls() == 8);
    REQUIRE(Constructable::GetDestructorCalls() == 8);
}

TEST_CASE("DirectArrayAccess", "[SmallVector]")
{
    Constructable::Reset();
    SmallVector<Constructable, 4> sv;
    REQUIRE(sv.capacity() == 4);
    REQUIRE(Constructable::GetConstructorCalls() == 0);
    sv.push_back(Constructable(1));
    sv.push_back(Constructable(2));
    sv.push_back(Constructable(3));
    sv.push_back(Constructable(4));
    REQUIRE(sv.size() == 4);
    REQUIRE(Constructable::GetConstructorCalls() == 8);
    for(size_t i = 0; i < sv.size(); ++i) 
    {
        REQUIRE(sv[i].GetValue() == i + 1);
    }
}