# Progress Entry

## Overview

Added device-side ESP-IDF project files and workspace debug tooling for ESP32-S3 development.

## Work Performed

- Added `hello_world_project/` as a new standalone ESP-IDF project with a simple `app_main` bring-up application.
- Converted `sample_project/` into a standalone ESP-IDF project when opened directly.
- Converted `common_utils/`, `common_os/`, and `common_driver/` to dual-purpose CMake files that work as either host libraries or ESP-IDF components.
- Added `.vscode/settings.json`, `.vscode/tasks.json`, `.vscode/launch.json`, and `.vscode/extensions.json`.
- Added helper scripts under `tools/esp32/` for `idf.py`, OpenOCD, and ELF load workflows.
- Updated repository documentation and ignore rules for nested ESP-IDF build output.

## Validation Result

- Root host configure/build succeeded after the ESP-IDF changes.
- Root host CTest run passed with 30 of 30 tests.
- Editor diagnostics for the new project files and scripts were clean.
- Direct device-side CLI validation is still pending because the ESP-IDF executables are not available on `PATH` in this terminal and the ESP-IDF extension `doctor` tool call failed internally.
