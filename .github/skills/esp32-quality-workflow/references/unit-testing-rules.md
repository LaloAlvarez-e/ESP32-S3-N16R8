# Unit Testing Rules

## Core Policy

- Unit tests must compile and execute the real production code under test.
- Public production headers must be used unchanged.
- Do not create alternate test-only versions of public headers.

## Mocking Policy

- When the unit under test calls another function, mock that dependency for the test when isolation is required.
- Mock the implementation or linked symbol only.
- Keep the header contract unchanged so the unit test validates the real production interface.
- Prefer GoogleMock-backed symbol overrides or weak-link override points over rewriting production APIs.

## Test Build Macros

- Use `UNIT_TEST` to identify test-only build behavior.
- Use a `STATIC` macro to expose internal functions only in the test build when necessary.
- Use a `WEAK` macro for explicit override points that must be replaced in tests or projects.
- Keep those macros deterministic and limited to controlled test seams.

## Test Location Rules

- Place unit tests inside the owning folder.
- Examples:
  - `common_utils/test/`
  - `common_os/test/`
  - `common_driver/test/`
  - `project_name/test/`
- Each test project must be isolated from every other test project.
- Do not share test-only sources across unrelated projects unless they are promoted into a real common test utility owned intentionally by the repository.

## Test Design Rules

- Prefer one unit-test target per owning project or shared library.
- Exercise success paths, boundary conditions, failure paths, and cleanup behavior.
- Keep mocks explicit so it is obvious which collaborators are replaced.
- Avoid hidden integration with hardware, RTOS primitives, or unrelated modules.
