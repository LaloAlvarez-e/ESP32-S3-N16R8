# Plan

## Goal

Add a standalone ESP-IDF hello-world project that can build an ELF, flash or load it to an ESP32-S3 target, and start a GDB debug session from VS Code on Windows.

## Planned Artifacts

1. Standalone device project folder `esp32s3_hello_world/`
   - `CMakeLists.txt`
   - `README.md`
   - `sdkconfig.defaults`
   - `main/CMakeLists.txt`
   - `main/main.c`
2. Workspace debug assets in `.vscode/`
   - `settings.json`
   - `tasks.json`
   - `launch.json`
3. Windows helper scripts in `tools/esp32/`
   - `invoke-idf.ps1`
   - `start-openocd.ps1`
   - `load-elf.ps1`
4. Root documentation update in `README.md`
   - Short section describing the device project and debug workflow

## Design Decisions

- Keep the ESP-IDF project standalone and do not add it to the root host-side `CMakeLists.txt`.
- Use a dedicated device project folder rather than reusing `sample_project/`.
- Parameterize tool locations through workspace settings instead of assuming PATH setup.
- Prefer direct `openocd.exe` invocation for VS Code tasks and keep `idf.py` for build and serial flashing.
