# Request

Add a second cheat sheet focused on ESP32-S3 peripheral base addresses and common register fields that are usually inspected first, and explain why Watch values in the Debug panel cannot be modified reliably in this workspace.

## Current Result

Completed.

- The repository now includes `docs/esp32-s3-peripheral-cheat-sheet.md`.
- The root and hello world documentation now link the new peripheral-focused sheet.
- The documentation now explains why Watch edits are not dependable in the current ESP-IDF debug workflow and points users to the GDB console write path.

