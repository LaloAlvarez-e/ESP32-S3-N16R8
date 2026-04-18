# Scope

## In Scope

- Correct the repository's OpenOCD startup behavior for the live-attach debug path.
- Keep the reset-and-load flow available.
- Update the repository documentation for the corrected live-attach sequence.

## Out of Scope

- Replacing OpenOCD, GDB, or the ESP-IDF debug adapter.
- Proving early `app_main` breakpoint retention across USB-JTAG reenumeration.
- Reworking unrelated ESP-IDF build or flash logic.
