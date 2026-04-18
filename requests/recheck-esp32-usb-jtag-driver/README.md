# Request

Recheck the current Windows driver binding for the ESP32-S3 USB JTAG and serial interfaces to confirm why OpenOCD access is failing.

## Outcome

The USB JTAG interface is already on `WinUSB`, and the COM interface is on `usbser`. The current OpenOCD block therefore points to host-side USB access or contention rather than an obviously wrong driver choice.