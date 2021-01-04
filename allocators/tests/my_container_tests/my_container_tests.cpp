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

    EXPECT_EQ(test_container.at(0U), value);
}

TEST(MyContainerTest, PushElementIntoContainerWithStlAllocatorAndAccessIt)
{
    my_container::MyContainer<float, 100U, std::allocator<float>> test_container{};
    const auto value{5.F};
    test_container.push_back(value);

    EXPECT_EQ(test_container.at(0U), value);
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

    ASSERT_EXIT((std::cout << test_container.at(1U)),::testing::KilledBySignal(SIGSEGV),".*");
}

TEST(MyContainerTest, PushTenElemensCopyContainerAndCompareWithCopy)
{
    const auto num_elements{25U};
    my_container::MyContainer<std::uint32_t, num_elements> test_container{};
    for(auto i{0U}; i < num_elements; ++i)
    {
        test_container.push_back(i);
    }

    const auto test_container_copy{test_container};

    EXPECT_EQ(test_container, test_container_copy);
}

TEST(MyContainerTest, PushTenElemensMoveContainer_ExpectContainerBeInvalid)
{
    const auto num_elements{25U};
    const auto num_elements_to_push{20U};

    my_container::MyContainer<std::uint32_t, num_elements> test_container_copy{};
    {
        my_container::MyContainer<std::uint32_t, num_elements> test_container{};
        for(auto i{0U}; i < num_elements_to_push; ++i)
        {
            test_container.push_back(i);
        }

        test_container_copy = std::move(test_container);
        EXPECT_THROW(test_container.push_back(num_elements_to_push), std::bad_alloc);
    }

    EXPECT_EQ(test_container_copy.size(), num_elements_to_push);
    EXPECT_NO_THROW((test_container_copy.push_back(num_elements_to_push)));
}