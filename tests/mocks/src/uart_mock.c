#include "driver/uart.h"

uart_mock_state_t uart_mock_state = {0};

esp_err_t uart_param_config(uart_port_t port, const uart_config_t *cfg)
{
    if (port < UART_NUM_MAX && cfg != NULL) {
        uart_mock_state.configs[port] = *cfg;
    }
    return ESP_OK;
}

esp_err_t uart_set_pin(uart_port_t port, int tx, int rx, int rts, int cts)
{
    (void)port; (void)tx; (void)rx; (void)rts; (void)cts;
    return ESP_OK;
}

esp_err_t uart_driver_install(uart_port_t port, int rx_buf, int tx_buf,
                               int queue_size, void *queue, int flags)
{
    (void)rx_buf; (void)tx_buf; (void)queue_size; (void)queue; (void)flags;
    if (port < UART_NUM_MAX) {
        uart_mock_state.installed[port] = true;
    }
    return ESP_OK;
}

int uart_write_bytes(uart_port_t port, const char *src, size_t size)
{
    (void)port; (void)src;
    return (int)size;
}

int uart_read_bytes(uart_port_t port, void *buf, uint32_t len, uint32_t ticks)
{
    (void)port; (void)buf; (void)ticks;
    return (int)len;
}

esp_err_t uart_driver_delete(uart_port_t port)
{
    if (port < UART_NUM_MAX) {
        uart_mock_state.installed[port] = false;
    }
    return ESP_OK;
}
