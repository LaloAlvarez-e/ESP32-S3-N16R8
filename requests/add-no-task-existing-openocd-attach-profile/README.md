# Request

Add a hello world launch profile that connects to an already running OpenOCD server without any `preLaunchTask`, so VS Code can try a direct GDB attach when the task-to-debug handoff is failing.

## Outcome

A new launch profile, `ESP32S3: Hello World (Connect To Existing OpenOCD)`, was added to `.vscode/launch.json`. It reuses the validated late-attach GDB settings, explicitly suppresses the ESP-IDF extension's hidden `app_main` breakpoint injection with `initialBreakpoint: ""`, and opens the GDB console for visibility. `README.md` now documents the two-step fallback flow: start `ESP32: OpenOCD Server`, wait for port `3333`, then launch the no-task attach profile. A follow-up direct GDB check against the same listener and ELF proved that the underlying OpenOCD plus GDB attach path is working outside the VS Code task handoff.
