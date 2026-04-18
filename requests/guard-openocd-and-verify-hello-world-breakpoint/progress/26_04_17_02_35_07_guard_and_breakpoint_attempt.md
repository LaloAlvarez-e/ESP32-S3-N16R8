# Progress Entry

## Completed Work

- Added a shared guard in `tools/esp32/common.ps1` to detect listeners on OpenOCD ports `3333`, `4444`, and `6666`, stop stale `openocd.exe` processes, and fail clearly if another process owns those ports.
- Wired that guard into `tools/esp32/start-openocd.ps1`.
- Updated `tools/esp32/load-elf.ps1` to disable GDB paging and use `set remotetimeout 10` plus `target extended-remote`.
- Updated `.vscode/launch.json` to use the same `extended-remote` and timeout setup for both ESP32-S3 debug configurations.
- Rebuilt hello world and reflashed it cleanly on COM8.
- Repeatedly retried the hello world debug attach using both the repository helper and direct batch GDB commands.

## Result

- The stale OpenOCD guard works and clears old listeners before startup.
- OpenOCD now starts reliably enough to expose the GDB server again.
- GDB successfully connected and set a hardware breakpoint at `app_main` (`0x420086F4`, `main.c:58`).
- The session still dropped after `continue`, so no successful halt at `app_main` was captured.
- OpenOCD logs show subsequent halts at unresolved ROM addresses `0x40041A76`, `0x40041A79`, and `0x40041A7C`, not at the `app_main` address.

## Current Conclusion

- The repository workflow is improved and less fragile than before.
- The remaining blocker is a live debugger or target stability issue after continue, not stale OpenOCD startup.