# sample_project

Sample application folder that shows how a project can sit beside the shared libraries.

- Use this folder as the reference shape for new projects.
- Keep project code module-based and nested where needed.
- Keep project-specific unit tests isolated in [test/README.md](test/README.md).
- Open this folder directly as an ESP-IDF project when building or debugging on target hardware.
- The standalone ESP-IDF project reuses `../common_utils`, `../common_os`, and `../common_driver` as shared components.
- Use the workspace tasks or `tools/esp32/invoke-idf.ps1` to build, flash, and monitor the project.
