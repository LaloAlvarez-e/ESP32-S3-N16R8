# Request

Enable the ESP32-S3 peripheral debug view in this workspace and clarify why the generic Registers and Memory panes stay empty under the current ESP-IDF `gdbtarget` debug flow.

## Current Result

Completed.

- The workspace now vendors `.vscode/svd/esp32s3.svd` and points `idf.svdFilePath` at it.
- The ESP-IDF Peripheral View now has the register-definition source it needs for stopped `gdbtarget` sessions.
- The documentation now explains that the generic Registers and Memory panes are not populated by this adapter flow and that the ESP-IDF Peripheral and Hex views are the supported alternatives.
