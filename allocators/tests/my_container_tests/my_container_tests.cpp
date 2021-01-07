#include "my_container.h"
#include <gtest/gtest.h>
#include <map>
#include <algorithm>
#include <iterator>

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

TEST(MyContainerTest, PushElement_ThenChangeItsValue)
{
    my_container::MyContainer<float, 1U> test_container{};
    const auto value{5.F};
    test_container.push_back(value);

    const auto new_value{10.F};
    test_container[0U] = new_value;

    EXPECT_EQ(test_container.at(0U), new_value);
}

TEST(MyContainerTest, FillContainerAndIterateThroughIt)
{
    const auto num_of_elements{30U};
    my_container::MyContainer<float, num_of_elements> test_container{};
    for(auto i{0.F}; i < num_of_elements; ++i)
    {
        test_container.push_back(i);
    }

    auto expected_value{0.F};
    for(const auto& el : test_container)
    {
        EXPECT_EQ(el, expected_value);
        ++expected_value;
    }


    expected_value = 0.F;
    for(auto itr{test_container.begin()}; itr != test_container.end(); ++itr)
    {
        EXPECT_EQ(*itr, expected_value);
        ++expected_value;
    }
}

TEST(MyContainerTest, FillContainerAndFindElementInIt)
{
    const auto num_of_elements{30U};
    my_container::MyContainer<float, num_of_elements> test_container{};
    for(auto i{0.F}; i < num_of_elements; ++i)
    {
        test_container.push_back(i);
    }

    const auto it{std::find(test_container.begin(), test_container.end(), 1.F)};
    const auto idx{std::distance(test_container.begin(), it)};
    EXPECT_EQ(idx, 1U);

    const auto it_end{std::find(test_container.begin(), test_container.end(), 30.F)};
    EXPECT_EQ(test_container.end(), it_end);
}