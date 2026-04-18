# Request

Fix the VS Code F5 debug startup error, add a permanent named future-project debug profile template, and keep improving the reliability of the visual ESP32 debug flow.

## Outcome

The workspace no longer relies on `cppdbg` for the visual ESP32 debug configurations. Instead it now uses the ESP-IDF extension's native `gdbtarget` adapter, includes a permanent copy-and-rename template profile, and documents the recommended attach-only path for better live-session stability. The latest refinement also makes the root-workspace launch flow quieter and more IDE-like by using the native `extended-remote` target form and keeping the OpenOCD startup task from taking over the terminal focus.