# Project Architecture Tree

## Top-Level Layout

```text
common_utils/
    test/
common_os/
    test/
common_driver/
    test/
project_name/
    test/
project_name_2/
    test/
```

## Top-Level Folder Rules

- `common_utils/` is a static library for reusable utility code.
- `common_utils/test/` contains the isolated unit-test project for `common_utils/`.
- `common_os/` is the RTOS abstraction or operating system layer for the repository.
- `common_os/` must be shared as a static library.
- `common_os/` must expose weak functions and callbacks that are initialized or overridden by each project.
- `common_os/test/` contains the isolated unit-test project for `common_os/`.
- `common_driver/` is a static library for board drivers and peripheral access.
- `common_driver/test/` contains the isolated unit-test project for `common_driver/`.
- `project_name/` represents one application or firmware project.
- `project_name/test/` contains the isolated unit-test project for that application.
- The repository may contain as many project folders as needed.

## Per-Project Layout

```text
project_name/
    main.c
    main.h
    test/
    xModule/
        xSource1.c
        xSource1.h
        xSubModule/
            xSubSource.c
            xSubSource.h
            xNestedModule/
            xSubModule.h
        xModule.h
```

## Per-Project Rules

- `main.c` and `main.h` are optional and only exist when the project needs a main entrypoint layer.
- `test/` is optional only when the project truly has no host-side unit tests yet; when unit tests exist, they must stay inside the owning folder.
- Every folder is a module.
- Every module folder must provide a folder-level header named after the folder.
- The folder-level header aggregates the headers inside that folder.
- Nested folders are nested submodules.

## Dependency Rules

- Dependencies must stay vertical within one branch of the folder tree.
- Nested modules must not depend on parent-folder APIs.
- Nested modules must not depend on sibling-folder APIs.
- Parent folders may compose or re-export nested module APIs through their own folder-level header.
- Avoid hidden sideways dependencies between peer modules.
- Test folders must not depend on test code from other projects or common libraries.

## Unit Testing Layout Notes

- Tests must compile the real production sources they are validating.
- Tests must include the production headers as-is.
- Tests may override linked behavior through mocks, weak symbols, or test-only visibility macros.
- Test-specific helpers must remain inside the local `test/` folder of the owning project or library.

## Intent

This layout keeps shared utilities, RTOS integration, drivers, and project-specific logic separated while preserving a consistent module hierarchy across all ESP32 projects in the repository.
