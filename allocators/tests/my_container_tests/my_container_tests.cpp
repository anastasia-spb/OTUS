#include "my_container.h"
#include <gtest/gtest.h>
#include <map>

TEST(MyContainerTest, ConstructContainer)
{
    EXPECT_NO_THROW((my_container::MyContainer<float, 100U>{}));
}