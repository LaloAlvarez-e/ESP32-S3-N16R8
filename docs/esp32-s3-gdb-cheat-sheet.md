# ESP32-S3 GDB Cheat Sheet

This cheat sheet targets the workspace debug flow in this repository:

- ESP-IDF VS Code extension with `gdbtarget`
- OpenOCD on `localhost:3333`
- Xtensa ESP32-S3 GDB

For a peripheral-first list of base addresses and common register fields, see `docs/esp32-s3-peripheral-cheat-sheet.md`.

Use these commands in the VS Code GDB console while the target is halted.

## Core CPU Registers

Show the normal CPU register set:

```text
info registers
```

Show a few important registers in hex:

```text
p/x $pc
p/x $ps
p/x $sp
p/x $a0
```

Move the program counter only when you intentionally want to redirect execution:

```text
set $pc = 0x42000753
```

## Disassembly

Show instructions around the current PC:

```text
x/12i $pc
```

Show instructions at a known instruction-mapped flash address:

```text
x/16i 0x42000020
```

Disassemble a function by symbol:

```text
disassemble app_main
disassemble /m app_main
```

Disassemble an explicit address range:

```text
disassemble 0x42000020,+96
```

## Variables And Expressions

Print a variable in hex:

```text
p/x some_variable
```

Print the address of a symbol:

```text
p &some_variable
```

Change a writable program variable:

```text
set var some_variable = 1
```

The VS Code `Watch` panel is not a reliable write path in this workspace. Use `set var ...` or raw address writes from the GDB console when you need to modify state.

## Peripheral Register Inspection

Read 32-bit words from a peripheral base address:

```text
x/16wx 0x60010000
```

Read bytes from a peripheral region:

```text
x/32bx 0x60010000
```

Write a 32-bit peripheral register directly:

```text
set *((volatile uint32_t *)0x60010010) = 0x00000001
```

Read back the register you changed:

```text
x/wx 0x60010010
```

Common ESP32-S3 peripheral base addresses visible in the ESP-IDF Peripheral View include:

- `0x60027000` for I2C1
- `0x6002C000` for MCPWM1
- `0x60025000` for SPI3
- `0x60020000` for TIMG1
- `0x60010000` for UART1

## Memory Inspection

The validated memory regions in this workspace are:

- DRAM data at `0x3FC88000`, length `0x53700`
- IRAM at `0x40374000`, length `0x57700`
- Instruction-mapped flash at `0x42000020`, length `0x7FFFE0`
- Read-only mapped flash at `0x3C000020`, length `0x1FFFFE0`
- RTC IRAM at `0x600FE000`, length `0x1FE8`
- RTC slow memory at `0x50000000`, length `0x2000`

Read words from DRAM:

```text
x/16wx 0x3FC88000
```

Read words from IRAM:

```text
x/16wx 0x40374000
```

Read bytes from mapped flash:

```text
x/32bx 0x3C000020
```

Read instructions from mapped flash:

```text
x/16i 0x42000020
```

Write a 32-bit word into writable RAM:

```text
set *((uint32_t *)0x3FC88000) = 0x12345678
```

## Breakpoints And Watchpoints

Set a breakpoint on a symbol:

```text
break app_main
```

Set a temporary breakpoint:

```text
tbreak hello_world_project_main_task
```

Watch a variable for writes:

```text
watch some_variable
```

Watch a raw address for writes:

```text
watch *((uint32_t *)0x3FC88000)
```

## OpenOCD Monitor Commands

Halt the target:

```text
monitor halt
```

Resume the target:

```text
monitor resume
```

Reset and halt:

```text
monitor reset halt
```

Reset and run:

```text
monitor reset run
```

## ESP-IDF Views And Their GDB Relationship

- `ESP-IDF: Peripheral View` is the supported register browser for this workspace, but it is read-only.
- `ESP-IDF: Hex View` is the supported sidebar memory inspector for variables and expressions.
- `Variables > Registers` is the only live register tree backed by the current `gdbtarget` session.
- Arbitrary address reads and writes still use the GDB console commands shown above.

## Quick Workflow

1. Start a workspace debug profile and halt the target.
2. Open `ESP-IDF: Peripheral View` for read-only peripheral browsing.
3. In `Variables`, right-click a variable or expression and choose `View As Hex` to populate `ESP-IDF: Hex View`.
4. Use the GDB console for raw addresses, direct register writes, and instruction inspection.
