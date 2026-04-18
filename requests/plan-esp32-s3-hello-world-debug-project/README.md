# Request README

## Request

Review the repository and define a concrete implementation plan for adding a minimal ESP-IDF hello-world debug project for ESP32-S3-N16R8, including build, flash or ELF load, and VS Code debugging support.

## Current Result

Completed. The repository review is finished and a concrete file-level plan is documented for a dedicated `esp32s3_hello_world/` device-side project, Windows helper scripts, and VS Code build and debug wiring.

## Validation

- Confirmed the repository currently contains host-side CMake libraries and tests only.
- Confirmed there are no ESP-IDF project files, `sdkconfig.defaults`, or `.vscode/` debug artifacts yet.
- Planned tool flow uses explicit `idf.py`, `openocd.exe`, and `xtensa-esp32s3-elf-gdb.exe` locations instead of relying on PATH discovery.
