# common_driver

Shared board-driver and peripheral library root.

- Build this folder as a static library.
- Keep hardware-facing modules separated by driver folder.
- Use [common_driver.h](common_driver.h) as the folder-level aggregator header.
- Keep unit tests isolated in [test/README.md](test/README.md).
