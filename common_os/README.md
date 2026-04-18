# common_os

Shared RTOS or operating-system abstraction library root.

- Build this folder as a static library.
- Keep project override hooks explicit and weak where needed.
- Use [common_os.h](common_os.h) as the folder-level aggregator header.
- Keep unit tests isolated in [test/README.md](test/README.md).
