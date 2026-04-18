# Status

Completed.

- Confirmed that the duplicate empty `PERIPHERALS`, `REGISTERS`, `MEMORY`, and `DISASSEMBLY` panes come from PlatformIO, not from ESP-IDF.
- Confirmed that the working ESP-IDF panes for this repository are `ESP-IDF: Peripheral View` and `ESP-IDF: Hex View` under the current `gdbtarget` flow.
- Confirmed that the ESP-IDF Peripheral View is read-only and that writable register or memory changes remain GDB-console operations.
- Marked PlatformIO as an unwanted recommendation and enabled the closest supported VS Code Disassembly behavior in workspace settings.
- Updated documentation and validated the edited files with no reported errors.
