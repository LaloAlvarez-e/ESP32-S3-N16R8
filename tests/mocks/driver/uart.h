/**
 * @file driver/uart.h  (mock)
 * @brief Stub UART types and functions for host-based unit tests.
 */
#pragma once
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "esp_err.h"

typedef enum { UART_NUM_0 = 0, UART_NUM_1 = 1, UART_NUM_2 = 2, UART_NUM_MAX = 3 } uart_port_t;
typedef enum { UART_DATA_8_BITS = 3 } uart_word_length_t;
typedef enum { UART_PARITY_DISABLE = 0 } uart_parity_t;
typedef enum { UART_STOP_BITS_1 = 1 } uart_stop_bits_t;
typedef enum { UART_HW_FLOWCTRL_DISABLE = 0 } uart_hw_flowcontrol_t;
typedef enum { UART_SCLK_DEFAULT = 0 } uart_sclk_t;

#define UART_PIN_NO_CHANGE (-1)

typedef struct {
    int                    baud_rate;
    uart_word_length_t     data_bits;
    uart_parity_t          parity;
    uart_stop_bits_t       stop_bits;
    uart_hw_flowcontrol_t  flow_ctrl;
    uart_sclk_t            source_clk;
} uart_config_t;

/* ---------- Mock state (C-linkage, defined in uart_mock.c) --------------- */
typedef struct {
    bool        installed[UART_NUM_MAX];
    uart_config_t configs[UART_NUM_MAX];
} uart_mock_state_t;

#ifdef __cplusplus
extern "C" {
#endif

extern uart_mock_state_t uart_mock_state;

esp_err_t uart_param_config(uart_port_t port, const uart_config_t *cfg);
esp_err_t uart_set_pin(uart_port_t port, int tx, int rx, int rts, int cts);
esp_err_t uart_driver_install(uart_port_t port, int rx_buf, int tx_buf,
                               int queue_size, void *queue, int flags);
int       uart_write_bytes(uart_port_t port, const char *src, size_t size);
int       uart_read_bytes(uart_port_t port, void *buf, uint32_t len, uint32_t ticks);
esp_err_t uart_driver_delete(uart_port_t port);

#ifdef __cplusplus
}
#endif
