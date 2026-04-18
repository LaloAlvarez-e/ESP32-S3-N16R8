# Progress Entry

## Completed Work

- Queried the active OpenOCD telnet interface and confirmed both `esp32s3.cpu0` and `esp32s3.cpu1` were already in the `running` state after the live-attach startup sequence.
- Added an explicit `ESP32_LIVE_ATTACH_READY` marker to `tools/esp32/start-openocd.ps1` so the live-attach startup path can report a true handoff point after `reset run` completes.
- Updated `.vscode/tasks.json` so `ESP32: OpenOCD Server (Live Attach)` now waits for `ESP32_LIVE_ATTACH_READY` instead of the first `Listening on port 3333 for gdb connections` line.
- Updated `README.md` and `hello_world_project/README.md` so the manual and preLaunch live-attach flows use the new readiness marker.

## Validation

- `get_errors` reported no errors for the edited PowerShell, JSON, and Markdown files.
- A read-only telnet query to the active OpenOCD server reported both ESP32-S3 cores in the `running` state, which proved the remaining issue was the VS Code handoff timing rather than a permanently halted target.
- The new ready marker is present and aligned across the helper script, task matcher, and documentation.

## Notes

- The live-attach OpenOCD startup log can still show transient reset-halt messages while `reset run` is completing.
- With the new task matcher, those transient messages no longer cause VS Code to start GDB too early.
