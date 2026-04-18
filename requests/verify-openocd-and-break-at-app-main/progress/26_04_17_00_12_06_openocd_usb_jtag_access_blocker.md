# Progress Entry

## Overview

Attempted the live OpenOCD plus GDB verification for the hello world ESP32-S3 target and isolated the current blocker to host-side USB-JTAG access on Windows.

## Actions Performed

- Confirmed that the repository debug launch sequence is logically correct for break-at-`app_main`: `target remote localhost:3333`, `monitor reset halt`, `load`, `thb app_main`, `exec-continue`.
- Started OpenOCD with the repository wrapper against `board/esp32s3-builtin.cfg`.
- Observed the initial OpenOCD failure: `esp_usb_jtag: could not find or open device!`.
- Verified that no process was listening on TCP port `3333` after the failure.
- Enumerated connected devices on Windows and confirmed that the ESP32-S3 native USB debug interface is present as `USB JTAG/serial debug unit` plus `COM8` under `USB\\VID_303A&PID_1001`.
- Inspected the bound driver and confirmed that the JTAG interface is using `WinUSB` via `usb_jtag_debug_unit.inf`.
- Re-ran OpenOCD with verbose logging and captured the decisive failure: `libusb_open() failed with LIBUSB_ERROR_ACCESS`.

## Result

The repository-side debug configuration is ready for a break at `app_main`, but live verification is blocked until the host can open the ESP32-S3 USB-JTAG interface successfully.

## Next Step

Fix the Windows USB-JTAG access issue for interface `USB\\VID_303A&PID_1001&MI_02`, then rerun OpenOCD and the configured GDB attach flow.