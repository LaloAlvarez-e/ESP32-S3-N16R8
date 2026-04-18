# Progress Entry

## Completed Work

- Investigated the F5 startup failure and confirmed it came from the Microsoft `cppdbg` adapter rather than from OpenOCD or the firmware image.
- Switched the visual launch configurations from `cppdbg` to the ESP-IDF extension's native `gdbtarget` adapter.
- Corrected `.vscode/settings.json` so `idf.openOcdConfigs` uses `board/esp32s3-builtin.cfg`, matching the ESP32-S3 built-in USB JTAG path.
- Added a permanent named launch profile template: `ESP32S3: Template Project (Copy And Rename)`.
- Updated the root README to document the native adapter, the recommended attach-only flow, and how to create permanent named profiles for future projects.
- Validated `.vscode/launch.json`, `.vscode/settings.json`, and `README.md`.

## Result

- The known `arch` error path in `cppdbg` was removed from the workspace visual-debug flow.
- The recommended visual debug path is now the attach-only profile when the board is already flashed, which is less intrusive and more stable than reloading flash during every session.
- New projects now have both a prompt-driven generic path and a permanent copy-and-rename launch template.