# Scope

## In Scope

- Add GoogleTest and GoogleMock CMake support to the repository.
- Add isolated host-side test targets inside each existing `test/` folder.
- Compile the real production implementation under test into each test target.
- Use symbol-level mocks for sample-project dependency seams.
- Maintain the required request-tracking files for this request.

## Out of Scope

- Adding ESP-IDF device-side tests.
- Refactoring the production modules beyond what is needed for host-side test integration.
- Sharing test code across unrelated project roots.

## Delivered

- Root-level GoogleTest and CTest integration with central dependency setup.
- Local `test/` CMake targets under `common_utils`, `common_os`, `common_driver`, and `sample_project`.
- Host-side GoogleTest coverage for the production modules in each root.
