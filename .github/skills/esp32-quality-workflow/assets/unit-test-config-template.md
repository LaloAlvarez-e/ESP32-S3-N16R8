# Unit Test Config Template

Use this pattern in production headers or shared compile configuration when unit tests need controlled visibility changes.

```c
#ifdef UNIT_TEST
#define STATIC
#define WEAK
#else
#define STATIC static
#define WEAK __attribute__((weak))
#endif
```

Guidance:

- Build the production source under test with `UNIT_TEST` defined only in the unit-test target.
- Use `STATIC` only where internal functions must be exposed for unit-test access.
- Use `WEAK` only on explicit override points that tests or projects may replace.
- Do not let test-only macro behavior leak into the normal production build.
