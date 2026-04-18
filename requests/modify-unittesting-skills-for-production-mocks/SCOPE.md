# Scope

## In Scope

- Define production-code unit-testing rules in the repository skill.
- Define implementation-only mocking rules for GoogleTest and GoogleMock.
- Document `UNIT_TEST`, `STATIC`, and `WEAK` test-build patterns.
- Define local `test/` folder placement inside each owning project or common library.
- Update the GoogleTest template and related references.

## Out of Scope

- Creating actual test projects under `common_utils/`, `common_os/`, `common_driver/`, or application folders.
- Adding real production code changes for `UNIT_TEST`, `STATIC`, or `WEAK` usage.
- Adding build-system integration for GoogleTest in this request.
