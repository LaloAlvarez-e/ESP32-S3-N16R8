# Progress Entry

## Completed Work

- Inspected host processes relevant to ESP32 debugging.
- Found a stale `openocd.exe` process with PID `10292`.
- Confirmed that the stale `openocd.exe` instance owned ports `3333`, `4444`, and `6666`.
- Stopped the stale OpenOCD process and verified those ports were released.
- Retried the repository OpenOCD launch sequence.

## Result

- A stale OpenOCD instance was holding the debug ports and interfering with fresh debug attempts.
- After clearing it, OpenOCD successfully reached JTAG tap detection, CPU0 examination, and GDB server startup on port `3333`.
- CPU1 still reported `Unexpected OCD_ID = 00000000`, which did not prevent the server from coming up for primary-core debugging.