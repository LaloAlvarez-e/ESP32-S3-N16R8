#include <inttypes.h>

#include "esp_chip_info.h"
#include "esp_err.h"
#include "esp_flash.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define HELLO_WORLD_PROJECT_DELAY_MS (1000U)
#define HELLO_WORLD_PROJECT_BYTES_PER_MEBIBYTE (1024U * 1024U)
#define HELLO_WORLD_PROJECT_DEBUG_STARTUP_LOG_INTERVAL_MS (1000U)

#ifndef HELLO_WORLD_PROJECT_DEBUG_STARTUP_HOLD_MS
#define HELLO_WORLD_PROJECT_DEBUG_STARTUP_HOLD_MS (0U)
#endif

static const char* HELLO_WORLD_PROJECT_LOG_TAG = "hello_world";

/**
 * @brief Log basic chip information for the running ESP32-S3 target.
 * @return ESP_OK on success, otherwise an ESP-IDF error code.
 */
static esp_err_t hello_world_project_log_chip_info(void)
{
    esp_err_t eEspError = ESP_OK;
    esp_chip_info_t xChipInfo = {0};
    uint32_t u32FlashSizeBytes = 0U;
    uint32_t u32FlashSizeMebibytes = 0U;

    esp_chip_info(&xChipInfo);

    if (ESP_OK == eEspError)
    {
        eEspError = esp_flash_get_size(NULL, &u32FlashSizeBytes);
    }

    if (ESP_OK == eEspError)
    {
        u32FlashSizeMebibytes = u32FlashSizeBytes / HELLO_WORLD_PROJECT_BYTES_PER_MEBIBYTE;

        ESP_LOGI(HELLO_WORLD_PROJECT_LOG_TAG,
                 "ESP32-S3 detected: %d core(s), revision %d, %" PRIu32 " MiB flash",
                 xChipInfo.cores,
                 xChipInfo.revision,
                 u32FlashSizeMebibytes);
    }

    if (ESP_OK != eEspError)
    {
        ESP_LOGW(HELLO_WORLD_PROJECT_LOG_TAG,
                 "Unable to query flash size: %s",
                 esp_err_to_name(eEspError));
    }

    return eEspError;
}

/**
 * @brief Hold startup long enough for a debugger attach when the debug build enables it.
 */
static void hello_world_project_wait_for_debug_attach(void)
{
    uint32_t u32RemainingDelayMs = HELLO_WORLD_PROJECT_DEBUG_STARTUP_HOLD_MS;
    uint32_t u32DelayStepMs = 0U;

    if (0U < u32RemainingDelayMs)
    {
        ESP_LOGI(HELLO_WORLD_PROJECT_LOG_TAG,
                 "Debug attach hold active for %" PRIu32 " ms",
                 u32RemainingDelayMs);
    }

    while (0U < u32RemainingDelayMs)
    {
        if (HELLO_WORLD_PROJECT_DEBUG_STARTUP_LOG_INTERVAL_MS < u32RemainingDelayMs)
        {
            u32DelayStepMs = HELLO_WORLD_PROJECT_DEBUG_STARTUP_LOG_INTERVAL_MS;
        }
        else
        {
            u32DelayStepMs = u32RemainingDelayMs;
        }

        ESP_LOGI(HELLO_WORLD_PROJECT_LOG_TAG,
                 "Waiting %" PRIu32 " ms before startup continues",
                 u32RemainingDelayMs);

        vTaskDelay(pdMS_TO_TICKS(u32DelayStepMs));
        u32RemainingDelayMs -= u32DelayStepMs;
    }
}

/**
 * @brief ESP-IDF application entry point for the hello world bring-up project.
 */
void app_main(void)
{
    esp_err_t eEspError = ESP_OK;
    TickType_t xDelayTicks = pdMS_TO_TICKS(HELLO_WORLD_PROJECT_DELAY_MS);

    ESP_LOGI(HELLO_WORLD_PROJECT_LOG_TAG, "Hello world from ESP32-S3");
    hello_world_project_wait_for_debug_attach();

    if (ESP_OK == eEspError)
    {
        eEspError = hello_world_project_log_chip_info();
    }

    if (ESP_OK != eEspError)
    {
        ESP_LOGW(HELLO_WORLD_PROJECT_LOG_TAG,
                 "Continuing after startup warning: %s",
                 esp_err_to_name(eEspError));
    }

    for (;;)
    {
        ESP_LOGI(HELLO_WORLD_PROJECT_LOG_TAG, "Hello world task alive");
        vTaskDelay(xDelayTicks);
    }
}