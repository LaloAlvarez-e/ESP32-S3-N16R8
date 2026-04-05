# ESP32-S3-N16R8 Development Environment

General-purpose learning repository for the **ESP32-S3-N16R8** module
(16 MB Flash / 8 MB Octal-PSRAM).  It implements the five foundational
pillars described in the project brief:

| # | Pillar | Location |
|---|--------|----------|
| 1 | Toolchain integration | `CMakeLists.txt`, `sdkconfig.defaults`, `partitions.csv` |
| 2 | Google Test integration | `tests/` |
| 3 | Driver implementation | `components/drivers/` |
| 4 | Camera setup (ML) | `components/camera/` |
| 5 | Server implementation | `components/http_server/` |

---

## Repository layout

```
ESP32-S3-N16R8/
├── CMakeLists.txt              # ESP-IDF top-level project file
├── sdkconfig.defaults          # Board-specific defaults (16 MB flash, 8 MB PSRAM)
├── partitions.csv              # Custom partition table for 16 MB flash
├── main/
│   ├── CMakeLists.txt
│   ├── Kconfig.projbuild       # WiFi SSID / password / HTTP port (menuconfig)
│   └── main.c                  # Application entry point
├── components/
│   ├── drivers/                # GPIO, UART, I2C, SPI wrappers
│   │   ├── include/
│   │   │   ├── gpio_driver.h
│   │   │   ├── uart_driver.h
│   │   │   ├── i2c_driver.h
│   │   │   └── spi_driver.h
│   │   └── src/
│   │       ├── gpio_driver.c
│   │       ├── uart_driver.c
│   │       ├── i2c_driver.c
│   │       └── spi_driver.c
│   ├── camera/                 # OV2640 camera driver (esp32-camera)
│   │   ├── include/camera_driver.h
│   │   └── src/camera_driver.c
│   └── http_server/            # WiFi STA + HTTP server (capture/stream)
│       ├── include/http_server.h
│       └── src/http_server.c
└── tests/                      # Host-based Google Test suite (no hardware needed)
    ├── CMakeLists.txt
    ├── mocks/                  # Lightweight ESP-IDF HAL stubs
    │   ├── esp_err.h
    │   ├── esp_log.h
    │   ├── freertos/FreeRTOS.h
    │   ├── driver/gpio.h
    │   ├── driver/uart.h
    │   ├── driver/i2c.h
    │   ├── driver/spi_master.h
    │   └── src/                # Mock implementations (C-linkage state)
    │       ├── gpio_mock.c
    │       ├── uart_mock.c
    │       ├── i2c_mock.c
    │       └── spi_mock.c
    └── unit/
        ├── test_gpio_driver.cpp
        ├── test_uart_driver.cpp
        ├── test_i2c_driver.cpp
        ├── test_spi_driver.cpp
        └── test_drivers_main.cpp
```

---

## 1. Toolchain setup (ESP-IDF)

### Prerequisites

