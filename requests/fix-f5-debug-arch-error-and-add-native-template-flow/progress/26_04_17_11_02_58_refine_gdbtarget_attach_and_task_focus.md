# Progress Update

## Completed Work

- Changed all workspace `gdbtarget` launch profiles to use the native `target` shape with `type: "extended-remote"`, `host: "localhost"`, and `port: "3333"` instead of manual `connectCommands`.
- Added `set pagination off` and `set remotetimeout 10` to the GDB init command sequences used by the visual launch profiles.
- Changed the `ESP32: OpenOCD Server` background task presentation to `reveal: "silent"` and `focus: false` so the OpenOCD terminal is less likely to dominate the debug experience.
- Revalidated `.vscode/launch.json` and `.vscode/tasks.json` with no reported errors.

## Result

The visual debug launch path is now closer to the native expectations of the ESP-IDF `gdbtarget` adapter and should behave more like a normal IDE flow. OpenOCD startup remains available in the terminal, but the background task should no longer take focus away from the debugger UI by default.

## Remaining Risk

- The board-side halt after `continue` is still not fully proven through the VS Code UI.
- Variables, Watch, and Call Stack panes still depend on the debugger completing attach and stopping the target. If the adapter does not finish the attach handshake, those panes will remain empty even though OpenOCD is running.
