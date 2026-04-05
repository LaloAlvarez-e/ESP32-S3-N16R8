#include "driver/i2c.h"

i2c_mock_state_t i2c_mock_state = { .cmd_begin_result = ESP_OK };

esp_err_t i2c_param_config(i2c_port_t port, const i2c_config_t *cfg)
{
    if (port < I2C_NUM_MAX && cfg != NULL) {
        i2c_mock_state.configs[port] = *cfg;
    }
    return ESP_OK;
}

esp_err_t i2c_driver_install(i2c_port_t port, i2c_mode_t mode,
                               size_t slv_rx, size_t slv_tx, int flags)
{
    (void)mode; (void)slv_rx; (void)slv_tx; (void)flags;
    if (port < I2C_NUM_MAX) {
        i2c_mock_state.installed[port] = true;
    }
    return ESP_OK;
}

i2c_cmd_handle_t i2c_cmd_link_create(void) { return (void *)1; }
void i2c_cmd_link_delete(i2c_cmd_handle_t cmd) { (void)cmd; }

esp_err_t i2c_master_start(i2c_cmd_handle_t cmd)       { (void)cmd; return ESP_OK; }
esp_err_t i2c_master_stop(i2c_cmd_handle_t cmd)        { (void)cmd; return ESP_OK; }

esp_err_t i2c_master_write_byte(i2c_cmd_handle_t cmd, uint8_t data, bool ack)
{
    (void)cmd; (void)data; (void)ack; return ESP_OK;
}

esp_err_t i2c_master_write(i2c_cmd_handle_t cmd, const uint8_t *data,
                             size_t data_len, bool ack)
{
    (void)cmd; (void)data; (void)data_len; (void)ack; return ESP_OK;
}

esp_err_t i2c_master_read(i2c_cmd_handle_t cmd, uint8_t *data,
                            size_t data_len, i2c_ack_type_t ack)
{
    (void)cmd; (void)data; (void)data_len; (void)ack; return ESP_OK;
}

esp_err_t i2c_master_read_byte(i2c_cmd_handle_t cmd, uint8_t *data,
                                 i2c_ack_type_t ack)
{
    (void)cmd; (void)data; (void)ack; return ESP_OK;
}

esp_err_t i2c_master_cmd_begin(i2c_port_t port, i2c_cmd_handle_t cmd,
                                 uint32_t ticks_to_wait)
{
    (void)port; (void)cmd; (void)ticks_to_wait;
    return i2c_mock_state.cmd_begin_result;
}

esp_err_t i2c_driver_delete(i2c_port_t port)
{
    if (port < I2C_NUM_MAX) {
        i2c_mock_state.installed[port] = false;
    }
    return ESP_OK;
}
