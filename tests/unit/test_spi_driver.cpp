/**
 * @file test_spi_driver.cpp
 * @brief Unit tests for spi_driver component.
 */
#include <gtest/gtest.h>
#include <cstring>

#include "driver/spi_master.h"
#include "spi_driver.h"

class SpiDriverTest : public ::testing::Test {
protected:
    void SetUp() override
    {
        memset(&spi_mock_state, 0, sizeof(spi_mock_state));
        spi_mock_state.transmit_result = ESP_OK;
    }

    spi_driver_config_t make_cfg(spi_host_device_t host = SPI2_HOST)
    {
        return spi_driver_config_t{
            .host   = host,
            .mosi   = 11,
            .miso   = 13,
            .sclk   = 12,
            .cs     = 10,
            .clk_hz = 1000000,
        };
    }
};

/* ---------- spi_driver_init --------------------------------------------- */

TEST_F(SpiDriverTest, InitNullConfigReturnsInvalidArg)
{
    EXPECT_EQ(spi_driver_init(nullptr), ESP_ERR_INVALID_ARG);
}

TEST_F(SpiDriverTest, InitInitializesBus)
{
    auto cfg = make_cfg(SPI2_HOST);
    EXPECT_EQ(spi_driver_init(&cfg), ESP_OK);
    EXPECT_TRUE(spi_mock_state.bus_initialized[SPI2_HOST]);
}

TEST_F(SpiDriverTest, InitAddsDevice)
{
    auto cfg = make_cfg(SPI2_HOST);
    EXPECT_EQ(spi_driver_init(&cfg), ESP_OK);
    EXPECT_NE(spi_mock_state.devices[SPI2_HOST], nullptr);
}

/* ---------- spi_driver_transfer ----------------------------------------- */

TEST_F(SpiDriverTest, TransferNullConfigReturnsInvalidArg)
{
    uint8_t tx[4] = {0, 1, 2, 3};
    uint8_t rx[4];
    EXPECT_EQ(spi_driver_transfer(nullptr, tx, rx, 4), ESP_ERR_INVALID_ARG);
}

TEST_F(SpiDriverTest, TransferZeroLenReturnsInvalidArg)
{
    auto cfg = make_cfg(SPI2_HOST);
    spi_driver_init(&cfg);
    uint8_t tx[4] = {}, rx[4] = {};
    EXPECT_EQ(spi_driver_transfer(&cfg, tx, rx, 0), ESP_ERR_INVALID_ARG);
}

TEST_F(SpiDriverTest, TransferSucceeds)
{
    auto cfg = make_cfg(SPI2_HOST);
    spi_driver_init(&cfg);
    uint8_t tx[] = {0xDE, 0xAD};
    uint8_t rx[2];
    EXPECT_EQ(spi_driver_transfer(&cfg, tx, rx, sizeof(tx)), ESP_OK);
}

TEST_F(SpiDriverTest, TransferTxOnlySucceeds)
{
    auto cfg = make_cfg(SPI2_HOST);
    spi_driver_init(&cfg);
    uint8_t tx[] = {0x01, 0x02, 0x03};
    EXPECT_EQ(spi_driver_transfer(&cfg, tx, nullptr, sizeof(tx)), ESP_OK);
}

TEST_F(SpiDriverTest, TransferRxOnlySucceeds)
{
    auto cfg = make_cfg(SPI2_HOST);
    spi_driver_init(&cfg);
    uint8_t rx[4];
    EXPECT_EQ(spi_driver_transfer(&cfg, nullptr, rx, sizeof(rx)), ESP_OK);
}

TEST_F(SpiDriverTest, TransferUninitializedReturnsInvalidState)
{
    /* Do NOT call spi_driver_init — device handle remains null */
    auto cfg = make_cfg(SPI3_HOST);
    uint8_t tx[2] = {0}, rx[2] = {};
    EXPECT_EQ(spi_driver_transfer(&cfg, tx, rx, 2), ESP_ERR_INVALID_STATE);
}

/* ---------- spi_driver_deinit ------------------------------------------- */

TEST_F(SpiDriverTest, DeinitNullConfigReturnsInvalidArg)
{
    EXPECT_EQ(spi_driver_deinit(nullptr), ESP_ERR_INVALID_ARG);
}

TEST_F(SpiDriverTest, DeinitFreesBus)
{
    auto cfg = make_cfg(SPI2_HOST);
    spi_driver_init(&cfg);
    EXPECT_EQ(spi_driver_deinit(&cfg), ESP_OK);
    EXPECT_FALSE(spi_mock_state.bus_initialized[SPI2_HOST]);
}
