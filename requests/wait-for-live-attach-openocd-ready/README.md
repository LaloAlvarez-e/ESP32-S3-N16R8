# Request

Make the root-workspace live-attach debug path wait for a true OpenOCD-ready point before starting GDB, so the attach-running profiles do not connect while the reset-run startup sequence is still producing transient halt states.

## Current Result

Completed. The live-attach helper now prints an explicit `ESP32_LIVE_ATTACH_READY` marker after the startup `reset run` release sequence completes, and the `ESP32: OpenOCD Server (Live Attach)` task now waits for that marker before VS Code starts GDB. The active OpenOCD telnet query also confirmed that the target reaches the `running` state after startup, so the remaining issue was the handoff timing rather than a permanently halted chip.
