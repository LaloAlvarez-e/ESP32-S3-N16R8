# Request

Add a practical hello world startup hold for the VS Code debug path so the ESP32-S3 built-in USB-JTAG reset and reenumeration sequence does not run past early application code before the debugger can attach.

## Outcome

The hello world project now supports a build-time startup hold controlled by the workspace setting `esp32Project.helloWorldDebugStartupHoldMs`. The normal build path explicitly sets the hold to `0`, while the hello world debug-prepare path builds with the configured hold value before starting OpenOCD. This gives VS Code a usable attach window after reset without forcing the delay into normal builds.
