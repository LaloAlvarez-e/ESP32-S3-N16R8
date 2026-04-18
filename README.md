# ESP32-S3-N16R8

This repository is the starting point for creating and organizing ESP32-based projects, with an initial focus on the ESP32-S3-N16R8 platform.

It will be used to build out project templates, source structure, configuration, setup notes, and development guidance for future ESP32 work.

## Status

Work in progress. More project files, examples, and documentation will be added as the repository takes shape.

## Host-Side Coverage

Host-side GoogleTest coverage for production files can be generated on Windows with OpenCppCoverage by running `powershell -ExecutionPolicy Bypass -File .\tools\coverage\run-host-coverage.ps1`. The tool emits an HTML report at `build/coverage/html/index.html` and a Cobertura report at `build/coverage/coverage.xml`.

See `tools/coverage/README.md` for prerequisites and supported options.

## Device-Side Projects

The repository now includes standalone ESP-IDF application folders for device-side bring-up and debugging.

- `sample_project/` can be opened directly as an ESP-IDF project and reuses `common_utils/`, `common_os/`, and `common_driver/` as shared components.
- `hello_world_project/` is a minimal ESP32-S3 hello-world bring-up and debug project.
- Workspace tasks, launch configurations, and helper scripts under `.vscode/` and `tools/esp32/` provide build, flash, OpenOCD, ELF load, and GDB debug entry points.
- `docs/esp32-s3-gdb-cheat-sheet.md` provides exact GDB commands for common ESP32-S3 register, memory, and disassembly inspection tasks in this workspace.
- `docs/esp32-s3-peripheral-cheat-sheet.md` provides a peripheral-first reference for ESP32-S3 base addresses and the first register fields worth checking in debug.

## ESP-IDF Environment Setup

The validated ESP-IDF installation used by this repository is `C:\esp\v6.0\esp-idf`.

For direct `idf.py` use in a PowerShell session, activate the ESP-IDF environment with:

```powershell
$env:IDF_PATH = 'C:\esp\v6.0\esp-idf'
& 'C:\esp\v6.0\esp-idf\export.ps1'
```

To persist `IDF_PATH` for future shells on Windows, run:

```powershell
setx IDF_PATH "C:\esp\v6.0\esp-idf"
```

Open a new terminal after `setx` so the updated environment variable is visible.

The repository tasks already pass the ESP-IDF path from `.vscode/settings.json`, so a global `IDF_PATH` is most important when you run `idf.py` yourself or open one of the project folders directly outside the workspace.

## Workspace Settings You May Need To Change

The repository reads the following settings from `.vscode/settings.json`:

- `esp32Project.idfPath`: update this if the ESP-IDF installation moves.
- `esp32Project.helloWorldPath`: update this if `hello_world_project/` is renamed or moved.
- `esp32Project.helloWorldDebugStartupHoldMs`: controls the hello world startup hold used by the debug build path so VS Code has time to attach after reset. Set it to `0` to disable the hold.
- `esp32Project.sampleProjectPath`: update this if `sample_project/` is renamed or moved.
- `esp32Project.serialPort`: keep this as `AUTO` to use the only detected COM port, or change it to `COMx` when multiple serial ports are attached.
- `esp32Project.flashBaudRate`: change this if the target requires a different flash baud rate.
- `esp32Project.openOcdPath`: update this if the OpenOCD executable moves.
- `esp32Project.openOcdScripts`: update this if the OpenOCD scripts folder moves.
- `esp32Project.openOcdConfig`: update this if the board or JTAG configuration changes.
- `esp32Project.openOcdAdapterSpeedKHz`: lower this when the built-in USB-JTAG link shows `esp_usb_jtag` buffer overflows, dropped GDB sockets, or unstable attach behavior. The validated value on this host is `5000`.
- `esp32Project.gdbPath`: update this if the Xtensa ESP32-S3 GDB executable moves.
- `idf.svdFilePath`: update this if you move or replace the workspace-local ESP32-S3 SVD file used by the ESP-IDF Peripheral View.

If the ESP-IDF tools are reinstalled in a new location, the most likely settings to update are `esp32Project.idfPath`, `esp32Project.openOcdPath`, `esp32Project.openOcdScripts`, and `esp32Project.gdbPath`.

## VS Code Header References And IntelliSense

This repository root is a multi-project workspace, not a single ESP-IDF application root. Source-level references into ESP-IDF headers from the root workspace are therefore driven by compile databases and the C/C++ extension configuration instead of by treating the repository root as one active ESP-IDF project.

The workspace now includes `.vscode/c_cpp_properties.json` with two C/C++ configurations:

