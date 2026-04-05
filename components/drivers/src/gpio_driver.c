#include <stdbool.h>
#include "gpio_driver.h"
#include "esp_log.h"

static const char *TAG = "gpio_driver";

esp_err_t gpio_driver_init(const gpio_driver_config_t *cfg)
{
    if (cfg == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << cfg->pin),
        .mode         = cfg->mode,
        .pull_up_en   = cfg->pull_up   ? GPIO_PULLUP_ENABLE   : GPIO_PULLUP_DISABLE,
        .pull_down_en = cfg->pull_down ? GPIO_PULLDOWN_ENABLE : GPIO_PULLDOWN_DISABLE,
        .intr_type    = GPIO_INTR_DISABLE,
    };

    esp_err_t ret = gpio_config(&io_conf);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "gpio_config failed for pin %d: 0x%x", cfg->pin, ret);
    } else {
        ESP_LOGD(TAG, "GPIO %d initialised (mode=%d)", cfg->pin, cfg->mode);
    }
    return ret;
}

esp_err_t gpio_driver_set_level(const gpio_driver_config_t *cfg, bool level)
{
    if (cfg == NULL) {
        return ESP_ERR_INVALID_ARG;
    }
    return gpio_set_level(cfg->pin, level ? 1 : 0);
}

int gpio_driver_get_level(const gpio_driver_config_t *cfg)
{
    if (cfg == NULL) {
        return -1;
    }
    return gpio_get_level(cfg->pin);
}

esp_err_t gpio_driver_deinit(const gpio_driver_config_t *cfg)
{
    if (cfg == NULL) {
        return ESP_ERR_INVALID_ARG;
    }
    esp_err_t ret = gpio_reset_pin(cfg->pin);
    if (ret == ESP_OK) {
        ESP_LOGD(TAG, "GPIO %d de-initialised", cfg->pin);
    }
    return ret;
}
