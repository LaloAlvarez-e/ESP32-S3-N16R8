#include "driver/gpio.h"
#include <string.h>

gpio_mock_state_t gpio_mock_state = {0};

esp_err_t gpio_config(const gpio_config_t *cfg)
{
    if (cfg == NULL) return ESP_ERR_INVALID_ARG;
    gpio_mock_state.config_called = true;
    for (int i = 0; i < GPIO_NUM_MAX; i++) {
        if (cfg->pin_bit_mask & (1ULL << i)) {
            gpio_mock_state.configs[i] = *cfg;
        }
    }
    return ESP_OK;
}

esp_err_t gpio_set_level(gpio_num_t gpio_num, uint32_t level)
{
    if (gpio_num >= 0 && gpio_num < GPIO_NUM_MAX) {
        gpio_mock_state.levels[gpio_num] = (int)level;
    }
    return ESP_OK;
}

int gpio_get_level(gpio_num_t gpio_num)
{
    if (gpio_num >= 0 && gpio_num < GPIO_NUM_MAX) {
        return gpio_mock_state.levels[gpio_num];
    }
    return 0;
}

esp_err_t gpio_reset_pin(gpio_num_t gpio_num)
{
    if (gpio_num >= 0 && gpio_num < GPIO_NUM_MAX) {
        gpio_mock_state.levels[gpio_num] = 0;
        memset(&gpio_mock_state.configs[gpio_num], 0, sizeof(gpio_config_t));
    }
    return ESP_OK;
}
