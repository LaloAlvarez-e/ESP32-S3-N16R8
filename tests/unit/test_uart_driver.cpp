/**
 * @file test_uart_driver.cpp
 * @brief Unit tests for uart_driver component.
 */
#include <gtest/gtest.h>
#include <cstring>

#include "driver/uart.h"
#include "uart_driver.h"

class UartDriverTest : public ::testing::Test {
protected:
    void SetUp() override
    {
        memset(&uart_mock_state, 0, sizeof(uart_mock_state));
    }

    uart_driver_config_t make_cfg(uart_port_t port = UART_NUM_1)
    {
        return uart_driver_config_t{
            .port      = port,
            .baud_rate = 115200,
            .tx_pin    = UART_PIN_NO_CHANGE,
            .rx_pin    = UART_PIN_NO_CHANGE,
            .buf_size  = 256,
        };
    }
};

/* ---------- uart_driver_init -------------------------------------------- */

TEST_F(UartDriverTest, InitNullConfigReturnsInvalidArg)
{
    EXPECT_EQ(uart_driver_init(nullptr), ESP_ERR_INVALID_ARG);
}

TEST_F(UartDriverTest, InitInstallsDriver)
{
    auto cfg = make_cfg(UART_NUM_1);
    EXPECT_EQ(uart_driver_init(&cfg), ESP_OK);
    EXPECT_TRUE(uart_mock_state.installed[UART_NUM_1]);
}

TEST_F(UartDriverTest, InitStoresBaudRate)
{
    auto cfg = make_cfg(UART_NUM_1);
    cfg.baud_rate = 9600;
    uart_driver_init(&cfg);
    EXPECT_EQ(uart_mock_state.configs[UART_NUM_1].baud_rate, 9600);
}

/* ---------- uart_driver_write ------------------------------------------- */

TEST_F(UartDriverTest, WriteNullConfigReturnsMinusOne)
{
    uint8_t buf[] = {0x01};
    EXPECT_EQ(uart_driver_write(nullptr, buf, 1), -1);
}

TEST_F(UartDriverTest, WriteNullDataReturnsMinusOne)
{
    auto cfg = make_cfg();
    EXPECT_EQ(uart_driver_write(&cfg, nullptr, 1), -1);
}

TEST_F(UartDriverTest, WriteZeroLenReturnsMinusOne)
{
    auto cfg = make_cfg();
    uint8_t buf[] = {0x00};
    EXPECT_EQ(uart_driver_write(&cfg, buf, 0), -1);
}

TEST_F(UartDriverTest, WriteReturnsByteCount)
{
    auto cfg = make_cfg(UART_NUM_1);
    uart_driver_init(&cfg);
    const uint8_t data[] = "hello";
    int written = uart_driver_write(&cfg, data, sizeof(data) - 1);
    EXPECT_EQ(written, (int)(sizeof(data) - 1));
}

/* ---------- uart_driver_read -------------------------------------------- */

TEST_F(UartDriverTest, ReadNullConfigReturnsMinusOne)
{
    uint8_t buf[10];
    EXPECT_EQ(uart_driver_read(nullptr, buf, sizeof(buf), 100), -1);
}

TEST_F(UartDriverTest, ReadNullBufReturnsMinusOne)
{
    auto cfg = make_cfg();
    EXPECT_EQ(uart_driver_read(&cfg, nullptr, 10, 100), -1);
}

TEST_F(UartDriverTest, ReadZeroLenReturnsMinusOne)
{
    auto cfg = make_cfg();
    uint8_t buf[10];
    EXPECT_EQ(uart_driver_read(&cfg, buf, 0, 100), -1);
}

TEST_F(UartDriverTest, ReadReturnsByteCount)
{
    auto cfg = make_cfg(UART_NUM_1);
    uart_driver_init(&cfg);
    uint8_t buf[16];
    int read = uart_driver_read(&cfg, buf, sizeof(buf), 100);
    EXPECT_EQ(read, (int)sizeof(buf));
}

/* ---------- uart_driver_deinit ------------------------------------------ */

TEST_F(UartDriverTest, DeinitNullConfigReturnsInvalidArg)
{
    EXPECT_EQ(uart_driver_deinit(nullptr), ESP_ERR_INVALID_ARG);
}

TEST_F(UartDriverTest, DeinitUninstallsDriver)
{
    auto cfg = make_cfg(UART_NUM_1);
    uart_driver_init(&cfg);
    EXPECT_TRUE(uart_mock_state.installed[UART_NUM_1]);
    EXPECT_EQ(uart_driver_deinit(&cfg), ESP_OK);
    EXPECT_FALSE(uart_mock_state.installed[UART_NUM_1]);
}
