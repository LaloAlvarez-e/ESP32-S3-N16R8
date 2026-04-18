# Request

Fix the VS Code attach-only debug flow so it behaves like a true late-attach session instead of waiting on an early `app_main` breakpoint that is unreliable on this board.

## Outcome

The attach-only profiles were replaced with practical `Attach Running Firmware` profiles that connect to the current OpenOCD session and immediately halt the current firmware state. Matching prepare tasks were added so the symbol build and OpenOCD startup still happen from the workspace. The profiles now also set `initialBreakpoint` to an empty string so the ESP-IDF extension cannot auto-inject `thb app_main`. A live GDB check confirmed that the new profile shape can connect and land in a paused state instead of hanging on `app_main`.
