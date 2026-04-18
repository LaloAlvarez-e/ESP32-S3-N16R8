# Progress Entry

## Overview

Added a no-task hello world attach profile to separate OpenOCD startup from GDB attach.

## Details

- Added `ESP32S3: Hello World (Connect To Existing OpenOCD)` to `.vscode/launch.json`.
- Kept `runOpenOCD` disabled and removed any `preLaunchTask` dependency so the launch profile can test direct GDB attach against an already running server.
- Reused the stable late-attach setup: `extended-remote`, `set pagination off`, `set remotetimeout 10`, `monitor halt`, and `initialBreakpoint: ""`.
- Documented the new fallback flow in `README.md`.
- Validated `.vscode/launch.json` and `README.md` with no reported errors.

## Rationale

Recent logs show an `OpenOCD only` state with no GDB process and no TCP client on port `3333`, which points at a failure before the debug adapter actually starts or completes. The new profile isolates that boundary by removing the task handoff from the launch path.
