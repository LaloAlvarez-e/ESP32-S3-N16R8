# Progress Entry

## Completed Work

- Added a `-ResumeTargetAfterStartup` switch to `tools/esp32/start-openocd.ps1`.
- Added `ESP32: OpenOCD Server (Live Attach)` to `.vscode/tasks.json`.
- Routed `ESP32: Prepare Hello World Live Attach`, `ESP32: Prepare Sample Project Live Attach`, and `ESP32: Prepare Custom Project Live Attach` through the new live-attach server task.
- Updated `README.md` and `hello_world_project/README.md` so the manual and prepare-task flows distinguish between the plain OpenOCD server and the live-attach server.

## Validation

- `get_errors` reported no errors for the edited PowerShell, JSON, and Markdown files.
- A direct alternate-port OpenOCD probe with `reset run` could not be completed because the active server already owned the USB-JTAG device and the second probe hit `LIBUSB_ERROR_ACCESS`.
- A direct telnet control check against the already running OpenOCD instance on `localhost:4444` succeeded.
- Sending `reset run` to that active server reached the target and triggered a software reset.
- Sending `resume` immediately afterward returned `[esp32s3.cpu0] not halted`, which indicates the current server no longer sees CPU0 stopped in the original reset halt.

## Notes

- The original pasted OpenOCD startup log was a startup snapshot, not a complete description of the current target state after telnet control.
- The new repository fix is aimed at future live-attach launches so they start from a released target state automatically instead of requiring manual telnet intervention.