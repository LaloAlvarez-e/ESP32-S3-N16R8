#include <gmock/gmock.h>
#include <gtest/gtest.h>

extern "C"
{
#include "app_core/app_core.h"
#include "gpio_driver/gpio_driver.h"
}

namespace
{
constexpr uint32_t APP_CORE_TEST_STATUS_LED_PIN = 2U;

class app_core_dependency_mock
{
public:
    MOCK_METHOD(gpio_driver_error_t, gpio_driver__init, (uint32_t u32PinNumber));
    MOCK_METHOD(gpio_driver_error_t, gpio_driver__set_level, (uint32_t u32PinNumber,
                                                              gpio_driver_level_t enLevel));
    MOCK_METHOD(telemetry_error_t, telemetry__publish, (telemetry_message_id_t enMessageId));
};

app_core_dependency_mock* gpAppCoreDependencyMock = nullptr;

extern "C" gpio_driver_error_t gpio_driver__init(uint32_t u32PinNumber)
{
    return gpAppCoreDependencyMock->gpio_driver__init(u32PinNumber);
}

extern "C" gpio_driver_error_t gpio_driver__set_level(uint32_t u32PinNumber,
                                                       gpio_driver_level_t enLevel)
{
    return gpAppCoreDependencyMock->gpio_driver__set_level(u32PinNumber, enLevel);
}

extern "C" telemetry_error_t telemetry__publish(telemetry_message_id_t enMessageId)
{
    return gpAppCoreDependencyMock->telemetry__publish(enMessageId);
}

class app_core_test : public ::testing::Test
{
protected:
    void SetUp() override
    {
        gpAppCoreDependencyMock = &xDependencyMock;
    }

    void TearDown() override
    {
        gpAppCoreDependencyMock = nullptr;
    }

    testing::StrictMock<app_core_dependency_mock> xDependencyMock;
};
}  // namespace

TEST_F(app_core_test, init_returns_driver_failure_when_gpio_init_fails)
{
    EXPECT_CALL(xDependencyMock, gpio_driver__init(APP_CORE_TEST_STATUS_LED_PIN))
        .WillOnce(testing::Return(GPIO_DRIVER_ERROR_PLATFORM_FAILURE));

    EXPECT_EQ(SAMPLE_PROJECT_ERROR_DRIVER_FAILURE, app_core__init());
}

TEST_F(app_core_test, run_cycle_returns_telemetry_failure_when_publish_fails)
{
    EXPECT_CALL(xDependencyMock, telemetry__publish(TELEMETRY_MESSAGE_ID_HEARTBEAT))
        .WillOnce(testing::Return(TELEMETRY_ERROR_PLATFORM_FAILURE));

    EXPECT_EQ(SAMPLE_PROJECT_ERROR_TELEMETRY_FAILURE, app_core__run_cycle());
}

TEST_F(app_core_test, run_cycle_returns_driver_failure_when_indicator_raise_fails)
{
    EXPECT_CALL(xDependencyMock, telemetry__publish(TELEMETRY_MESSAGE_ID_HEARTBEAT))
        .WillOnce(testing::Return(TELEMETRY_ERROR_OK));
    EXPECT_CALL(xDependencyMock,
                gpio_driver__set_level(APP_CORE_TEST_STATUS_LED_PIN, GPIO_DRIVER_LEVEL_HIGH))
        .WillOnce(testing::Return(GPIO_DRIVER_ERROR_PLATFORM_FAILURE));

    EXPECT_EQ(SAMPLE_PROJECT_ERROR_DRIVER_FAILURE, app_core__run_cycle());
}

TEST_F(app_core_test, run_cycle_returns_driver_failure_when_indicator_clear_fails)
{
    EXPECT_CALL(xDependencyMock, telemetry__publish(TELEMETRY_MESSAGE_ID_HEARTBEAT))
        .WillOnce(testing::Return(TELEMETRY_ERROR_OK));
    EXPECT_CALL(xDependencyMock,
                gpio_driver__set_level(APP_CORE_TEST_STATUS_LED_PIN, GPIO_DRIVER_LEVEL_HIGH))
        .WillOnce(testing::Return(GPIO_DRIVER_ERROR_OK));
    EXPECT_CALL(xDependencyMock,
                gpio_driver__set_level(APP_CORE_TEST_STATUS_LED_PIN, GPIO_DRIVER_LEVEL_LOW))
        .WillOnce(testing::Return(GPIO_DRIVER_ERROR_PLATFORM_FAILURE));

    EXPECT_EQ(SAMPLE_PROJECT_ERROR_DRIVER_FAILURE, app_core__run_cycle());
}

TEST_F(app_core_test, run_cycle_returns_ok_when_dependencies_succeed)
{
    EXPECT_CALL(xDependencyMock, telemetry__publish(TELEMETRY_MESSAGE_ID_HEARTBEAT))
        .WillOnce(testing::Return(TELEMETRY_ERROR_OK));
    EXPECT_CALL(xDependencyMock,
                gpio_driver__set_level(APP_CORE_TEST_STATUS_LED_PIN, GPIO_DRIVER_LEVEL_HIGH))
        .WillOnce(testing::Return(GPIO_DRIVER_ERROR_OK));
    EXPECT_CALL(xDependencyMock,
                gpio_driver__set_level(APP_CORE_TEST_STATUS_LED_PIN, GPIO_DRIVER_LEVEL_LOW))
        .WillOnce(testing::Return(GPIO_DRIVER_ERROR_OK));

    EXPECT_EQ(SAMPLE_PROJECT_ERROR_OK, app_core__run_cycle());
}