- `ESP32S3 Hello World Project`
- `ESP32S3 Sample Project`

Use the root workspace like this:

1. Install the recommended extensions from `.vscode/extensions.json`.
2. Run `ESP32: Build Hello World` or `ESP32: Build Sample Project` once so that the project emits `build/compile_commands.json`.
3. Run `C/C++: Select a Configuration...` in VS Code and choose the project you are editing.
4. Use Go To Definition, Peek Definition, Find All References, and IntelliSense from the root workspace.

The selected configuration reads the active project's `compile_commands.json`, indexes `common_utils/`, `common_os/`, `common_driver/`, and browses the ESP-IDF components tree rooted at `C:\esp\v6.0\esp-idf`.

If the ESP-IDF installation path changes, update both `.vscode/settings.json` and `.vscode/c_cpp_properties.json`.

## Serial Port Refresh

To list the currently available serial ports from the repository tools, run:

```powershell
powershell -ExecutionPolicy Bypass -File .\tools\esp32\list-serial-ports.ps1
```

Or use the VS Code task `ESP32: List Serial Ports`.

With `esp32Project.serialPort` set to `AUTO`, the flash and monitor flows automatically select the serial port when exactly one COM port is detected. If more than one COM port is present, set `esp32Project.serialPort` to the correct `COMx` value or pass `-Port COMx` explicitly to the wrapper script.

## Common Commands

Run these commands from the repository root:

```powershell
# List currently available COM ports
powershell -ExecutionPolicy Bypass -File .\tools\esp32\list-serial-ports.ps1

# Build hello world
powershell -ExecutionPolicy Bypass -File .\tools\esp32\invoke-idf.ps1 -ProjectDir .\hello_world_project -IdfPath 'C:\esp\v6.0\esp-idf' build

# Flash hello world using AUTO serial-port detection
powershell -ExecutionPolicy Bypass -File .\tools\esp32\invoke-idf.ps1 -ProjectDir .\hello_world_project -IdfPath 'C:\esp\v6.0\esp-idf' -Baud 460800 flash

# Monitor hello world serial log
powershell -ExecutionPolicy Bypass -File .\tools\esp32\invoke-idf.ps1 -ProjectDir .\hello_world_project -IdfPath 'C:\esp\v6.0\esp-idf' monitor

# Build sample project
powershell -ExecutionPolicy Bypass -File .\tools\esp32\invoke-idf.ps1 -ProjectDir .\sample_project -IdfPath 'C:\esp\v6.0\esp-idf' build

# Flash sample project
powershell -ExecutionPolicy Bypass -File .\tools\esp32\invoke-idf.ps1 -ProjectDir .\sample_project -IdfPath 'C:\esp\v6.0\esp-idf' -Baud 460800 flash

# Monitor sample project
powershell -ExecutionPolicy Bypass -File .\tools\esp32\invoke-idf.ps1 -ProjectDir .\sample_project -IdfPath 'C:\esp\v6.0\esp-idf' monitor
```

Change `-ProjectDir` when the project folder moves. Change `-IdfPath` when the ESP-IDF folder moves. Pass `-Port COMx` when automatic serial-port selection is not appropriate.

## VS Code Tasks

The workspace already provides these tasks in `.vscode/tasks.json`:

- `ESP32: List Serial Ports`
- `ESP32: Build Hello World`
- `ESP32: Build Hello World (Debug Hold)`
- `ESP32: Flash Hello World`
- `ESP32: Monitor Hello World`
- `ESP32: Build Sample Project`
- `ESP32: Flash Sample Project`
- `ESP32: Monitor Sample Project`
- `ESP32: Build Custom Project`
- `ESP32: Flash Custom Project`
- `ESP32: Monitor Custom Project`
- `ESP32: Prepare Hello World Debug`
- `ESP32: Prepare Hello World Live Attach`
- `ESP32: Prepare Sample Project Debug`
- `ESP32: Prepare Sample Project Live Attach`
- `ESP32: Prepare Custom Project Debug`
- `ESP32: Prepare Custom Project Live Attach`
- `ESP32: OpenOCD Server`
- `ESP32: OpenOCD Server (Live Attach)`
- `ESP32: Load Hello World ELF`
- `ESP32: Load Sample Project ELF`

The build tasks now also force `CMAKE_EXPORT_COMPILE_COMMANDS=ON`, so a normal workspace build refreshes the compile database used by the root IntelliSense configuration.

Use `Terminal: Run Task` in VS Code to invoke them without typing the full command line.

## OpenOCD, ELF Load, and Debug

