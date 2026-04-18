#include <gtest/gtest.h>

extern "C"
{
#include "gpio_driver/gpio_driver.h"
}

TEST(gpio_driver_test, init_returns_invalid_argument_for_zero_pin)
{
    EXPECT_EQ(GPIO_DRIVER_ERROR_INVALID_ARGUMENT, gpio_driver__init(0U));
}

TEST(gpio_driver_test, init_returns_ok_for_valid_pin)
{
    EXPECT_EQ(GPIO_DRIVER_ERROR_OK, gpio_driver__init(1U));
}

TEST(gpio_driver_test, set_level_returns_invalid_argument_for_invalid_level)
{
    EXPECT_EQ(GPIO_DRIVER_ERROR_INVALID_ARGUMENT,
              gpio_driver__set_level(1U, (gpio_driver_level_t)2));
}

TEST(gpio_driver_test, set_level_returns_ok_for_valid_arguments)
{
    EXPECT_EQ(GPIO_DRIVER_ERROR_OK,
              gpio_driver__set_level(1U, GPIO_DRIVER_LEVEL_HIGH));
}