| Tool | Version |
|------|---------|
| [ESP-IDF](https://docs.espressif.com/projects/esp-idf/en/stable/esp32s3/get-started/) | ≥ 5.1 |
| CMake | ≥ 3.16 |
| Python | ≥ 3.8 |

### Install ESP-IDF

```bash
git clone --recursive https://github.com/espressif/esp-idf.git ~/esp/esp-idf
cd ~/esp/esp-idf
./install.sh esp32s3
. ./export.sh          # or `. export.fish` for fish shell
```

### Configure WiFi credentials (menuconfig)

```bash
idf.py menuconfig
# Navigate to: ESP32-S3-N16R8 Application → WiFi Configuration
```

Or set them directly:

```bash
idf.py -DCONFIG_APP_WIFI_SSID="MyNetwork" \
        -DCONFIG_APP_WIFI_PASSWORD="MyPassword" \
        menuconfig
```

### Build & flash

```bash
idf.py set-target esp32s3
idf.py build
idf.py -p /dev/ttyUSB0 flash monitor
```

The board will:
1. Initialise GPIO, UART, I2C, SPI drivers.
2. Attempt to initialise the camera (logs a warning if no sensor is detected).
3. Connect to WiFi and start the HTTP server.
4. Blink the status LED every 500 ms.

### HTTP endpoints

| URL | Description |
|-----|-------------|
| `GET /` | Status page with links |
| `GET /capture` | Single JPEG frame |
| `GET /stream` | MJPEG live stream |

---

## 2. Google Test (host-based unit tests)

Tests run entirely on the development machine — no ESP32 hardware needed.

### Prerequisites

| Tool | Notes |
|------|-------|
| CMake ≥ 3.14 | |
| GCC / Clang with C++17 | |
| Internet access | GoogleTest v1.14.0 is fetched automatically on first run |

### Build & run

```bash
cd tests
cmake -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
ctest --test-dir build --output-on-failure
```

Expected output:

```
100% tests passed, 0 tests failed out of 51
```

### Test coverage

| Suite | Tests | Drivers exercised |
|-------|-------|-------------------|
| `GpioDriverTest` | 12 | gpio_driver |
| `UartDriverTest` | 13 | uart_driver |
| `I2cDriverTest`  | 14 | i2c_driver |
| `SpiDriverTest`  | 12 | spi_driver |

### Mock architecture

Each ESP-IDF HAL header (`driver/gpio.h`, etc.) is replaced by a
lightweight stub in `tests/mocks/`.  A companion `*_mock.c` file
(compiled into the test binary alongside the real driver sources)
provides the C-linkage function bodies that update a plain C state
struct (`gpio_mock_state_t`, etc.).  Tests inspect that struct to
verify driver behaviour without touching real hardware.

---

## 3. Driver implementation

All drivers follow the same pattern:

```c
// 1. Fill a config struct
gpio_driver_config_t cfg = {
    .pin       = GPIO_NUM_2,
    .mode      = GPIO_MODE_OUTPUT,
    .pull_up   = false,
    .pull_down = false,
};

// 2. Init
ESP_ERROR_CHECK(gpio_driver_init(&cfg));

// 3. Use
gpio_driver_set_level(&cfg, true);

// 4. Deinit when done
gpio_driver_deinit(&cfg);
```

| Driver | Header | Key functions |
|--------|--------|---------------|
| GPIO   | `gpio_driver.h` | `init`, `set_level`, `get_level`, `deinit` |
| UART   | `uart_driver.h` | `init`, `write`, `read`, `deinit` |
| I2C    | `i2c_driver.h`  | `init`, `write`, `read`, `write_read`, `deinit` |
| SPI    | `spi_driver.h`  | `init`, `transfer` (full-duplex), `deinit` |

---

## 4. Camera setup (OV2640 — Machine Learning)

The camera component wraps Espressif's
[`esp32-camera`](https://github.com/espressif/esp32-camera) component.

```c
camera_config_t cfg = CAMERA_DEFAULT_CONFIG();
// Override any pin for your specific module:
// cfg.pin_pwdn = -1;  // if PWDN tied to GND

ESP_ERROR_CHECK(camera_driver_init(&cfg));

// Capture a JPEG frame
camera_fb_t *fb = camera_driver_capture();
if (fb) {
    // fb->buf  — JPEG data
    // fb->len  — byte count
    // fb->width / fb->height
    camera_driver_return_fb(fb);   // MUST return to free the buffer
}

camera_driver_deinit();
```

**`CAMERA_DEFAULT_CONFIG()`** maps the AI-Thinker / M5Stack-CAM pin layout.
Adjust the pin numbers in `camera_driver.h` for other modules.

Frame buffers are allocated from **PSRAM** (`CAMERA_FB_IN_PSRAM`) so the
8 MB on the N16R8 module is fully utilised.

For Machine-Learning inference, pair captured frames with
[ESP-DL](https://github.com/espressif/esp-dl) or
[TensorFlow Lite for Microcontrollers](https://github.com/tensorflow/tflite-micro).

---

## 5. Server implementation

The `http_server` component initialises WiFi (station mode) and registers
three HTTP handlers.

```c
http_server_config_t srv = HTTP_SERVER_DEFAULT_CONFIG();
// srv.ssid / srv.password / srv.port come from Kconfig defaults
ESP_ERROR_CHECK(http_server_start(&srv));
```

To stop:

```c
http_server_stop();
```

The MJPEG stream at `/stream` is suitable for viewing live camera output
in a browser or sending frames to a remote ML inference service.

---

## Partition table

`partitions.csv` configures the 16 MB flash for OTA support:

| Partition | Size | Purpose |
|-----------|------|---------|
| `nvs`     | 24 KB | Non-volatile storage |
| `phy_init`| 4 KB | PHY calibration data |
| `factory` | 3 MB | Factory firmware |
| `ota_0`   | 3 MB | OTA slot A |
| `ota_1`   | 3 MB | OTA slot B |
| `ota_data`| 8 KB | Active OTA slot record |
| `storage` | ~7 MB | SPIFFS user storage |

---

## Contributing

1. Fork the repository.
2. Create a feature branch: `git checkout -b feature/my-feature`.
3. Add or update unit tests in `tests/unit/`.
4. Verify all tests pass: `cd tests && cmake -B build && cmake --build build && ctest --test-dir build`.
5. Open a pull request.

---

## License

This project is released under the **MIT License**.
