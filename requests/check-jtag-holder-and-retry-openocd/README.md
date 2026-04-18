# Request

Check whether another process is holding the ESP32-S3 JTAG interface and retry OpenOCD.

## Outcome

The blocker was at least partly a stale OpenOCD process. Once that process was stopped, a fresh OpenOCD instance could start and expose the GDB server for the target.