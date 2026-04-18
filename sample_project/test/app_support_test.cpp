#include <gmock/gmock.h>
#include <gtest/gtest.h>

extern "C"
{
#include "app_support/app_support.h"
#include "os_clock/os_clock.h"
#include "util_math/util_math.h"
#include "util_status/util_status.h"
}

namespace
{
constexpr uint32_t APP_SUPPORT_TEST_BOOT_TICKS = 4U;
constexpr uint32_t APP_SUPPORT_TEST_LOG_VALUE = 5U;

class app_support_dependency_mock
{
public:
    MOCK_METHOD(os_clock_error_t, os_clock__get_ticks, (uint32_t* pu32Ticks));
    MOCK_METHOD(util_math_error_t, util_math__saturating_add, (uint32_t u32Left,
                                                               uint32_t u32Right,
                                                               uint32_t* pu32Result));
    MOCK_METHOD(util_status_error_t, util_status__normalize, (util_status_error_t eInputError,
                                                              util_status_error_t* penOutputError));
};

app_support_dependency_mock* gpAppSupportDependencyMock = nullptr;

extern "C" os_clock_error_t os_clock__get_ticks(uint32_t* pu32Ticks)
{
    return gpAppSupportDependencyMock->os_clock__get_ticks(pu32Ticks);
}

extern "C" util_math_error_t util_math__saturating_add(uint32_t u32Left,
                                                        uint32_t u32Right,
                                                        uint32_t* pu32Result)
{
    return gpAppSupportDependencyMock->util_math__saturating_add(u32Left, u32Right, pu32Result);
}

extern "C" util_status_error_t util_status__normalize(util_status_error_t eInputError,
                                                       util_status_error_t* penOutputError)
{
    return gpAppSupportDependencyMock->util_status__normalize(eInputError, penOutputError);
}

class app_support_test : public ::testing::Test
{
protected:
    void SetUp() override
    {
        gpAppSupportDependencyMock = &xDependencyMock;
    }

    void TearDown() override
    {
        gpAppSupportDependencyMock = nullptr;
    }

    testing::StrictMock<app_support_dependency_mock> xDependencyMock;
};
}  // namespace

TEST_F(app_support_test, record_boot_returns_clock_failure_when_clock_read_fails)
{
    EXPECT_CALL(xDependencyMock, os_clock__get_ticks(testing::_))
        .WillOnce(testing::Return(OS_CLOCK_ERROR_PLATFORM_FAILURE));

    EXPECT_EQ(APP_SUPPORT_ERROR_CLOCK_FAILURE, app_support__record_boot());
}

TEST_F(app_support_test, record_boot_returns_utility_failure_when_math_fails)
{
    EXPECT_CALL(xDependencyMock, os_clock__get_ticks(testing::_))
        .WillOnce(testing::DoAll(
            testing::SetArgPointee<0>(APP_SUPPORT_TEST_BOOT_TICKS),
            testing::Return(OS_CLOCK_ERROR_OK)));
    EXPECT_CALL(xDependencyMock,
                util_math__saturating_add(APP_SUPPORT_TEST_BOOT_TICKS, 1U, testing::_))
        .WillOnce(testing::Return(UTIL_MATH_ERROR_OVERFLOW));

    EXPECT_EQ(APP_SUPPORT_ERROR_UTILITY_FAILURE, app_support__record_boot());
}

TEST_F(app_support_test, record_boot_returns_ok_when_dependencies_succeed)
{
    EXPECT_CALL(xDependencyMock, os_clock__get_ticks(testing::_))
        .WillOnce(testing::DoAll(
            testing::SetArgPointee<0>(APP_SUPPORT_TEST_BOOT_TICKS),
            testing::Return(OS_CLOCK_ERROR_OK)));
    EXPECT_CALL(xDependencyMock,
                util_math__saturating_add(APP_SUPPORT_TEST_BOOT_TICKS, 1U, testing::_))
        .WillOnce(testing::DoAll(
            testing::SetArgPointee<2>(APP_SUPPORT_TEST_LOG_VALUE),
            testing::Return(UTIL_MATH_ERROR_OK)));

    EXPECT_EQ(APP_SUPPORT_ERROR_OK, app_support__record_boot());
}

TEST_F(app_support_test, report_result_returns_utility_failure_when_normalize_fails)
{
    EXPECT_CALL(xDependencyMock,
                util_status__normalize(UTIL_STATUS_ERROR_INVALID_ARGUMENT, testing::_))
        .WillOnce(testing::Return(UTIL_STATUS_ERROR_INVALID_ARGUMENT));

    EXPECT_EQ(APP_SUPPORT_ERROR_UTILITY_FAILURE, app_support__report_result(1U));
}

TEST_F(app_support_test, report_result_returns_ok_when_normalize_succeeds)
{
    EXPECT_CALL(xDependencyMock,
                util_status__normalize(UTIL_STATUS_ERROR_OK, testing::_))
        .WillOnce(testing::DoAll(
            testing::SetArgPointee<1>(UTIL_STATUS_ERROR_OK),
            testing::Return(UTIL_STATUS_ERROR_OK)));

    EXPECT_EQ(APP_SUPPORT_ERROR_OK, app_support__report_result(0U));
}
