# Plan

## Objective

Add real GoogleTest CMake targets inside each local `test/` folder so the repository can build and run host-side unit tests against the real production code.

## Steps

1. [x] Add root-level GoogleTest and CTest setup in CMake.
2. [x] Add per-folder `test/CMakeLists.txt` files.
3. [x] Add real host-side unit tests that compile the production `.c` files directly with `UNIT_TEST` enabled.
4. [x] Build and run the tests, then update the request tracker.

## Validation

- Configure and build with `cmake -S . -B <build-dir> -DBUILD_TESTING=ON` succeeded on MSVC.
- `ctest --test-dir <build-dir> -C Release --output-on-failure` passed with 30 of 30 tests.
