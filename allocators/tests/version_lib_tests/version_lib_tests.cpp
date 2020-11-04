#include "get_version.h"
#include <gtest/gtest.h>


TEST(VersionTest, VersionShallBeGreaterThanZero)
{
    EXPECT_GT(version(), 0);
}