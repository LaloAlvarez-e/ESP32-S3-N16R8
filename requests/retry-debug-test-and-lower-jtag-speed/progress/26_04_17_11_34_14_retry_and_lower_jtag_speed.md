# Progress Update

## Completed Work

- Retried the hello world debug path after the user shut down GDB.
- Confirmed that stale and overlapping GDB clients could interfere with repeat tests.
- Reproduced OpenOCD startup instability at the default 40000 kHz USB-JTAG speed, including `esp_usb_jtag` buffer overflows and dropped GDB sockets.
- Validated that `adapter speed 5000` allowed OpenOCD to start cleanly and GDB to attach interactively.
- Confirmed that the lower-speed path allowed a live hardware breakpoint to be set at `app_main`.
- Confirmed that the current soft-reset flow still did not reach `app_main`; the target halted back in ROM around `0x40041A79` or `0x40041A7C`.
- Updated the repository OpenOCD task path to pass a configurable adapter speed and set the validated workspace value to `5000`.
- Removed `monitor reset halt` from the attach-only launch profiles so they behave like actual attach sessions.
- Updated the README to document the lower-speed fix and the remaining reset-path limitation.

## Result

The root-workspace debug workflow is now materially more stable on this machine because the repository-managed OpenOCD path no longer runs the built-in USB-JTAG link at the unstable 40000 kHz default. The remaining limitation is no longer the socket handshake; it is the board/reset behavior when trying to use the reset-driven path to stop at `app_main`.