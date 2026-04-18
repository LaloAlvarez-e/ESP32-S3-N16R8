# Request

Retry the live hello world debug test after the user shut down GDB, determine why the session was failing, and apply any repository-side changes needed to make the USB-JTAG debug path more reliable.

## Outcome

The retry showed that the main instability was the ESP32-S3 built-in USB-JTAG link at the default 40000 kHz OpenOCD speed. Lowering the OpenOCD adapter speed to 5000 kHz stabilized OpenOCD startup and interactive GDB attach on this host. The repository task path now uses the lower speed by default, and the attach-only launch profiles no longer force a reset. The remaining limitation is that the soft-reset path still halted back in ROM around `0x40041A79` or `0x40041A7C` instead of proving a stop at `app_main`; those addresses were confirmed to be ESP32-S3 internal ROM addresses, not user-image code. A later reset trace also showed `0x40378AEE`, which resolves in the app ELF to `esp_cpu_wait_for_intr`, meaning the application can boot successfully after a manual reset even when the early `app_main` breakpoint is lost.
