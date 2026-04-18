# Request

Integrate the validated ESP-IDF 6.0 installation into this VS Code workspace so ESP32-S3 projects can be built, flashed, and debugged from the root workspace with the normal VS Code debug UI, code references into ESP-IDF headers, and practical guidance for memory, peripheral, register, watch, and disassembly views.

## Current Result

Completed. The root workspace now has explicit compile-database generation, root-level C/C++ configurations for ESP-IDF and shared modules, normalized attach-running and reset-and-load launch names, updated settings and extension recommendations, and refreshed documentation for the supported debug UI and memory windows. The device builds were revalidated successfully after the change.