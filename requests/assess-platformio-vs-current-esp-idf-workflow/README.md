# Request

Assess whether switching this repository from the current ESP-IDF plus VS Code workflow to PlatformIO would likely improve the user's build and debug experience.

## Outcome

Assessment completed. PlatformIO is installed locally and can build ESP-IDF projects, but this repository currently has no PlatformIO project files. The current device-side projects already use standard ESP-IDF CMake structure, so migration is possible, but the main current blocker is the debug transport and VS Code handoff around OpenOCD and GDB. PlatformIO would still rely on the same underlying ESP32 debug tooling for that layer. For this repository, PlatformIO is more attractive as a future wrapper for build, upload, and board selection than as an immediate fix for the current debug issue.
