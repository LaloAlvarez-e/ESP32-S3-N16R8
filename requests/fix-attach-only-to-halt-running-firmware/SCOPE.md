# Scope

## In Scope

- Make the VS Code attach-only flow halt the current firmware state instead of waiting on `app_main`.
- Keep the change aligned with the existing ESP-IDF `gdbtarget` workflow.
- Validate the practical attach path for delivery-oriented debugging.

## Out of Scope

- Solving reset-time breakpoint retention on the ESP32-S3 built-in USB-JTAG path.
- Replacing the ESP-IDF extension or OpenOCD stack.
