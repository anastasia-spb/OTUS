#include "my_allocator.h"
#include <gtest/gtest.h>
#include <map>

TEST(MyAllocatorTest, ConstructMapUsingCustomAllocator)
{
    EXPECT_NO_THROW((std::map<int, int, std::less<int>, my_allocator::MyAllocator<std::pair<const int,int>>>{}));
}

TEST(MyAllocatorTest, AddElementToTheMapWithCustomAllocator)
{
    std::map<int, int, std::less<int>, my_allocator::MyAllocator<std::pair<const int,int>>> my_map{};
    EXPECT_NO_THROW(my_map.insert(std::pair<int, int>(0, 0)));
}

TEST(MyAllocatorTest, AddTenElementsToTheMapWithCustomAllocator)
{
    std::map<int, int, std::less<int>, my_allocator::MyAllocator<std::pair<const int,int>>> my_map{};
    for(auto i{0}; i < 10; ++i)
    {
        EXPECT_NO_THROW(my_map.insert(std::pair<int, int>(i, i)));
    }
}