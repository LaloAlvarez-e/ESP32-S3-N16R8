# Request README

## Request

Implement a coverage tool to get the test coverage for the production files.

## Current Result

Completed. The repository now contains a host-side coverage runner under `tools/coverage/`, validated against the real CMake and CTest flow.

## Validation

- Command: `powershell -ExecutionPolicy Bypass -File .\tools\coverage\run-host-coverage.ps1 -Clean`
- Coverage reports: `build/coverage/html/index.html` and `build/coverage/coverage.xml`
- Production line coverage: `99.38% (321/323)`
- Production-only file list validated from the Cobertura XML.
- `common_utils/util_status/util_status.c`
- `common_utils/util_math/util_math.c`
- `common_os/os_port/os_port.c`
- `common_os/os_clock/os_clock.c`
- `common_driver/gpio_driver/gpio_driver.c`
- `common_driver/uart_driver/uart_driver.c`
- `sample_project/app_core/app_core.c`
- `sample_project/app_core/telemetry/telemetry.c`
- `sample_project/app_support/app_support.c`
