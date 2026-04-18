# Scope

## In Scope

- Start the configured OpenOCD server for the hello world debug flow.
- Connect GDB using the built hello-world ELF and verify that execution reaches `app_main`.
- Capture the outcome for the repository tracking workflow.

## Out of Scope

- Reworking firmware code.
- Changing the board debug wiring.
- Extending the debug session beyond verifying the configured break at `app_main` unless required to diagnose a failure.
