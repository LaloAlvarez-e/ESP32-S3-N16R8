# Progress Update

## Completed Work

- Added `ESP32: Prepare Hello World Live Attach`, `ESP32: Prepare Sample Project Live Attach`, and `ESP32: Prepare Custom Project Live Attach`.
- Replaced the previous attach-only launch profiles with `Attach Running Firmware` profiles.
- Removed `initialBreakpoint` from those profiles.
- Added `monitor halt` to the attach-running init command sequence.
- Explicitly set `initialBreakpoint` to an empty string after confirming that the ESP-IDF extension auto-injects `thb app_main` when the field is undefined.
- Renamed the hello world late-attach profile to `ESP32S3: Hello World (Recommended Attach Running Firmware)` and made it the first visible hello world launch entry so F5 is less likely to choose the reset-and-load path by mistake.
- Updated the README to describe the late-attach workflow as the practical delivery path.
- Validated the new GDB sequence against a live OpenOCD server.

## Result

The attach-running path now gives VS Code a debuggable paused state even when trapping `app_main` during reset is unreliable on the built-in USB-JTAG transport.
