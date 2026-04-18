# Status

## State

Completed

## Summary

The F5 startup failure was traced to two stacked issues: the Microsoft `cppdbg` adapter rejected the Xtensa target architecture, and the ESP-IDF extension did not recognize the repository root as an ESP-IDF project because `sdkconfig` and a valid ESP-IDF build directory do not exist at the workspace root. The workspace visual debug profiles were migrated to the ESP-IDF native `gdbtarget` adapter, `idf.openOcdConfigs` was corrected to `board/esp32s3-builtin.cfg`, and the recommended F5 path was changed to root-workspace-compatible profiles that build the project and start OpenOCD through repository tasks before attaching visually. A permanent named template profile and updated guidance were also added. The latest follow-up refinement changed the `gdbtarget` connection blocks to the adapter's native `extended-remote` host/port form, added conservative GDB init commands, and changed the OpenOCD background task to stay silent instead of stealing focus so the visual session can behave more like a normal IDE debug launch. The attach-only path is now the recommended stability-oriented profile, although a clean observable halt at `app_main` is still not fully proven.