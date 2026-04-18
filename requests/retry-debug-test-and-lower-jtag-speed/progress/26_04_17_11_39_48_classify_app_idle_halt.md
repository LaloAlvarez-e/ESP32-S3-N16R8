# Progress Update

## Completed Work

- Resolved the later halt address `0x40378AEE` against the hello world build artifacts.
- Confirmed that `0x40378AEE` resolves in `hello_world_project/build/hello_world_project.elf` to `esp_cpu_wait_for_intr` from `components/esp_hw_support/cpu.c`.
- Confirmed that the same address does not resolve in `bootloader/bootloader.elf`.

## Result

This distinguishes two different halt modes on the board:

- `0x40041A79` and `0x40041A7C` are ROM-side boot/reset addresses.
- `0x40378AEE` is application-side idle wait code.

That means a manual reset with transient USB-JTAG I/O loss can still allow the application to boot all the way into its idle path. The remaining reason `app_main` is not being trapped is therefore more likely breakpoint loss across reset/reenumeration than a failure to boot the application.