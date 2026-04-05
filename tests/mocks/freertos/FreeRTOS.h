/**
 * @file freertos/FreeRTOS.h  (mock)
 * @brief Minimal FreeRTOS shims for host-based unit tests.
 */
#pragma once
#include <stdint.h>

typedef uint32_t TickType_t;
#define portMAX_DELAY       ((TickType_t)0xFFFFFFFF)
#define pdMS_TO_TICKS(ms)   ((TickType_t)(ms))
#define pdFALSE             0
#define pdTRUE              1
