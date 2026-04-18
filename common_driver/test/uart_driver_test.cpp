#include <cstdint>

#include <gtest/gtest.h>

extern "C"
{
#include "uart_driver/uart_driver.h"
}

TEST(uart_driver_test, init_returns_invalid_argument_for_zero_port)
{
    EXPECT_EQ(UART_DRIVER_ERROR_INVALID_ARGUMENT, uart_driver__init(0U));
}

TEST(uart_driver_test, init_returns_ok_for_valid_port)
{
    EXPECT_EQ(UART_DRIVER_ERROR_OK, uart_driver__init(1U));
}

TEST(uart_driver_test, write_returns_invalid_argument_for_null_buffer)
{
    EXPECT_EQ(UART_DRIVER_ERROR_INVALID_ARGUMENT,
              uart_driver__write(1U, nullptr, 1U));
}

TEST(uart_driver_test, write_returns_ok_for_valid_arguments)
{
    static const uint8_t au8Buffer[2] = {0x12U, 0x34U};

    EXPECT_EQ(UART_DRIVER_ERROR_OK,
              uart_driver__write(1U, au8Buffer, 2U));
}
