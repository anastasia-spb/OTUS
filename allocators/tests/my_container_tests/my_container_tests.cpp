#include "my_container.h"
#include <gtest/gtest.h>
#include <map>

TEST(MyContainerTest, ConstructContainer)
{
    EXPECT_NO_THROW((my_container::MyContainer<float, 100U>{}));
}

TEST(MyContainerTest, ConstructContainerUsingStlAllocator)
{
    EXPECT_NO_THROW((my_container::MyContainer<float, 100U, std::allocator<float>>{}));
}

TEST(MyContainerTest, PushElementIntoContainerAndAccessIt)
{
    my_container::MyContainer<float, 100U> test_container{};
    const auto value{5.F};
    test_container.push_back(value);

    EXPECT_EQ(test_container[0U], value);
}

TEST(MyContainerTest, PushElementIntoContainerWithStlAllocatorAndAccessIt)
{
    my_container::MyContainer<float, 100U, std::allocator<float>> test_container{};
    const auto value{5.F};
    test_container.push_back(value);

    EXPECT_EQ(test_container[0U], value);
}

TEST(MyContainerTest, PushMoreElementsThanAllocated_ExpectBadAlloc)
{
    my_container::MyContainer<float, 1U> test_container{};
    const auto value{5.F};
    test_container.push_back(value);

    EXPECT_THROW(test_container.push_back(value), std::bad_alloc);
}

TEST(MyContainerTest, AccessElementOutOfAllocatedMemory_ExpectBadAlloc)
{
    my_container::MyContainer<float, 1U> test_container{};
    const auto value{5.F};
    test_container.push_back(value);

    ASSERT_EXIT((std::cout << test_container[1U]),::testing::KilledBySignal(SIGSEGV),".*");
}