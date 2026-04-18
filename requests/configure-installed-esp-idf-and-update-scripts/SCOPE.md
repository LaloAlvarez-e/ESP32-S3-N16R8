# Scope

## In Scope

- Detect the installed ESP-IDF 6.0 toolchain paths.
- Update workspace settings to use the verified framework and debugger paths.
- Fix helper script assumptions that do not match the exported ESP-IDF environment.

## Out of Scope

- Upgrading ESP-IDF or changing the installed tool versions.
- Reworking the application projects beyond what is needed for toolchain readiness.

## Completion Notes

- Verified the installed toolchain paths in the workspace settings.
- Verified wrapper-script behavior against the installed ESP-IDF export model.
- Verified build artifact generation for `hello_world_project` and `sample_project`.