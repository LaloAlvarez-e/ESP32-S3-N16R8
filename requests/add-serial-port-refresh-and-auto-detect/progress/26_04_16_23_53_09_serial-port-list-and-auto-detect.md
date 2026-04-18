# Progress Entry

- Added serial-port enumeration and safe automatic port-resolution helpers to `tools/esp32/common.ps1`.
- Added `tools/esp32/list-serial-ports.ps1` so available COM ports can be checked from the repository tools.
- Added the `ESP32: List Serial Ports` VS Code task.
- Updated `.vscode/settings.json` so `esp32Project.serialPort` now uses `AUTO` instead of a fixed COM value.
- Validated that the new listing flow reports `COM7` and that automatic resolution selects `COM7` when it is the only detected serial port.