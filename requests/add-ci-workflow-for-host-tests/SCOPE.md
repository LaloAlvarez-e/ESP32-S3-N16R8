# Scope

## In Scope

- Add a GitHub Actions workflow for the existing host-side GoogleTest build.
- Reuse the repository's validated CMake and CTest flow.
- Track the request in a new `requests/` folder.

## Out of Scope

- Adding device-side ESP-IDF CI jobs.
- Expanding the host matrix beyond the validated Windows and MSVC flow.
- Refactoring production or test code unrelated to CI execution.

## Delivered

- Added `.github/workflows/host-side-tests.yml` for automatic host-side CMake test execution.
- Reused the validated Windows, Visual Studio 2022, x64, Release command path.
- Recorded the request state and validation result in the new tracker folder.
