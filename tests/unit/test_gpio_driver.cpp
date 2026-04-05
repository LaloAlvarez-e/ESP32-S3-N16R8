/**
 * @file test_gpio_driver.cpp
 * @brief Unit tests for gpio_driver component.
 */
#include <gtest/gtest.h>
#include <cstring>

#include "driver/gpio.h"
#include "gpio_driver.h"

class GpioDriverTest : public ::testing::Test {
protected:
    void SetUp() override
    {
        memset(&gpio_mock_state, 0, sizeof(gpio_mock_state));
    }

    gpio_driver_config_t make_cfg(gpio_num_t pin = GPIO_NUM_2,
                                   gpio_mode_t mode = GPIO_MODE_OUTPUT)
    {
        return gpio_driver_config_t{
            .pin       = pin,
            .mode      = mode,
            .pull_up   = false,
            .pull_down = false,
        };
    }
};

/* ---------- gpio_driver_init -------------------------------------------- */

TEST_F(GpioDriverTest, InitNullConfigReturnsInvalidArg)
{
    EXPECT_EQ(gpio_driver_init(nullptr), ESP_ERR_INVALID_ARG);
}

TEST_F(GpioDriverTest, InitOutputPinSucceeds)
{
    auto cfg = make_cfg(GPIO_NUM_2, GPIO_MODE_OUTPUT);
    EXPECT_EQ(gpio_driver_init(&cfg), ESP_OK);
    EXPECT_TRUE(gpio_mock_state.config_called);
}

TEST_F(GpioDriverTest, InitInputPinSucceeds)
{
    auto cfg = make_cfg(GPIO_NUM_4, GPIO_MODE_INPUT);
    EXPECT_EQ(gpio_driver_init(&cfg), ESP_OK);
}

TEST_F(GpioDriverTest, InitWithPullUpSetsFlag)
{
    gpio_driver_config_t cfg = make_cfg(GPIO_NUM_5, GPIO_MODE_INPUT);
    cfg.pull_up = true;
    EXPECT_EQ(gpio_driver_init(&cfg), ESP_OK);
    EXPECT_EQ(gpio_mock_state.configs[GPIO_NUM_5].pull_up_en, GPIO_PULLUP_ENABLE);
}

TEST_F(GpioDriverTest, InitWithPullDownSetsFlag)
{
    gpio_driver_config_t cfg = make_cfg(GPIO_NUM_6, GPIO_MODE_INPUT);
    cfg.pull_down = true;
    EXPECT_EQ(gpio_driver_init(&cfg), ESP_OK);
    EXPECT_EQ(gpio_mock_state.configs[GPIO_NUM_6].pull_down_en, GPIO_PULLDOWN_ENABLE);
}

/* ---------- gpio_driver_set_level --------------------------------------- */

TEST_F(GpioDriverTest, SetLevelNullConfigReturnsInvalidArg)
{
    EXPECT_EQ(gpio_driver_set_level(nullptr, true), ESP_ERR_INVALID_ARG);
}

TEST_F(GpioDriverTest, SetLevelHighStoresOne)
{
    auto cfg = make_cfg(GPIO_NUM_2, GPIO_MODE_OUTPUT);
    gpio_driver_init(&cfg);
    EXPECT_EQ(gpio_driver_set_level(&cfg, true), ESP_OK);
    EXPECT_EQ(gpio_mock_state.levels[GPIO_NUM_2], 1);
}

TEST_F(GpioDriverTest, SetLevelLowStoresZero)
{
    auto cfg = make_cfg(GPIO_NUM_2, GPIO_MODE_OUTPUT);
    gpio_driver_init(&cfg);
    gpio_driver_set_level(&cfg, true);
    EXPECT_EQ(gpio_driver_set_level(&cfg, false), ESP_OK);
    EXPECT_EQ(gpio_mock_state.levels[GPIO_NUM_2], 0);
}

/* ---------- gpio_driver_get_level --------------------------------------- */

TEST_F(GpioDriverTest, GetLevelNullConfigReturnsMinusOne)
{
    EXPECT_EQ(gpio_driver_get_level(nullptr), -1);
}

TEST_F(GpioDriverTest, GetLevelReflectsSetLevel)
{
    auto cfg = make_cfg(GPIO_NUM_3, GPIO_MODE_OUTPUT);
    gpio_driver_init(&cfg);
    gpio_driver_set_level(&cfg, true);
    EXPECT_EQ(gpio_driver_get_level(&cfg), 1);
    gpio_driver_set_level(&cfg, false);
    EXPECT_EQ(gpio_driver_get_level(&cfg), 0);
}

/* ---------- gpio_driver_deinit ------------------------------------------ */

TEST_F(GpioDriverTest, DeinitNullConfigReturnsInvalidArg)
{
    EXPECT_EQ(gpio_driver_deinit(nullptr), ESP_ERR_INVALID_ARG);
}

TEST_F(GpioDriverTest, DeinitSucceeds)
{
    auto cfg = make_cfg();
    gpio_driver_init(&cfg);
    EXPECT_EQ(gpio_driver_deinit(&cfg), ESP_OK);
}
