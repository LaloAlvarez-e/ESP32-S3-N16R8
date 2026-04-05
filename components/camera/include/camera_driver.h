/**
 * @file camera_driver.h
 * @brief Camera driver for machine-learning applications on ESP32-S3-N16R8.
 *
 * Wraps the Espressif `esp32-camera` component and provides helper macros for
 * the default OV2640 pin mapping used by common AI-Thinker / M5Stack camera
 * modules.  Other sensors (OV5640, GC2145, …) can be swapped in by changing
 * `camera_config_t::pixel_format` / `camera_config_t::frame_size`.
 *
 * Usage:
 * @code
 *   camera_config_t cfg = CAMERA_DEFAULT_CONFIG();
 *   ESP_ERROR_CHECK(camera_driver_init(&cfg));
 *
 *   camera_fb_t *fb = camera_driver_capture();
 *   if (fb) {
 *       // use fb->buf, fb->len
 *       camera_driver_return_fb(fb);
 *   }
 *   camera_driver_deinit();
 * @endcode
 */
#pragma once

#include "esp_err.h"
#include "esp_camera.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Default OV2640 pin-map for the AI-Thinker ESP32-CAM / ESP32-S3-CAM
 *        module.  Override individual fields after expanding the macro.
 *
 * Pin assignments (adjust to match your PCB):
 *   PWDN   GPIO_NUM_32   (or -1 if tied to GND)
 *   RESET  GPIO_NUM_-1   (hardware reset, or -1 if not connected)
 *   XCLK   GPIO_NUM_0
 *   SIOD   GPIO_NUM_26   (I2C SDA)
 *   SIOC   GPIO_NUM_27   (I2C SCL)
 *   D7…D0  GPIO_NUM_35,34,39,38,37,36,21,19
 *   VSYNC  GPIO_NUM_25
 *   HREF   GPIO_NUM_23
 *   PCLK   GPIO_NUM_22
 */
#define CAMERA_DEFAULT_CONFIG()  {                          \
    .pin_pwdn    =  32,                                     \
    .pin_reset   =  -1,                                     \
    .pin_xclk    =   0,                                     \
    .pin_sscb_sda = 26,                                     \
    .pin_sscb_scl = 27,                                     \
    .pin_d7      =  35,                                     \
    .pin_d6      =  34,                                     \
    .pin_d5      =  39,                                     \
    .pin_d4      =  38,                                     \
    .pin_d3      =  37,                                     \
    .pin_d2      =  36,                                     \
    .pin_d1      =  21,                                     \
    .pin_d0      =  19,                                     \
    .pin_vsync   =  25,                                     \
    .pin_href    =  23,                                     \
    .pin_pclk    =  22,                                     \
    .xclk_freq_hz = 20000000,                               \
    .ledc_timer   = LEDC_TIMER_0,                           \
    .ledc_channel = LEDC_CHANNEL_0,                         \
    .pixel_format = PIXFORMAT_JPEG,                         \
    .frame_size   = FRAMESIZE_QVGA,                         \
    .jpeg_quality = 12,                                     \
    .fb_count     = 2,                                      \
    .fb_location  = CAMERA_FB_IN_PSRAM,                     \
    .grab_mode    = CAMERA_GRAB_WHEN_EMPTY,                 \
}

/**
 * @brief  Initialise the camera sensor.
 * @param  cfg  Camera configuration (use CAMERA_DEFAULT_CONFIG() as a base).
 * @return ESP_OK, or an ESP-IDF error code if the sensor is not detected.
 */
esp_err_t camera_driver_init(const camera_config_t *cfg);

/**
 * @brief  Capture a single frame.
 * @return Pointer to a `camera_fb_t` frame buffer, or NULL on failure.
 *         Caller **must** release the buffer with camera_driver_return_fb().
 */
camera_fb_t *camera_driver_capture(void);

/**
 * @brief  Return a previously captured frame buffer to the driver.
 * @param  fb  Frame buffer obtained from camera_driver_capture().
 */
void camera_driver_return_fb(camera_fb_t *fb);

/**
 * @brief  De-initialise the camera and release all resources.
 * @return ESP_OK on success.
 */
esp_err_t camera_driver_deinit(void);

#ifdef __cplusplus
}
#endif
