#include <gtest/gtest.h>

// GoogleTest groups the test results by test suites, so logically related
// tests should be in the same test suite; in other words, the first argument
// to their TEST() should be the same

// The first argument is the name of the test suite, and the second argument
// is the test’s name within the test suite.
TEST(HelloTest, BasicAssertions)
{
    // Expect two strings not to be equal.
    EXPECT_STRNE("hello", "world");
    // Expect equality.
    EXPECT_EQ(7 * 6, 42);
}
