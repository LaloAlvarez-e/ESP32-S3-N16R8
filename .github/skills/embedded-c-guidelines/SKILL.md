---
name: embedded-c-guidelines
description: 'Embedded C/C++ MISRA-oriented coding rules for ESP32 firmware. Use when writing or reviewing functions, naming APIs, defining module folder architecture, adding production header or source templates, applying UNIT_TEST and STATIC/WEAK seams, aggregating headers, applying yoda conditions, enforcing single-return cleanup, returning error codes, documenting with Doxygen, avoiding magic numbers, and applying variable prefixes.'
argument-hint: 'Apply embedded firmware coding rules to this task'
user-invocable: true
disable-model-invocation: false
---

# Embedded C/C++ Coding Guidelines

## When to Use

- Writing or refactoring embedded C or C++ source files
- Reviewing code for MISRA-oriented structure and naming
- Adding new APIs, helper functions, or module-level logic
- Normalizing error-handling, cleanup, documentation, and parameter usage

## Workflow

1. Read the task and identify the affected module boundary and resource ownership points.
2. Apply the function structure and naming rules from this skill.
3. Use the reusable code patterns in [assets/function-template.md](./assets/function-template.md), [assets/production-header-template.md](./assets/production-header-template.md), and [assets/production-source-template.md](./assets/production-source-template.md) when creating or rewriting modules.
4. Review the result with [references/review-checklist.md](./references/review-checklist.md) before finishing the task.

## Module Architecture Rules

- Organize implementation by module folders instead of flat source lists.
- Treat every folder as a module boundary.
- Each folder must provide a folder-level header that aggregates the public headers in that folder.
- Keep dependencies vertical inside a single branch of the tree.
- Nested modules must not include or call APIs from parent folders.
- Sibling modules must not depend on each other directly.
- Parent modules may expose nested module APIs upward through their own folder-level header.
- Use [references/module-architecture.md](./references/module-architecture.md) when creating or reviewing folder layouts.

## Core Rules

1. Use Yoda conditions for comparisons with constants and enum values.
2. Use a single return statement per function.
3. Make the function return value an error or status code, not the business data.
4. Model outputs as output parameters.
5. Initialize local state at the beginning of the function.
6. Release or deinitialize owned resources at the end of the function before the single return.
7. Wrap each function call in an error-gated control block.
8. Add Doxygen documentation for every function.
9. Do not use magic numbers.
10. Prefix variable names with the variable type/category.
11. Structure source trees by module folders with one aggregator header per folder.
12. Keep dependency direction vertical only, with no sibling-to-sibling coupling.

## Required Patterns

### Error Handling

- All normal functions must return a project error or status code.
- Return data through output parameters.
- Keep one local error variable for the function and return it once at the end.

Example pattern:

```cpp
error_t eError = ERROR_OK;

if (ERROR_OK == eError)
{
    eError = module__do_step(xContext, u32Value, xResult);
}

if (ERROR_OK == eError)
{
    eError = module__do_next_step(xContext, xResult);
}

module__deinit(xContext);
return eError;
```

### Output Parameters

- Treat outputs as reference-style parameters.
- In C++ code, use references for output parameters when practical.
- In C code, use pointer output parameters with explicit null checks because the language has no references.
- Do not return payload values directly unless a language construct requires it.

### Initialization and Cleanup

- Initialize all locals immediately after declaration.
- Set output parameters to a safe default as early as possible after validation.
- Pair every acquisition or init path with a visible cleanup or deinit path near the end of the function.
- The single return statement must come after cleanup.

### Function Call Guarding

- Calls that can fail must appear inside an error check block.
- Preferred pattern:

```cpp
if (ERROR_OK == eError)
{
    eError = module__action(xContext, u32Value, xOutput);
}
```

- Do not chain complex calls in conditions.
- Keep each step explicit so failures are easy to debug.

### Naming Rules

- Static or local-scope functions must follow the pattern `<module>_<what_does>`.
- Global functions must follow the requested project pattern `<module>__<what_does>`.
- Keep names descriptive and action-oriented.

Portability note:
- The requested double-underscore convention is reserved by the C++ standard. If code must remain strictly portable as C++, prefer revisiting that specific rule before broad adoption.

### Variable Prefix Rules

Use explicit prefixes that describe the stored type or category. Examples:

- `u8`, `u16`, `u32`, `u64` for unsigned integers
- `s8`, `s16`, `s32`, `s64` for signed integers
- `f` for `float`
- `d` for `double`
- `p` for pointers
- `x` for structs or object-like aggregates
- `en` for enum elements or enum-typed values
- `n` for general numeric or count-style values when a fixed-width prefix is not used
- `v` for void-style placeholders or opaque handles when appropriate to the codebase
- `a` for arrays

Keep the prefix followed by a meaningful name, for example `u32RetryCount`, `pBuffer`, `xConfig`, `enMode`.

### Magic Numbers

- Replace literal constants with named constants, enums, or `constexpr` values.
- Hardware register fields, delays, sizes, retry counts, and protocol values must be named.

### Doxygen Rules

Every function must have a Doxygen block that documents:

- Purpose
- Parameters
- Output parameters
- Return error/status code
- Preconditions or resource expectations when relevant

Example:

```cpp
/**
 * @brief Initialize the UART transport context.
 * @param[in] xConfig UART configuration.
 * @param[out] xContext Initialized transport context.
 * @return ERROR_OK on success, otherwise an error code.
 */
error_t uart__init(const uart_config_t& xConfig, uart_context_t& xContext);
```

## Review Checklist

- Does the function return an error code?
- Is there exactly one return statement?
- Are outputs provided through output parameters?
- Are locals initialized at the start?
- Is cleanup or deinit visible before return?
- Is every fallible call guarded by `if (ERROR_OK == eError)`?
- Does the function follow naming rules?
- Are variable prefixes consistent?
- Are all constants named?
- Does the function include Doxygen?

## References

- Reusable function skeleton: [assets/function-template.md](./assets/function-template.md)
- Production header template: [assets/production-header-template.md](./assets/production-header-template.md)
- Production source template: [assets/production-source-template.md](./assets/production-source-template.md)
- Expanded review checklist: [references/review-checklist.md](./references/review-checklist.md)
- Module architecture reference: [references/module-architecture.md](./references/module-architecture.md)