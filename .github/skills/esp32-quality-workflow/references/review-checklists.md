# ESP32 Workflow Review Checklists

## Debugging Checklist

- Is the failing path reproducible with explicit steps?
- Can the state transition be observed in GDB or logs?
- Are intermediate variables named clearly enough for watch expressions?
- Is the suspected fault narrowed to one component or one call chain?

## GoogleTest Checklist

- Does the test compile the real production implementation under test?
- Are production headers used unchanged?
- Are called dependencies mocked at the implementation level instead of replacing the public header contract?
- Is `UNIT_TEST` used only to enable test-specific visibility or overrides?
- Are `STATIC` and `WEAK` style test macros constrained to the test build?
- Is the test located inside the owning project or common library folder?
- Is the test project isolated from other test projects?
- Is the logic isolated from hardware dependencies?
- Are success, boundary, and failure cases all covered?
- Are cleanup behaviors or resource releases tested when relevant?
- Do expectations verify error codes and observable outputs?

## Doxygen Checklist

- Are all parameters documented with direction tags?
- Is the return error model documented?
- Are ownership or lifetime expectations stated when needed?
- Do comments explain intent rather than restating code?