The repository supports both an explicit ELF-load step and a VS Code launch configuration.

Start OpenOCD from the repository root with:

```powershell
powershell -ExecutionPolicy Bypass -File .\tools\esp32\start-openocd.ps1 -IdfPath 'C:\esp\v6.0\esp-idf' -OpenOcdPath 'C:\Users\avala\.espressif\tools\openocd-esp32\v0.12.0-esp32-20251215\openocd-esp32\bin\openocd.exe' -OpenOcdScripts 'C:\Users\avala\.espressif\tools\openocd-esp32\v0.12.0-esp32-20251215\openocd-esp32\share\openocd\scripts' -OpenOcdConfig 'board/esp32s3-builtin.cfg' -AdapterSpeedKHz 5000
```

Load the hello world ELF over the GDB/OpenOCD connection with:

```powershell
powershell -ExecutionPolicy Bypass -File .\tools\esp32\load-elf.ps1 -ProjectDir .\hello_world_project -IdfPath 'C:\esp\v6.0\esp-idf' -GdbPath 'C:\Users\avala\.espressif\tools\xtensa-esp-elf-gdb\16.3_20250913\xtensa-esp-elf-gdb\bin\xtensa-esp32s3-elf-gdb.exe'
```

Or use the VS Code launch configurations in `.vscode/launch.json`:

- `ESP32S3: Hello World (Recommended Attach Running Firmware)`
- `ESP32S3: Hello World (Connect To Existing OpenOCD)`
- `ESP32S3: Hello World (Reset And Load)`
- `ESP32S3: Hello World (Manual OpenOCD)`
- `ESP32S3: Sample Project (Attach Running Firmware)`
- `ESP32S3: Sample Project (Connect To Existing OpenOCD)`
- `ESP32S3: Sample Project (Reset And Load)`
- `ESP32S3: Sample Project (Manual OpenOCD)`
- `ESP32S3: Custom Project (Attach Running Firmware)`
- `ESP32S3: Custom Project (Connect To Existing OpenOCD)`
- `ESP32S3: Custom Project (Reset And Load)`
- `ESP32S3: Template Project (Copy And Rename)`

The launch flow is:

1. Build the project.
2. For the reset-and-load profiles, VS Code runs a prepare task that builds the project and starts the plain OpenOCD server from the repository helper script. For hello world, that build uses `esp32Project.helloWorldDebugStartupHoldMs` to insert a temporary startup hold before normal app initialization.
3. For the attach-running profiles, VS Code runs a live-attach prepare task that builds the project and starts `ESP32: OpenOCD Server (Live Attach)`, which resumes the target after OpenOCD startup so GDB can halt application-side execution instead of inheriting the initial reset halt.
4. For the `Manual OpenOCD` profiles, start the OpenOCD server yourself first.
5. Launch the matching VS Code debug configuration.
6. VS Code connects GDB to `localhost:3333`. The reset-and-load profiles reset and halt the target, optionally load the ELF, set a temporary breakpoint at `app_main`, and continue. The `Recommended Attach Running Firmware` profile avoids reset-time breakpoint assumptions and halts the running target state after the live-attach OpenOCD startup path has released it.

For the live-attach path, the OpenOCD startup log can still show transient reset-halt lines while the `reset run` release sequence completes. The workspace task now waits for an explicit `ESP32_LIVE_ATTACH_READY` marker before it lets VS Code start GDB, so those intermediate log lines are expected and do not by themselves mean the chip is still stuck in reset.

The visual F5 flow now uses the ESP-IDF extension's native `gdbtarget` adapter instead of the Microsoft `cppdbg` adapter. This avoids the Xtensa `arch` error that can appear when `cppdbg` tries to infer the target architecture.

This stack does not use GEL files. The equivalent control points are the OpenOCD board configuration, the `initCommands` and `preRunCommands` passed to `gdbtarget`, and the ESP-IDF extension's own Peripheral View and Hex View inside the VS Code debug UI.

The workspace now vendors an ESP32-S3 SVD file at `.vscode/svd/esp32s3.svd` and points `idf.svdFilePath` at it, so `ESP-IDF: Peripheral View` has a real register description source. That view populates when the active `gdbtarget` debug session is stopped.

Because this repository root is not itself a single ESP-IDF project, the workspace-managed profiles are the recommended F5 path. They do not depend on the ESP-IDF extension recognizing the repository root as the active ESP-IDF project.

