# hello_world_project

Minimal ESP32-S3 hello-world bring-up project for first-device validation, ELF loading, and GDB debugging.

## Purpose

- Confirm the ESP-IDF toolchain and target configuration are working.
- Provide a small ELF target for OpenOCD and GDB bring-up.
- Keep a simple reference project beside the richer `sample_project/` application.

## Build and Flash

Run these commands from the repository root:

```powershell
# List the available COM ports
powershell -ExecutionPolicy Bypass -File .\tools\esp32\list-serial-ports.ps1

# Build the project
powershell -ExecutionPolicy Bypass -File .\tools\esp32\invoke-idf.ps1 -ProjectDir .\hello_world_project -IdfPath 'C:\esp\v6.0\esp-idf' build

# Flash the project using AUTO serial-port detection
powershell -ExecutionPolicy Bypass -File .\tools\esp32\invoke-idf.ps1 -ProjectDir .\hello_world_project -IdfPath 'C:\esp\v6.0\esp-idf' -Baud 460800 flash

# Start the serial monitor
powershell -ExecutionPolicy Bypass -File .\tools\esp32\invoke-idf.ps1 -ProjectDir .\hello_world_project -IdfPath 'C:\esp\v6.0\esp-idf' monitor
```

If more than one COM port is attached, pass `-Port COMx` explicitly or set `esp32Project.serialPort` in `.vscode/settings.json`.

The validated monitor output includes:

- `hello_world: Hello world from ESP32-S3`
- `hello_world: ESP32-S3 detected: 2 core(s), revision 2, 16 MiB flash`
- repeating `hello_world: Hello world task alive`

## Debug and ELF Load

Use one of the following two debug paths.

### Option 1: OpenOCD plus explicit ELF load

```powershell
# Start OpenOCD
powershell -ExecutionPolicy Bypass -File .\tools\esp32\start-openocd.ps1 -IdfPath 'C:\esp\v6.0\esp-idf' -OpenOcdPath 'C:\Users\avala\.espressif\tools\openocd-esp32\v0.12.0-esp32-20251215\openocd-esp32\bin\openocd.exe' -OpenOcdScripts 'C:\Users\avala\.espressif\tools\openocd-esp32\v0.12.0-esp32-20251215\openocd-esp32\share\openocd\scripts' -OpenOcdConfig 'board/esp32s3-builtin.cfg'

# Load the ELF over GDB
powershell -ExecutionPolicy Bypass -File .\tools\esp32\load-elf.ps1 -ProjectDir .\hello_world_project -IdfPath 'C:\esp\v6.0\esp-idf' -GdbPath 'C:\Users\avala\.espressif\tools\xtensa-esp-elf-gdb\16.3_20250913\xtensa-esp-elf-gdb\bin\xtensa-esp32s3-elf-gdb.exe'
```

### Option 2: VS Code launch configuration

1. Run `ESP32: Build Hello World` or `ESP32: Build Hello World (Debug Hold)`.
2. Open `Run and Debug` in the repository root workspace.
3. Start either `ESP32S3: Hello World (Recommended Attach Running Firmware)` or `ESP32S3: Hello World (Reset And Load)`.

Use `Recommended Attach Running Firmware` for the stable late-attach path when the board is already flashed and running. Its prepare task now starts the dedicated `ESP32: OpenOCD Server (Live Attach)` path so OpenOCD resumes the target before GDB halts it, and the task does not hand control to VS Code until the server prints `ESP32_LIVE_ATTACH_READY`. Use `Reset And Load` when you want the debugger to reset the target, load the ELF, and break at `app_main` through the root-workspace prepare task.

For ESP-IDF extension debug panes, this workspace now points `idf.svdFilePath` at `.vscode/svd/esp32s3.svd`, so `ESP-IDF: Peripheral View` can populate register data while the target is stopped. The generic `Registers` and `Memory` panes may still stay empty under the `gdbtarget` adapter; use `ESP-IDF: Peripheral View`, `ESP-IDF: Hex View`, the Variables pane, and the GDB console for live target inspection.

If PlatformIO is installed on the machine, its separate `Peripherals`, `Registers`, `Memory`, and `Disassembly` panes can also appear in the Debug sidebar. Those panes are not connected to this repository's ESP-IDF `gdbtarget` session. The backed register view for this workflow is still `Variables > Registers`, the ESP-IDF Peripheral View remains read-only, and writable register or memory changes should be done through the GDB console.

The `Watch` panel is also not a dependable write surface in this debug stack. If you need to change a variable or register while stopped, use the GDB console with `set var ...` or a raw-address write.

For the exact GDB commands used for register reads, direct register writes, disassembly, raw memory inspection, and watchpoints in this workspace, see `../docs/esp32-s3-gdb-cheat-sheet.md`.
For a peripheral-first register reference, see `../docs/esp32-s3-peripheral-cheat-sheet.md`.

The build task now also emits `build/compile_commands.json`, so the root workspace can resolve ESP-IDF headers and shared-component references when you select `ESP32S3 Hello World Project` in `C/C++: Select a Configuration...`.

## Environment Setup

For direct terminal use, activate the ESP-IDF environment with:

```powershell
$env:IDF_PATH = 'C:\esp\v6.0\esp-idf'
& 'C:\esp\v6.0\esp-idf\export.ps1'
```

To keep the `IDF_PATH` value across new shells on Windows, run:

```powershell
setx IDF_PATH "C:\esp\v6.0\esp-idf"
```

## What To Change If Paths Move

Update these settings in `.vscode/settings.json` when the workspace layout or tool locations change:

- `esp32Project.idfPath` when the ESP-IDF folder moves.
- `esp32Project.helloWorldPath` when the project folder moves or is renamed.
- `esp32Project.serialPort` when you want to force a specific COM port instead of `AUTO`.
- `esp32Project.openOcdPath` when the OpenOCD executable moves.
- `esp32Project.openOcdScripts` when the OpenOCD scripts folder moves.
- `esp32Project.openOcdConfig` when the board or debug configuration changes.
- `esp32Project.gdbPath` when the Xtensa ESP32-S3 GDB executable moves.
- `idf.svdFilePath` when the workspace-local ESP32-S3 SVD file moves.
