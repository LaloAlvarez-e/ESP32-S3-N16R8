# Scope

## In Scope

- Root-workspace VS Code integration for ESP-IDF 6.0 at `C:\esp\v6.0\esp-idf`.
- ESP32-S3 build, flash, monitor, and visual debug workflow through this workspace.
- Launch profiles for both attach-running and reset-and-load debug rules.
- Root-workspace header resolution and IntelliSense for ESP-IDF and the repository shared components.
- Documentation of supported debug views, memory windows, and practical limitations.

## Out of Scope

- Replacing the ESP-IDF extension, OpenOCD, or GDB with another debugger backend.
- Fixing host USB-JTAG driver or hardware reenumeration behavior beyond documenting the observed limitation.
- Refactoring unrelated firmware modules or host-side tests.