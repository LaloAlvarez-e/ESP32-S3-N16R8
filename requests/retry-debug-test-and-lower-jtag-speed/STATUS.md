# Status

## State

Completed

## Summary

The original retry failure was not just a stale GDB session. Live testing showed three distinct factors: overlapping GDB batch clients could collide on the same OpenOCD socket, the default 40000 kHz built-in USB-JTAG speed was unstable on this host and produced `esp_usb_jtag` buffer overflows plus dropped GDB connections, and the GDB-driven soft-reset path still did not reach `app_main`. Lowering OpenOCD to 5000 kHz stabilized OpenOCD startup and allowed an interactive GDB session to connect, arm a hardware breakpoint at `hello_world_project/main/main.c:58`, and continue without immediate socket loss. Follow-up symbol resolution clarified the two recurring halt classes: `0x40041A79` and `0x40041A7C` are ESP32-S3 internal ROM boot/reset addresses, while `0x40378AEE` resolves in the application ELF to `esp_cpu_wait_for_intr`. That means a manual reset with transient USB-JTAG I/O loss can still let the application boot all the way into its idle wait path, but the early hardware breakpoint at `app_main` is not surviving that reset/reenumeration sequence. A clean stop at `app_main` still remains unproven.
