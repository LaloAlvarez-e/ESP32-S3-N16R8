# Host-Side Coverage Tool

## Purpose

Generate host-side test coverage for the repository's production C and C++ files by reusing the existing CMake and CTest unit-test flow.

## Prerequisites

- Windows host with PowerShell.
- `cmake` and `ctest` available on `PATH`.
- `OpenCppCoverage.exe` available on `PATH`.

## Default Usage

```powershell
powershell -ExecutionPolicy Bypass -File .\tools\coverage\run-host-coverage.ps1
```

## Useful Options

```powershell
powershell -ExecutionPolicy Bypass -File .\tools\coverage\run-host-coverage.ps1 -Clean
powershell -ExecutionPolicy Bypass -File .\tools\coverage\run-host-coverage.ps1 -Configuration RelWithDebInfo
powershell -ExecutionPolicy Bypass -File .\tools\coverage\run-host-coverage.ps1 -BuildDir build/host-coverage -ReportDir build/coverage
```

If the current PowerShell session already has script execution enabled, you can also run the script directly with `& .\tools\coverage\run-host-coverage.ps1`.

## Output

- HTML report: `build/coverage/html/index.html`
- Cobertura XML: `build/coverage/coverage.xml`

## Scope

The tool includes production sources under:

- `common_utils/`
- `common_os/`
- `common_driver/`
- `sample_project/`

The tool excludes sources under each local `test/` folder so the report reflects production-file coverage rather than test code coverage.