Use the matching `Attach Running Firmware` profile when the board is already flashed and you need the practical delivery path: attach to the current firmware, halt immediately, and use the normal VS Code Step, Next, Continue, Step Into, Disassembly, Variables, Watch, Call Stack, and ESP-IDF Peripheral or Hex views without relying on `app_main` being trapped during reset. These profiles explicitly set `initialBreakpoint` to an empty string so the ESP-IDF extension does not auto-inject `thb app_main` behind the scenes.

If the preLaunchTask-to-debug handoff in VS Code is the part that fails, use the matching `Connect To Existing OpenOCD` profile instead. Those profiles do not run any task. For late attach, start `ESP32: OpenOCD Server (Live Attach)` yourself first, wait until it reports `ESP32_LIVE_ATTACH_READY`, then launch the selected no-task profile to connect GDB directly to the existing OpenOCD server. Use the plain `ESP32: OpenOCD Server` task when you intentionally want the raw reset-oriented server behavior for manual reset-and-load work.

The workspace supports these debug panes and views through the standard VS Code debug UI plus the ESP-IDF extension:

- Breakpoints, Continue, Pause, Step Over, Step Into, and Step Out.
- Variables, Watch, and Call Stack.
- Disassembly view for instruction-level stepping.
- `ESP-IDF: Peripheral View`, backed by `.vscode/svd/esp32s3.svd` through `idf.svdFilePath`.
- `ESP-IDF: Hex View`, which can be populated from a stopped `gdbtarget` session by using `View As Hex` from the Variables context menu.

The ESP-IDF extension also contributes these non-debug views that can be useful in this workspace when the underlying feature is configured:

- `ESP-IDF Hints` in the bottom panel for build and flash error guidance.
- `Partition Table` in the ESP-IDF side bar when a partition table is defined.
- `App Trace` and `App Trace Archive` in the ESP-IDF side bar when app trace is enabled in firmware.
- `Components` in the Explorer area when component discovery is relevant to the opened folder.
- `ESP RainMaker` in the ESP-IDF side bar only if the project uses RainMaker.

To reopen an ESP-IDF view in VS Code, use `View: Open View...` and select the exact view name such as `ESP-IDF Peripheral View`, `ESP-IDF Hex View`, `ESP-IDF Hints`, `Partition Table`, or `App Trace`. VS Code stores visible view layout locally for the current machine and workspace, so once you open the views you want, the layout should be remembered for your local workspace state.

Repository files can recommend extensions and configure the debug session, but they cannot reliably force a specific set of views to stay pinned open because that visibility state is managed by VS Code as local user interface state rather than a stable shareable workspace setting.

The generic `Registers` and `Memory` panes that VS Code or the C/C++ extension can show are not populated by this workspace's current `gdbtarget` adapter flow, so an empty provider message there is expected. For this debug stack, use the GDB console, the ESP-IDF Peripheral View, and the ESP-IDF Hex View instead of treating those generic panes as the source of truth.

If you also have the PlatformIO extension installed, it contributes a separate `Peripherals`, `Registers`, `Memory`, and `Disassembly` group in the Debug view. Those PlatformIO panes are not wired to the ESP-IDF `gdbtarget` session used by this repository, so they stay empty here. The workspace now marks `platformio.platformio-ide` as an unwanted recommendation, but removing those duplicate panes from your UI still requires disabling PlatformIO for this workspace from VS Code if you want them gone entirely.

For the current ESP-IDF adapter, the only register tree that is actually backed by live target data is the `Registers` scope under `Variables`. The bottom `REGISTERS` pane from PlatformIO cannot be repointed to the ESP-IDF adapter by workspace settings.

The ESP-IDF Peripheral View is read-only in this adapter stack even for registers marked writable in the SVD. When you need to modify registers or memory during a stopped session, use the GDB console directly, for example:

```text
set $pc = 0x42000753
set *((volatile uint32_t *)0x6002C000) = 0x00000001
x/16wx 0x3FC88000
```

Use `ESP-IDF: Hex View` as the supported sidebar memory inspector for this workflow. It is populated from `Variables` by right-clicking a variable or expression and choosing `View As Hex`. For arbitrary address ranges, use the GDB console `x/...` commands with the validated memory regions listed below.

The `Watch` panel in VS Code is also not a reliable write path in this stack. A Watch entry is an evaluated expression, and VS Code can only edit it when the watched text is an assignable l-value in the current frame and the debug adapter successfully performs the corresponding write operation. In the current ESP-IDF `gdbtarget` flow, inspection works, but watch editing is not dependable for general variables, registers, or cast expressions. Use the GDB console instead, for example `set var some_variable = 1` or `set *((volatile uint32_t *)0x60004004) = 0x00000001`.

