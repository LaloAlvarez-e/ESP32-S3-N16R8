# Status

## State

Completed

## Summary

The previous attach-only launch profiles were still behaving like early-startup breakpoint launches for two reasons: they had their own `initialBreakpoint` fields, and the ESP-IDF extension auto-injects `thb app_main` when `initialBreakpoint` is undefined. The workspace now provides `Attach Running Firmware` profiles that connect through `gdbtarget`, issue `monitor halt`, and explicitly set `initialBreakpoint` to an empty string so no hidden `app_main` breakpoint is added. Matching prepare tasks build symbols and start OpenOCD without relying on the debug-startup hold path. A live GDB attach confirmed that the new flow can connect and pause the target successfully.
