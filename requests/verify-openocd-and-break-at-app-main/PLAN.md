# Plan

## Objective

Run the OpenOCD plus GDB debug path for the hello world ESP32-S3 project and verify that execution stops at `app_main`.

## Steps

1. Create the request tracker files.
2. Start OpenOCD with the configured repository wrapper and confirm that it exposes the GDB listener on `localhost:3333`.
3. If OpenOCD fails, capture the failure signature and identify whether the blocker is configuration, transport selection, or host USB access.
4. Connect GDB to the target with the built hello-world ELF.
5. Reset, halt, set a breakpoint at `app_main`, and verify the stop location.
6. Record the outcome and update the tracker.

## Current Result

OpenOCD was launched with the repository wrapper and failed before opening the GDB listener. The current blocker is host-side USB-JTAG access on Windows: `libusb_open()` failed with `LIBUSB_ERROR_ACCESS` for the ESP32-S3 USB-JTAG interface (`USB\\VID_303A&PID_1001&MI_02`).
