# Request README

## Request

Create a hello-world debug project and configure the repository so the project folders can be used as ESP32 projects with ELF load and GDB debugging support.

## Current Result

Completed. The repository now contains standalone ESP-IDF project scaffolding, shared component-compatible CMake files, and workspace build/debug helper files.

## Validation

- Root host configure/build: passed.
- Root host tests: 30 of 30 passed.
- ESP-IDF project and script diagnostics: clean.
- Direct ESP-IDF CLI validation: not completed from this terminal because the ESP-IDF executables are not on `PATH`, and the ESP-IDF extension `doctor` tool call returned an internal error.
