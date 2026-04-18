# Scope

## In Scope

- Add a way to list currently available serial ports from the repository tools.
- Add safe automatic serial-port resolution for ESP-IDF flash and monitor flows.
- Update workspace configuration so the serial-port handling is easier to maintain when the board port changes.

## Out of Scope

- Flashing firmware in this request.
- Changing the ESP-IDF build or OpenOCD toolchain.
- Implementing complex multi-device port selection heuristics.
