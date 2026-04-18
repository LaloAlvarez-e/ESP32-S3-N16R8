# Status

## State

Completed

## Summary

The workflow was updated to clear stale OpenOCD listeners automatically, disable GDB paging, and use `target extended-remote` with a longer remote timeout. The guarded OpenOCD startup was validated, and hello world was reflashed cleanly on COM8. A full debug attach repeatedly connected and set a hardware breakpoint at `app_main` in `main.c:58`, but the GDB session dropped after `continue`, and no actual halt at `app_main` was observed; OpenOCD instead reported halts at unresolved ROM addresses such as `0x40041A76`, `0x40041A79`, and `0x40041A7C`.