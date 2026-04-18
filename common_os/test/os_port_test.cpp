#include <gtest/gtest.h>

extern "C"
{
#include "os_port/os_port.h"
}

TEST(os_port_test, platform_start_scheduler_returns_ok_with_default_hook)
{
    EXPECT_EQ(COMMON_OS_ERROR_OK, os_port__platform_start_scheduler());
}

TEST(os_port_test, init_returns_ok_with_default_hooks)
{
    EXPECT_EQ(COMMON_OS_ERROR_OK, os_port__init());
}
