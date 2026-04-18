# Scope

## In Scope

- Add a repository-owned coverage runner for the host-side GoogleTest suite.
- Restrict coverage reporting to production source files.
- Emit coverage outputs that can be opened locally or consumed by other tooling.
- Track the work in a new request folder.

## Out of Scope

- Device-side coverage for ESP-IDF firmware.
- Refactoring production code solely to change coverage percentages.
- Replacing the existing host-side test workflow.

## Delivered

- Added `tools/coverage/run-host-coverage.ps1` as the repository-owned coverage runner.
- Added coverage usage documentation under `tools/coverage/README.md` and the root `README.md`.
- Validated production-only coverage output for the existing host-side test matrix.
