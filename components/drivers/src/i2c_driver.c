#include <stdbool.h>
#include "freertos/FreeRTOS.h"
#include "i2c_driver.h"
#include "esp_log.h"

#define I2C_MASTER_TIMEOUT_MS 1000

static const char *TAG = "i2c_driver";

esp_err_t i2c_driver_init(const i2c_driver_config_t *cfg)
{
    if (cfg == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    i2c_config_t i2c_cfg = {
        .mode             = I2C_MODE_MASTER,
        .sda_io_num       = cfg->sda_pin,
        .scl_io_num       = cfg->scl_pin,
        .sda_pullup_en    = cfg->pullup ? GPIO_PULLUP_ENABLE : GPIO_PULLUP_DISABLE,
        .scl_pullup_en    = cfg->pullup ? GPIO_PULLUP_ENABLE : GPIO_PULLUP_DISABLE,
        .master.clk_speed = cfg->clk_hz,
    };

    esp_err_t ret = i2c_param_config(cfg->port, &i2c_cfg);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "i2c_param_config failed: 0x%x", ret);
        return ret;
    }

    ret = i2c_driver_install(cfg->port, I2C_MODE_MASTER, 0, 0, 0);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "i2c_driver_install failed: 0x%x", ret);
        return ret;
    }

    ESP_LOGD(TAG, "I2C%d initialised at %lu Hz (sda=%d scl=%d)",
             cfg->port, (unsigned long)cfg->clk_hz, cfg->sda_pin, cfg->scl_pin);
    return ESP_OK;
}

esp_err_t i2c_driver_write(const i2c_driver_config_t *cfg,
                            uint8_t dev_addr,
                            const uint8_t *data, size_t len)
{
    if (cfg == NULL || data == NULL || len == 0) {
        return ESP_ERR_INVALID_ARG;
    }

    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (dev_addr << 1) | I2C_MASTER_WRITE, true);
    i2c_master_write(cmd, data, len, true);
    i2c_master_stop(cmd);

    esp_err_t ret = i2c_master_cmd_begin(cfg->port, cmd,
                                          pdMS_TO_TICKS(I2C_MASTER_TIMEOUT_MS));
    i2c_cmd_link_delete(cmd);
    return ret;
}

esp_err_t i2c_driver_read(const i2c_driver_config_t *cfg,
                           uint8_t dev_addr,
                           uint8_t *buf, size_t len)
{
    if (cfg == NULL || buf == NULL || len == 0) {
        return ESP_ERR_INVALID_ARG;
    }

    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (dev_addr << 1) | I2C_MASTER_READ, true);
    if (len > 1) {
        i2c_master_read(cmd, buf, len - 1, I2C_MASTER_ACK);
    }
    i2c_master_read_byte(cmd, buf + len - 1, I2C_MASTER_NACK);
    i2c_master_stop(cmd);

    esp_err_t ret = i2c_master_cmd_begin(cfg->port, cmd,
                                          pdMS_TO_TICKS(I2C_MASTER_TIMEOUT_MS));
    i2c_cmd_link_delete(cmd);
    return ret;
}

esp_err_t i2c_driver_write_read(const i2c_driver_config_t *cfg,
                                 uint8_t dev_addr,
                                 const uint8_t *write_buf, size_t write_len,
                                 uint8_t *read_buf,  size_t read_len)
{
    if (cfg == NULL || write_buf == NULL || read_buf == NULL
        || write_len == 0 || read_len == 0) {
        return ESP_ERR_INVALID_ARG;
    }

    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    /* Write phase */
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (dev_addr << 1) | I2C_MASTER_WRITE, true);
    i2c_master_write(cmd, write_buf, write_len, true);
    /* Read phase (repeated start) */
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (dev_addr << 1) | I2C_MASTER_READ, true);
    if (read_len > 1) {
        i2c_master_read(cmd, read_buf, read_len - 1, I2C_MASTER_ACK);
    }
    i2c_master_read_byte(cmd, read_buf + read_len - 1, I2C_MASTER_NACK);
    i2c_master_stop(cmd);

    esp_err_t ret = i2c_master_cmd_begin(cfg->port, cmd,
                                          pdMS_TO_TICKS(I2C_MASTER_TIMEOUT_MS));
    i2c_cmd_link_delete(cmd);
    return ret;
}

esp_err_t i2c_driver_deinit(const i2c_driver_config_t *cfg)
{
    if (cfg == NULL) {
        return ESP_ERR_INVALID_ARG;
    }
    esp_err_t ret = i2c_driver_delete(cfg->port);
    if (ret == ESP_OK) {
        ESP_LOGD(TAG, "I2C%d de-initialised", cfg->port);
    }
    return ret;
}
