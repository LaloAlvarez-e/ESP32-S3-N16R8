#include "camera_driver.h"
#include "esp_log.h"

static const char *TAG = "camera_driver";

esp_err_t camera_driver_init(const camera_config_t *cfg)
{
    if (cfg == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    esp_err_t ret = esp_camera_init(cfg);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "esp_camera_init failed: 0x%x", ret);
        return ret;
    }

    /* Log sensor information */
    sensor_t *sensor = esp_camera_sensor_get();
    if (sensor != NULL) {
        ESP_LOGI(TAG, "Camera sensor detected: PID=0x%04x", sensor->id.PID);

        /* Tune OV2640 for better image quality */
        if (sensor->id.PID == 0x2642) {  /* OV2640 */
            sensor->set_brightness(sensor, 0);
            sensor->set_contrast(sensor, 0);
            sensor->set_saturation(sensor, 0);
            sensor->set_whitebal(sensor, 1);   /* auto white balance   */
            sensor->set_exposure_ctrl(sensor, 1); /* auto exposure     */
            sensor->set_gain_ctrl(sensor, 1);     /* auto gain         */
            sensor->set_hmirror(sensor, 0);
            sensor->set_vflip(sensor, 0);
        }
    }

    ESP_LOGI(TAG, "Camera driver initialised (format=%d, size=%d)",
             cfg->pixel_format, cfg->frame_size);
    return ESP_OK;
}

camera_fb_t *camera_driver_capture(void)
{
    camera_fb_t *fb = esp_camera_fb_get();
    if (fb == NULL) {
        ESP_LOGE(TAG, "Failed to capture frame");
    } else {
        ESP_LOGD(TAG, "Frame captured: %zu bytes", fb->len);
    }
    return fb;
}

void camera_driver_return_fb(camera_fb_t *fb)
{
    if (fb != NULL) {
        esp_camera_fb_return(fb);
    }
}

esp_err_t camera_driver_deinit(void)
{
    esp_err_t ret = esp_camera_deinit();
    if (ret == ESP_OK) {
        ESP_LOGD(TAG, "Camera driver de-initialised");
    }
    return ret;
}
