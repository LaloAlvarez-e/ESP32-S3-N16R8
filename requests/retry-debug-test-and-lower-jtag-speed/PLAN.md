# Plan

1. Retry the live hello world OpenOCD and GDB test after stale GDB shutdown.
2. Determine whether the failure is on the OpenOCD transport side, the GDB client side, or the reset path.
3. Apply focused repository changes for the validated stability improvement.
4. Document the findings and remaining limitation.