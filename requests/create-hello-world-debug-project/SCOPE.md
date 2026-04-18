# Scope

## In Scope

- Add a standalone ESP-IDF hello-world project for ESP32-S3 bring-up.
- Convert `sample_project/` into a standalone ESP-IDF project when opened directly.
- Keep the root host-side CMake and GoogleTest workflow intact.
- Add workspace debug and ELF-load tooling around OpenOCD and GDB.

## Out of Scope

- Building or flashing the device from this environment without a configured ESP-IDF CLI toolchain.
- Rewriting the production module implementations beyond project and toolchain integration.
- Creating device-side tests.

## Delivered

- Added `hello_world_project/` as a standalone ESP32-S3 ESP-IDF bring-up and debug project.
- Converted `sample_project/` into a standalone ESP-IDF project when opened directly.
- Made `common_utils/`, `common_os/`, and `common_driver/` usable as shared ESP-IDF components while preserving the host-side CMake flow.
- Added workspace `.vscode` settings, tasks, launch configurations, and helper scripts for build, flash, monitor, OpenOCD, and ELF load.