The workspace sets `debug.openDisassembly = auto` and `debug.disassemblyView.showSourceCode = true`, which is the closest supported VS Code behavior to keep the Disassembly view useful during debug stops. VS Code does not expose a workspace setting that forces the dedicated Disassembly pane to track every normal editor file selection outside debug-location changes.

For exact GDB commands to inspect or modify registers and memory in this workspace, see `docs/esp32-s3-gdb-cheat-sheet.md`.
For a peripheral-first register map reference, see `docs/esp32-s3-peripheral-cheat-sheet.md`.

### Suggested Memory Windows

The current `hello_world_project` and `sample_project` linker maps expose the same validated core memory regions, so these are the best default ranges to inspect when you open a memory view:

- DRAM data: `0x3FC88000`, length `0x53700`
- IRAM internal executable RAM: `0x40374000`, length `0x57700`
- Instruction-mapped flash: `0x42000020`, length `0x7FFFE0`
- Read-only mapped flash: `0x3C000020`, length `0x1FFFFE0`
- RTC IRAM: `0x600FE000`, length `0x1FE8`
- RTC slow memory: `0x50000000`, length `0x2000`

These values come from the generated linker maps for the current ESP32-S3 builds. External RAM is not a default inspection window because the current validated builds do not enable PSRAM.

On this host, the ESP32-S3 built-in USB-JTAG link was unstable at the default 40000 kHz OpenOCD speed and produced `esp_usb_jtag` buffer overflows plus dropped GDB sockets. The workspace OpenOCD tasks are therefore pinned to `esp32Project.openOcdAdapterSpeedKHz = 5000` for the recommended root-workspace debug flow.

During live validation, the lower-speed path stabilized OpenOCD startup and GDB attach, but the GDB-driven soft-reset path still halted back in ROM around `0x40041A79` and `0x40041A7C` and did not yet prove a stop at `app_main`. If you need to catch early startup code on this board, prefer the attach-only profiles and use a manual board reset after the debugger is attached.

If a manual reset causes transient `libusb_bulk_write` or `missing data from bitq interface` errors but OpenOCD later reexamines the target and halts at `0x40378AEE`, that is a different state: `0x40378AEE` resolves inside the application ELF to `esp_cpu_wait_for_intr`, which means the application progressed into its idle wait path after reset. In that case the remaining limitation is more likely early-breakpoint loss across USB-JTAG reenumeration than a failure to boot the application.

For the hello world project, the repository now includes a debug-only startup hold near the top of `app_main`. The regular build task explicitly disables it, while the hello world debug-prepare task enables it through a CMake cache definition so the VS Code attach path has a practical window to reconnect after reset.

## Debugging New Projects Without Editing launch.json

You do not need to add every new ESP-IDF project to `.vscode/launch.json`.

Use the generic entries instead:

1. Run `Terminal: Run Task` and choose `ESP32: Build Custom Project`.
2. If needed, run `ESP32: Flash Custom Project`.
3. Open `Run and Debug` and launch either `ESP32S3: Custom Project (Attach Running Firmware)` or `ESP32S3: Custom Project (Reset And Load)`.
4. When prompted, enter the workspace-relative project folder, for example `my_new_project`, and the ELF file name inside `build/`, for example `my_new_project.elf`.

That is enough when the new project uses the same ESP-IDF tools, GDB, and OpenOCD board configuration as the rest of this workspace.

If you want a permanent named profile for the new project instead of prompt-driven inputs, duplicate `ESP32S3: Template Project (Copy And Rename)` in `.vscode/launch.json`, rename it, and replace `template_project` with your real folder and ELF names.

You only need to change JSON or settings when one of these changes:

- The ESP-IDF installation path changes.
- The GDB or OpenOCD executable paths change.
- The target board needs a different `openOcdConfig`.
- You want a permanent named launch profile for a project instead of using the generic prompt-based one.

If the board changes, update `esp32Project.openOcdConfig`. If the tool locations change, update `esp32Project.openOcdPath`, `esp32Project.openOcdScripts`, and `esp32Project.gdbPath`.

## Required Tools

The validated setup uses:

- ESP-IDF 6.0 with the installed Python environment and Xtensa ESP32-S3 toolchain
- OpenOCD for ESP32
- Xtensa ESP32-S3 GDB
- VS Code extension `espressif.esp-idf-extension`
- VS Code extension `ms-vscode.cpptools`
- VS Code extension `ms-vscode.hexeditor`

For serial flash and monitor, a working USB serial connection is enough. For OpenOCD and GDB debugging, the target and chosen `openOcdConfig` must expose a supported debug path.
