#include "my_allocator.h"
#include <gtest/gtest.h>
#include <map>
#include <vector>

using element_type = std::pair<const int, int>;

template <std::size_t N>
using allocator_type = my_allocator::MyAllocator<element_type, N>;

namespace
{
unsigned int factorial(unsigned int n)
{
    unsigned int result{1U};
    for(auto i{1U}; i <= n; ++i)
    {
        result *= i;
    }
        
    return result;
}
}

TEST(MyAllocatorTest, ConstructMapUsingCustomAllocator)
{
    const auto elements_count{100U};
    EXPECT_NO_THROW((std::map<int, int, std::less<int>, allocator_type<elements_count>>{}));
}

TEST(MyAllocatorTest, AddElementToTheMapWithCustomAllocator)
{
    std::map<int, int, std::less<int>, allocator_type<1U>> my_map{};
    EXPECT_NO_THROW(my_map.emplace(std::pair<int, int>(0, 0)));
}

TEST(MyAllocatorTest, AddTenElementsToTheMapWithCustomAllocator)
{
    std::map<int, int, std::less<int>, allocator_type<10U>> my_map{};
    for(auto i{0U}; i < 10U; ++i)
    {
        EXPECT_NO_THROW(my_map.emplace(std::pair<int, int>(i, factorial(i))));
    }
}

TEST(MyAllocatorTest, AddElementsToTheMapWithCustomAllocatorAndThenAccessThem)
{
    std::map<int, int, std::less<int>, allocator_type<10U>> my_map{};
    for(auto i{0U}; i < 10U; ++i)
    {
        EXPECT_NO_THROW(my_map.emplace(std::pair<int, int>(i, factorial(i))));
    }

    for(auto i{0U}; i < 10U; ++i)
    {
        EXPECT_NO_THROW(my_map[i]);
        EXPECT_EQ(my_map[i], factorial(i));
    }
}

TEST(MyAllocatorTest, AllocateOneElementTryAddTwoElementsToTheMapWithCustomAllocator_ExpectThrowWhenAddingSecondElement)
{
    std::map<int, int, std::less<int>, allocator_type<1U>> my_map{};
    my_map.emplace(std::pair<int, int>(0, 0));
    EXPECT_THROW(my_map.emplace(std::pair<int, int>(0, 0)), std::bad_alloc);
}
