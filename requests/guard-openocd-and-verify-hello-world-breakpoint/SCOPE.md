# Scope

## In Scope

- Add a small workflow guard around OpenOCD startup.
- Retry the hello world debug attach against the current board and toolchain state.
- Verify whether the debug flow reaches `app_main`.

## Out of Scope

- Broad debugger workflow redesign.
- Firmware code changes unrelated to debugger validation.