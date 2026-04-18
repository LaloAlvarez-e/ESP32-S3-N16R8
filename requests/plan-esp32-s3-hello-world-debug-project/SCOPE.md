# Scope

## In Scope

- Repository review for current build and project layout.
- Concrete recommendation for a new ESP-IDF hello-world debug project folder.
- Exact artifact list for project files, helper scripts, and VS Code configuration.
- Practical Windows debug and ELF-load flow for ESP32-S3 using standard ESP-IDF tooling.
- Key caveats about OpenOCD selection, ELF handling, and tool path parameterization.

## Out of Scope

- Implementing the ESP-IDF project files in this request.
- Local build, flash, or GDB validation, because required ESP-IDF tools are not available on PATH in the current environment.
- Board-specific JTAG pinout or hardware wiring changes beyond standard ESP32-S3 conventions.
