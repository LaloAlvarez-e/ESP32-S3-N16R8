# Request

Align the VS Code debug views with the current ESP-IDF `gdbtarget` workflow by removing confusing duplicates where possible, enabling supported register or memory inspection behavior, and clarifying unsupported panes.

## Current Result

Completed with documented adapter limits.

- The workspace now marks PlatformIO as an unwanted recommendation because its debug panes are not wired to this repository's ESP-IDF `gdbtarget` flow.
- The workspace now sets the closest supported Disassembly behavior with `debug.openDisassembly = auto` and `debug.disassemblyView.showSourceCode = true`.
- The documentation now explains that `Variables > Registers`, `ESP-IDF: Peripheral View`, and `ESP-IDF: Hex View` are the supported data-backed panes for this workflow.
- Duplicate PlatformIO panes still require manual extension disablement in VS Code if the user wants them removed from the sidebar entirely.
