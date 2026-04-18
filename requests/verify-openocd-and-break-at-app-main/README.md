# Request README

## Request

Run the OpenOCD plus VS Code debug path next and verify break-at-`app_main`.

## Current Result

Blocked on the current Windows USB-JTAG access path.

## Details

- `board/esp32s3-builtin.cfg` is the correct repository-side transport for the native ESP32-S3 USB debug interface.
- Windows enumerates the native USB composite device as `USB\\VID_303A&PID_1001`, including `USB JTAG/serial debug unit` and `COM8`.
- OpenOCD fails during USB-JTAG open with `libusb_open() failed with LIBUSB_ERROR_ACCESS`, so the GDB port on `localhost:3333` never becomes available.
- Because the OpenOCD server never reaches a listening state, the configured GDB sequence cannot yet verify the `thb app_main` stop.
