#include "my_allocator.h"
#include <gtest/gtest.h>
#include <map>

using element_type = std::pair<const int, int>;
using allocator_type = my_allocator::MyAllocator<element_type>;

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
    EXPECT_NO_THROW((std::map<int, int, std::less<int>, allocator_type>{allocator_type(100U)}));
}

TEST(MyAllocatorTest, AddElementToTheMapWithCustomAllocator)
{
    std::map<int, int, std::less<int>, allocator_type> my_map{allocator_type(1U)};
    EXPECT_NO_THROW(my_map.emplace(std::pair<int, int>(0, 0)));
}

TEST(MyAllocatorTest, AddTenElementsToTheMapWithCustomAllocator)
{
    std::map<int, int, std::less<int>, allocator_type> my_map{allocator_type(10U)};
    for(auto i{0U}; i < 10U; ++i)
    {
        EXPECT_NO_THROW(my_map.emplace(std::pair<int, int>(i, factorial(i))));
    }
}

TEST(MyAllocatorTest, AddElementsToTheMapWithCustomAllocatorAndThenAccessThem)
{
    std::map<int, int, std::less<int>, allocator_type> my_map{allocator_type(10U)};
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

TEST(MyAllocatorTest, AllocateZeroElementsTryAddElementToTheMapWithCustomAllocator_ExpectThrow)
{
    std::map<int, int, std::less<int>, allocator_type> my_map{allocator_type(0U)};
    for(auto i{0U}; i < 1U; ++i)
    {
        EXPECT_THROW(my_map.emplace(std::pair<int, int>(i, factorial(i))), std::bad_alloc);
    }
}
