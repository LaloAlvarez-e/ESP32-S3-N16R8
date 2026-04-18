# Status

## State

Completed

## Summary

A stale `openocd.exe` process was found holding ports `3333`, `4444`, and `6666`. After stopping that stale process, a fresh OpenOCD start succeeded far enough to detect the ESP32-S3 JTAG taps, examine CPU0, and start the GDB server on port `3333`, although CPU1 examination still reported `Unexpected OCD_ID = 00000000`.