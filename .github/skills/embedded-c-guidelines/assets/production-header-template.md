# Production Header Template

Use this template for production headers that need explicit unit-test seams without changing the public contract.

```c
#ifndef MODULE_NAME_H
#define MODULE_NAME_H

#include <stdint.h>

#if !defined(STATIC)
#if defined(UNIT_TEST)
#define STATIC
#else
#define STATIC static
#endif
#endif

#if !defined(WEAK)
#if defined(UNIT_TEST)
#define WEAK
#else
#define WEAK __attribute__((weak))
#endif
#endif

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @brief Module status codes.
 */
typedef enum module_error
{
    MODULE_ERROR_OK = 0,
    MODULE_ERROR_INVALID_ARGUMENT = 1,
    MODULE_ERROR_DEPENDENCY = 2
} module_error_t;

/**
 * @brief Module context.
 */
typedef struct module_context
{
    uint32_t u32Reserved;
} module_context_t;

/**
 * @brief Optional platform or test override hook.
 * @param[in] pxContext Module context.
 * @return MODULE_ERROR_OK on success, otherwise an error code.
 */
WEAK module_error_t module__platform_hook(module_context_t* pxContext);

/**
 * @brief Initialize the module context.
 * @param[out] pxContext Module context to initialize.
 * @return MODULE_ERROR_OK on success, otherwise an error code.
 */
module_error_t module__init(module_context_t* pxContext);

/**
 * @brief Execute one module operation.
 * @param[in] pxContext Initialized module context.
 * @param[in] u32Input Input value.
 * @param[out] pu32Output Output value.
 * @return MODULE_ERROR_OK on success, otherwise an error code.
 */
module_error_t module__run(module_context_t* pxContext,
                           uint32_t u32Input,
                           uint32_t* pu32Output);

#ifdef __cplusplus
}
#endif

#endif
```

Guidance:

- Define `UNIT_TEST` only in the unit-test target.
- Keep the production header identical in production and test builds.
- Use `STATIC` only for internal helpers that must become externally visible in unit tests.
- Use `WEAK` only on explicit override points.
