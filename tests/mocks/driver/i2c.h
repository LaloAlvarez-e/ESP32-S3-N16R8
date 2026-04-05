/**
 * @file driver/i2c.h  (mock)
 * @brief Stub I2C types and functions for host-based unit tests.
 */
#pragma once
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "esp_err.h"

typedef enum { I2C_NUM_0 = 0, I2C_NUM_1 = 1, I2C_NUM_MAX = 2 } i2c_port_t;
typedef enum { I2C_MODE_MASTER = 1 } i2c_mode_t;
typedef enum { I2C_MASTER_WRITE = 0, I2C_MASTER_READ = 1 } i2c_rw_t;
typedef enum {
    I2C_MASTER_ACK       = 0x0,
    I2C_MASTER_NACK      = 0x1,
    I2C_MASTER_LAST_NACK = 0x2,
} i2c_ack_type_t;

typedef enum { GPIO_PULLUP_DISABLE = 0, GPIO_PULLUP_ENABLE = 1 } gpio_pullup_t;

typedef struct {
    i2c_mode_t    mode;
    int           sda_io_num;
    int           scl_io_num;
    gpio_pullup_t sda_pullup_en;
    gpio_pullup_t scl_pullup_en;
    union {
        struct { uint32_t clk_speed; } master;
    };
} i2c_config_t;

typedef void *i2c_cmd_handle_t;

/* ---------- Mock state (C-linkage, defined in i2c_mock.c) --------------- */
typedef struct {
    bool        installed[I2C_NUM_MAX];
    i2c_config_t configs[I2C_NUM_MAX];
    esp_err_t   cmd_begin_result;
} i2c_mock_state_t;

#ifdef __cplusplus
extern "C" {
#endif

extern i2c_mock_state_t i2c_mock_state;

esp_err_t        i2c_param_config(i2c_port_t port, const i2c_config_t *cfg);
esp_err_t        i2c_driver_install(i2c_port_t port, i2c_mode_t mode,
                                     size_t slv_rx, size_t slv_tx, int flags);
i2c_cmd_handle_t i2c_cmd_link_create(void);
void             i2c_cmd_link_delete(i2c_cmd_handle_t cmd);
esp_err_t        i2c_master_start(i2c_cmd_handle_t cmd);
esp_err_t        i2c_master_stop(i2c_cmd_handle_t cmd);
esp_err_t        i2c_master_write_byte(i2c_cmd_handle_t cmd, uint8_t data, bool ack);
esp_err_t        i2c_master_write(i2c_cmd_handle_t cmd, const uint8_t *data,
                                   size_t data_len, bool ack);
esp_err_t        i2c_master_read(i2c_cmd_handle_t cmd, uint8_t *data,
                                  size_t data_len, i2c_ack_type_t ack);
esp_err_t        i2c_master_read_byte(i2c_cmd_handle_t cmd, uint8_t *data,
                                       i2c_ack_type_t ack);
esp_err_t        i2c_master_cmd_begin(i2c_port_t port, i2c_cmd_handle_t cmd,
                                       uint32_t ticks_to_wait);
esp_err_t        i2c_driver_delete(i2c_port_t port);

#ifdef __cplusplus
}
#endif
