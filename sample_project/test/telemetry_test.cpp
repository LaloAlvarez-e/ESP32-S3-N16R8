#include <gtest/gtest.h>

extern "C"
{
#include "app_core/telemetry/telemetry.h"
}

TEST(telemetry_test, returns_invalid_argument_for_unknown_message)
{
    EXPECT_EQ(TELEMETRY_ERROR_INVALID_ARGUMENT,
              telemetry__publish((telemetry_message_id_t)0));
}

TEST(telemetry_test, returns_ok_for_heartbeat_message)
{
    EXPECT_EQ(TELEMETRY_ERROR_OK,
              telemetry__publish(TELEMETRY_MESSAGE_ID_HEARTBEAT));
}
