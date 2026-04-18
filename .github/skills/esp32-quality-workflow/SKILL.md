---
name: esp32-quality-workflow
description: 'ESP32 embedded workflow guidance for ESP-IDF toolchains, project architecture trees, static common libraries, GDB debugging, GoogleTest and GoogleMock unit testing with production code, Doxygen documentation, and code comments. Use when building, debugging, testing, documenting, or structuring ESP32 firmware work.'
argument-hint: 'Apply ESP32 debugging, testing, and documentation workflow guidance'
user-invocable: true
disable-model-invocation: false
---

# ESP32 Quality Workflow

## When to Use

- Working on ESP32 or ESP32-S3 firmware tasks
- Setting up or troubleshooting toolchain-driven builds
- Preparing code for debugger use
- Adding or updating GoogleTest unit tests
- Adding Doxygen or targeted implementation comments

## Workflow

1. Identify whether the task is primarily debugging, testing, or documentation.
2. Keep the implementation aligned with the embedded coding rules skill.
3. For unit tests, compile the real production code under test and keep the production headers unchanged.
4. Mock called dependencies at the implementation or symbol level only.
5. Use the available templates when adding tests or function documentation.
6. Review the result with the workflow-specific checklist before finishing.

## Toolchain Expectations

- Prefer workflows that stay compatible with ESP32 toolchains, especially ESP-IDF project structure, build flags, and debugger support.
- Keep compile-time options explicit and avoid hiding hardware behavior behind fragile macros.
- Favor code organization that separates hardware-dependent logic from testable business logic.

## Project Layout Expectations

- Structure the repository around reusable common libraries and project-specific application folders.
- `common_utils/` must be a static library for shared utility code.
- `common_os/` must be the project RTOS layer, built as a static library.
- `common_os/` must expose weak functions and callbacks that each project can initialize or override.
- `common_driver/` must be a static library for board drivers and peripherals shared across projects.
- Project-specific applications live in their own folders such as `project_name/`, and the repository may contain many of them.
- Inside each project, split code again by modules and nested submodules.
- Each module folder must provide a folder-level header that aggregates the headers in that folder.
- Use [references/project-architecture-tree.md](./references/project-architecture-tree.md) when creating or reviewing project structure.

## Debugging Expectations

- Write code that is easy to inspect in GDB: simple control flow, explicit state variables, and named intermediate values.
- Preserve meaningful error codes and state transitions so debugger sessions show where failure occurred.
- Avoid compact expressions that make stepping difficult.
- When debugging changes, prefer recommendations that can be validated with breakpoints, watch expressions, and deterministic repro steps.

## Unit Testing Expectations

- Prefer GoogleTest with GoogleMock for host-side unit tests around deterministic logic.
- Unit tests must build and execute the real production implementation under test.
- Production headers must be included as-is in unit tests.
- Do not create alternate test-only public headers for the module under test.
- Any called dependency of the unit under test must be mocked when unit isolation requires it.
- Mock only the implementation or linked symbol, not the header contract.
- Use `UNIT_TEST` compile-time defines to distinguish production and test-only build behavior when needed.
- Use test-aware macros such as `STATIC` and `WEAK` so internal functions can be exposed or override points can be replaced only in the test build.
- Keep test-specific macro use narrow and explicit; production behavior must remain the default behavior.
- Place test code inside the owning library or project folder, for example `common_utils/test/`, `common_os/test/`, `common_driver/test/`, or `project_name/test/`.
- Each test project must be isolated from the others and must not depend on another project's test code.
- Isolate transport, HAL, and peripheral interactions behind seams that can be mocked deterministically.
- Test error paths, boundary conditions, and cleanup behavior, not only success cases.
- Keep tests readable and aligned with the production naming and error-handling model.

## Documentation and Comments

- Every function must have Doxygen documentation.
- Comments in implementation should explain intent, safety rationale, hardware assumptions, or unusual constraints.
- Avoid comments that merely restate the code.
- Keep public interfaces documented so generated documentation stays useful as the project grows.

## Templates and References

- GoogleTest template: [assets/gtest-case-template.md](./assets/gtest-case-template.md)
- Unit test config macros: [assets/unit-test-config-template.md](./assets/unit-test-config-template.md)
- Doxygen template: [assets/doxygen-function-template.md](./assets/doxygen-function-template.md)
- Project architecture tree: [references/project-architecture-tree.md](./references/project-architecture-tree.md)
- Unit testing rules: [references/unit-testing-rules.md](./references/unit-testing-rules.md)
- Debug, test, and documentation review lists: [references/review-checklists.md](./references/review-checklists.md)

## Preferred Task Output

When completing ESP32 firmware work, aim to leave behind:

- Implementation that follows the embedded coding rules skill
- Doxygen on changed functions
- Tests or a clearly identified test gap
- Debuggable control flow and error propagation