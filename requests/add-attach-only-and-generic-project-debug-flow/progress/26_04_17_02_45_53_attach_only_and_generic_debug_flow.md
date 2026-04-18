# Progress Entry

## Completed Work

- Added VS Code-managed attach-only debug profiles for hello world and sample project.
- Added prompt-driven custom project launch configurations for managed OpenOCD debug with and without ELF load.
- Added prompt-driven custom project build, flash, and monitor tasks.
- Updated the repository README to explain the new visual debug options and the new-project flow.
- Validated `.vscode/launch.json`, `.vscode/tasks.json`, and `README.md`.

## Result

- Existing projects now have a less intrusive visual attach-only option.
- New ESP-IDF projects can be built, flashed, monitored, and debugged without hand-editing `launch.json` for each new folder.
- JSON or workspace setting edits are only still needed when tool paths or the OpenOCD board configuration change, or when a permanent named project profile is preferred.