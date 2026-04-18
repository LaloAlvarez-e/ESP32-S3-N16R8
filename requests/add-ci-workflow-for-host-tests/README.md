# Request README

## Request

Add a CI workflow that runs the same host-side test matrix automatically.

## Current Result

Completed. The repository now has a GitHub Actions workflow that runs the validated Windows and MSVC host-side CMake test flow automatically on push, pull request, and manual dispatch.

## Validation

- Configure: `cmake -S . -B build/host-tests -G "Visual Studio 17 2022" -A x64 -DBUILD_TESTING=ON`
- Build: `cmake --build build/host-tests --config Release --parallel`
- Test: `ctest --test-dir build/host-tests -C Release --output-on-failure`
