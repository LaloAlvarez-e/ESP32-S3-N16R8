#include <cstdint>

#include <gtest/gtest.h>

extern "C"
{
#include "os_clock/os_clock.h"
}

TEST(os_clock_test, returns_invalid_argument_when_output_pointer_is_null)
{
    EXPECT_EQ(OS_CLOCK_ERROR_INVALID_ARGUMENT, os_clock__get_ticks(nullptr));
}

TEST(os_clock_test, returns_default_tick_count_with_default_platform_hook)
{
    uint32_t u32Ticks = 1U;

    EXPECT_EQ(OS_CLOCK_ERROR_OK, os_clock__get_ticks(&u32Ticks));
    EXPECT_EQ(0U, u32Ticks);
}
