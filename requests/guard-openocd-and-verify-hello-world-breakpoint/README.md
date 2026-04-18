# Request

Add a small guard so stale OpenOCD is detected or cleared before future debug launches, then try the full hello world debugger attach and verify that it stops at `app_main`.

## Outcome

The stale-OpenOCD guard and debugger connection improvements were added successfully. The attach path now reaches OpenOCD and programs a hardware breakpoint at `app_main`, but this host or target setup still does not keep the session alive through the post-`continue` halt, so an actual stop at `app_main` has not yet been proven.