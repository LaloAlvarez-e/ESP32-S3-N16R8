# Embedded Review Checklist

## Function Structure

- Does the function return an error code?
- Is there a single return statement?
- Are outputs provided through output parameters?
- Are locals initialized immediately?
- Are outputs set to a safe default when needed?

## Error Handling

- Is each fallible step guarded by `if (ERROR_OK == eError)`?
- Are cleanup failures handled without hiding the primary failure?
- Are null, bounds, and state validations explicit?

## Resource Management

- Are init and deinit paths visible in the function?
- Is every acquisition paired with cleanup?
- Is the cleanup block reachable for all relevant failure paths?

## Naming and Constants

- Do static functions use `<module>_<what_does>`?
- Do global functions use the project global naming rule?
- Are variable prefixes consistent with their types?
- Are literal constants replaced with named values?

## Documentation

- Is there a Doxygen block?
- Are parameter directions documented?
- Is the return error code described?
