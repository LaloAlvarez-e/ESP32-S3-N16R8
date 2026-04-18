# Status

## State

Completed

## Summary

The installed ESP-IDF VS Code extension can provide the expected VS Code debug experience for ESP32-S3 work: step, next, continue, call stack, variables, watch, disassembly through the standard debug UI, plus the extension's Peripheral View and Hex View. There is no GEL-file concept in this stack. The closest equivalent is the combination of `initCommands`, `preRunCommands`, OpenOCD configuration, and the ESP-IDF extension's register/peripheral integration. The current limitation in this workspace is not a missing VS Code feature; it is that the built-in USB-JTAG link can reenumerate on reset, which makes catching the very earliest `app_main` breakpoint unreliable even though the application can boot and later be debugged.
