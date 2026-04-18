# Status

## State

Blocked

## Summary

The repository launch sequence is configured for a break at `app_main`, but live verification is currently blocked on the host machine. OpenOCD finds the ESP32-S3 native USB debug device and then fails with `libusb_open() failed with LIBUSB_ERROR_ACCESS`, so no GDB listener is created on `localhost:3333`.
