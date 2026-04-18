# Plan

## Objective

Create a standalone ESP32-S3 hello-world bring-up project, convert the existing sample application into a standalone ESP-IDF project, and add workspace debug and ELF-load tooling.

## Steps

1. [x] Create the request tracker and required files.
2. [x] Add the standalone ESP-IDF project files for `hello_world_project/`.
3. [x] Convert `sample_project/` and the shared common roots for ESP-IDF component use.
4. [x] Add VS Code tasks, launch settings, and helper scripts for build, flash, OpenOCD, and ELF load.
5. [x] Validate the file set and close the tracker.

## Validation

- Root host CMake configure and build succeeded after the ESP-IDF conversion changes.
- Root host CTest run passed with 30 of 30 tests.
- Editor diagnostics for the new ESP-IDF project files, helper scripts, and workspace files were clean.
- Direct ESP-IDF CLI validation was not possible from this terminal because `idf.py`, `openocd`, and `xtensa-esp32s3-elf-gdb` are still not exposed on `PATH`, and the ESP-IDF extension `doctor` command returned an internal tool error in this environment.
