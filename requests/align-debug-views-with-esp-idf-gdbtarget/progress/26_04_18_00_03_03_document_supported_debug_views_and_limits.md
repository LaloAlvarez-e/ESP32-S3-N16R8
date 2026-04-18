# Progress Entry

## Completed Work

- Confirmed that the duplicate empty `PERIPHERALS`, `REGISTERS`, `MEMORY`, and `DISASSEMBLY` panes come from the installed PlatformIO extension, not from the ESP-IDF extension used by this repository.
- Confirmed that the active debug adapter in this workspace remains ESP-IDF `gdbtarget`.
- Confirmed that the ESP-IDF extension contributes the working `ESP-IDF: Peripheral View` and `ESP-IDF: Hex View` panels.
- Confirmed that the ESP-IDF Peripheral View is read-only and that the current ESP-IDF `gdbtarget` flow does not back the generic PlatformIO `REGISTERS` or `MEMORY` panes.
- Updated `.vscode/extensions.json` to mark `platformio.platformio-ide` as an unwanted recommendation for this ESP-IDF workspace.
- Updated `.vscode/settings.json` with the closest supported Disassembly settings: `debug.openDisassembly = auto` and `debug.disassemblyView.showSourceCode = true`.
- Updated the workspace documentation to explain which panes are valid for this workflow, why the PlatformIO panes stay empty, and how to modify registers or memory through the GDB console.

## Validation

- `get_errors` reported no errors in `.vscode/extensions.json`, `.vscode/settings.json`, `README.md`, or `hello_world_project/README.md` after the edits.
- Confirmed the new settings and documentation text are present.

## Notes

- Removing the duplicate PlatformIO panes entirely requires disabling the PlatformIO extension for this workspace in VS Code; there is no repository-local setting that can hide them once the extension is active.
- The only live register view for the current ESP-IDF `gdbtarget` workflow is `Variables > Registers`.
- The supported sidebar memory inspector for this workflow is `ESP-IDF: Hex View`, populated from `View As Hex` on variables or expressions.
- Arbitrary address reads and writable register or memory changes remain GDB-console operations in this stack.
