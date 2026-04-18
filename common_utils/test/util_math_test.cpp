#include <cstdint>

#include <gtest/gtest.h>

extern "C"
{
#include "util_math/util_math.h"
}

TEST(util_math_test, returns_invalid_argument_when_output_pointer_is_null)
{
    EXPECT_EQ(UTIL_MATH_ERROR_INVALID_ARGUMENT,
              util_math__saturating_add(1U, 2U, nullptr));
}

TEST(util_math_test, returns_sum_without_overflow)
{
    uint32_t u32Result = 0U;

    EXPECT_EQ(UTIL_MATH_ERROR_OK,
              util_math__saturating_add(2U, 3U, &u32Result));
    EXPECT_EQ(5U, u32Result);
}

TEST(util_math_test, saturates_and_reports_overflow)
{
    uint32_t u32Result = 0U;

    EXPECT_EQ(UTIL_MATH_ERROR_OVERFLOW,
              util_math__saturating_add(UINT32_MAX, 1U, &u32Result));
    EXPECT_EQ(UINT32_MAX, u32Result);
}
