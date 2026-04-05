/**
 * @file test_i2c_driver.cpp
 * @brief Unit tests for i2c_driver component.
 */
#include <gtest/gtest.h>
#include <cstring>

#include "driver/i2c.h"
#include "i2c_driver.h"

class I2cDriverTest : public ::testing::Test {
protected:
    void SetUp() override
    {
        memset(&i2c_mock_state, 0, sizeof(i2c_mock_state));
        i2c_mock_state.cmd_begin_result = ESP_OK;
    }

    i2c_driver_config_t make_cfg(i2c_port_t port = I2C_NUM_0)
    {
        return i2c_driver_config_t{
            .port    = port,
            .sda_pin = 8,
            .scl_pin = 9,
            .clk_hz  = 400000,
            .pullup  = true,
        };
    }
};

/* ---------- i2c_driver_init --------------------------------------------- */

TEST_F(I2cDriverTest, InitNullConfigReturnsInvalidArg)
{
    EXPECT_EQ(i2c_driver_init(nullptr), ESP_ERR_INVALID_ARG);
}

TEST_F(I2cDriverTest, InitInstallsDriver)
{
    auto cfg = make_cfg(I2C_NUM_0);
    EXPECT_EQ(i2c_driver_init(&cfg), ESP_OK);
    EXPECT_TRUE(i2c_mock_state.installed[I2C_NUM_0]);
}

TEST_F(I2cDriverTest, InitStoresClockSpeed)
{
    auto cfg = make_cfg(I2C_NUM_0);
    cfg.clk_hz = 100000;
    i2c_driver_init(&cfg);
    EXPECT_EQ(i2c_mock_state.configs[I2C_NUM_0].master.clk_speed, 100000u);
}

TEST_F(I2cDriverTest, InitPullUpEnablesPullUp)
{
    auto cfg = make_cfg(I2C_NUM_0);
    cfg.pullup = true;
    i2c_driver_init(&cfg);
    EXPECT_EQ(i2c_mock_state.configs[I2C_NUM_0].sda_pullup_en, GPIO_PULLUP_ENABLE);
    EXPECT_EQ(i2c_mock_state.configs[I2C_NUM_0].scl_pullup_en, GPIO_PULLUP_ENABLE);
}

/* ---------- i2c_driver_write -------------------------------------------- */

TEST_F(I2cDriverTest, WriteNullConfigReturnsInvalidArg)
{
    uint8_t data[] = {0x01};
    EXPECT_EQ(i2c_driver_write(nullptr, 0x50, data, 1), ESP_ERR_INVALID_ARG);
}

TEST_F(I2cDriverTest, WriteNullDataReturnsInvalidArg)
{
    auto cfg = make_cfg();
    EXPECT_EQ(i2c_driver_write(&cfg, 0x50, nullptr, 1), ESP_ERR_INVALID_ARG);
}

TEST_F(I2cDriverTest, WriteZeroLenReturnsInvalidArg)
{
    auto cfg = make_cfg();
    uint8_t data[] = {0x00};
    EXPECT_EQ(i2c_driver_write(&cfg, 0x50, data, 0), ESP_ERR_INVALID_ARG);
}

TEST_F(I2cDriverTest, WriteSucceeds)
{
    auto cfg = make_cfg(I2C_NUM_0);
    i2c_driver_init(&cfg);
    uint8_t data[] = {0xAB, 0xCD};
    EXPECT_EQ(i2c_driver_write(&cfg, 0x50, data, sizeof(data)), ESP_OK);
}

/* ---------- i2c_driver_read --------------------------------------------- */

TEST_F(I2cDriverTest, ReadNullConfigReturnsInvalidArg)
{
    uint8_t buf[4];
    EXPECT_EQ(i2c_driver_read(nullptr, 0x50, buf, sizeof(buf)), ESP_ERR_INVALID_ARG);
}

TEST_F(I2cDriverTest, ReadNullBufReturnsInvalidArg)
{
    auto cfg = make_cfg();
    EXPECT_EQ(i2c_driver_read(&cfg, 0x50, nullptr, 4), ESP_ERR_INVALID_ARG);
}

TEST_F(I2cDriverTest, ReadSucceeds)
{
    auto cfg = make_cfg(I2C_NUM_0);
    i2c_driver_init(&cfg);
    uint8_t buf[4];
    EXPECT_EQ(i2c_driver_read(&cfg, 0x50, buf, sizeof(buf)), ESP_OK);
}

/* ---------- i2c_driver_write_read --------------------------------------- */

TEST_F(I2cDriverTest, WriteReadNullArgsReturnInvalidArg)
{
    auto cfg = make_cfg();
    uint8_t w[] = {0x00};
    uint8_t r[2];
    EXPECT_EQ(i2c_driver_write_read(nullptr, 0x50, w, 1, r, 2), ESP_ERR_INVALID_ARG);
    EXPECT_EQ(i2c_driver_write_read(&cfg, 0x50, nullptr, 1, r, 2), ESP_ERR_INVALID_ARG);
    EXPECT_EQ(i2c_driver_write_read(&cfg, 0x50, w, 0, r, 2), ESP_ERR_INVALID_ARG);
    EXPECT_EQ(i2c_driver_write_read(&cfg, 0x50, w, 1, nullptr, 2), ESP_ERR_INVALID_ARG);
    EXPECT_EQ(i2c_driver_write_read(&cfg, 0x50, w, 1, r, 0), ESP_ERR_INVALID_ARG);
}

TEST_F(I2cDriverTest, WriteReadSucceeds)
{
    auto cfg = make_cfg(I2C_NUM_0);
    i2c_driver_init(&cfg);
    uint8_t reg = 0x10;
    uint8_t val[2];
    EXPECT_EQ(i2c_driver_write_read(&cfg, 0x50, &reg, 1, val, sizeof(val)), ESP_OK);
}

/* ---------- i2c_driver_deinit ------------------------------------------- */

TEST_F(I2cDriverTest, DeinitNullConfigReturnsInvalidArg)
{
    EXPECT_EQ(i2c_driver_deinit(nullptr), ESP_ERR_INVALID_ARG);
}

TEST_F(I2cDriverTest, DeinitUninstallsDriver)
{
    auto cfg = make_cfg(I2C_NUM_0);
    i2c_driver_init(&cfg);
    EXPECT_TRUE(i2c_mock_state.installed[I2C_NUM_0]);
    EXPECT_EQ(i2c_driver_deinit(&cfg), ESP_OK);
    EXPECT_FALSE(i2c_mock_state.installed[I2C_NUM_0]);
}
