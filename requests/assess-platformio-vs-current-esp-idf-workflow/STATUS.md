# Status

## State

Completed

## Summary

PlatformIO IDE is installed and PlatformIO Core 6.1.19 is available from the bundled user environment. The repository does not currently contain any `platformio.ini` files or PlatformIO-specific documentation. The device projects already follow ESP-IDF CMake structure closely enough that migration is feasible, and PlatformIO has nearby ESP32-S3 board definitions, including generic DevKitC and at least one R8N16-specific board entry. However, the current blocker is the debug attach path around OpenOCD, GDB, and VS Code handoff. PlatformIO would still rely on the same underlying debug stack for ESP32, so it is unlikely to be an immediate fix for the current failure mode. It is a reasonable future simplification layer, but not the highest-value next move if the goal is to unblock debugging quickly.
