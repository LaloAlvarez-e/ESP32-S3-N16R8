# Status

## State

Completed

## Summary

Windows currently shows the ESP32-S3 native USB device as a composite device with `MI_00` on Microsoft `usbser.inf` for the COM port and `MI_02` on `WinUSB` via libwdi INF `oem108.inf` for the USB JTAG interface. The driver assignment is compatible with OpenOCD in principle, so the remaining `LIBUSB_ERROR_ACCESS` failure is not explained by a missing WinUSB binding.