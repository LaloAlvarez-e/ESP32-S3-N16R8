# Status

## State

Completed

## Summary

The built-in USB-JTAG path in this environment can allow the application to boot while still losing the earliest breakpoint window across reset. To make the VS Code debug flow practical, the hello world project now has a build-time startup hold helper near the top of `app_main`. The value is injected through `HELLO_WORLD_PROJECT_DEBUG_STARTUP_HOLD_MS`, exposed in workspace settings as `esp32Project.helloWorldDebugStartupHoldMs`, and enabled automatically by the hello world debug-prepare task. The normal hello world build path explicitly sets the hold back to `0`, and both the debug-hold and normal build variants were validated successfully.
