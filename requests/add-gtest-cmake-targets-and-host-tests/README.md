# Request README

## Request

Add real GoogleTest CMake targets inside each local `test/` folder so the repository can build and run host-side unit tests.

## Current Result

Completed. The repository now builds host-side GoogleTest targets from each local `test/` folder, and the validated CTest run passed 30 of 30 tests.

## Validation

- Configure/build: `cmake -S . -B <build-dir> -DBUILD_TESTING=ON`
- Test run: `ctest --test-dir <build-dir> -C Release --output-on-failure`
