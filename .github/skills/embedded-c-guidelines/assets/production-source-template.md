# Production Source Template

Use this template for production source files that need explicit `UNIT_TEST`, `STATIC`, and `WEAK` seams while keeping the production implementation under test.

```c
#include "module_name.h"

#include <stdbool.h>
#include <stddef.h>

/**
 * @brief Validate one module input.
 * @param[in] u32Input Input value.
 * @return MODULE_ERROR_OK on success, otherwise an error code.
 */
STATIC module_error_t module_validate_input(uint32_t u32Input);

/**
 * @brief Deinitialize local module resources.
 * @param[in] pxContext Module context.
 */
STATIC void module_cleanup(module_context_t* pxContext);

/**
 * @brief Validate one module input.
 * @param[in] u32Input Input value.
 * @return MODULE_ERROR_OK on success, otherwise an error code.
 */
STATIC module_error_t module_validate_input(uint32_t u32Input)
{
    module_error_t eError = MODULE_ERROR_OK;

    if (0U == u32Input)
    {
        eError = MODULE_ERROR_INVALID_ARGUMENT;
    }

    return eError;
}

/**
 * @brief Deinitialize local module resources.
 * @param[in] pxContext Module context.
 */
STATIC void module_cleanup(module_context_t* pxContext)
{
    (void)pxContext;
}

/**
 * @brief Optional platform or test override hook.
 * @param[in] pxContext Module context.
 * @return MODULE_ERROR_OK on success, otherwise an error code.
 */
WEAK module_error_t module__platform_hook(module_context_t* pxContext)
{
    module_error_t eError = MODULE_ERROR_OK;

    (void)pxContext;

    return eError;
}

/**
 * @brief Initialize the module context.
 * @param[out] pxContext Module context to initialize.
 * @return MODULE_ERROR_OK on success, otherwise an error code.
 */
module_error_t module__init(module_context_t* pxContext)
{
    module_error_t eError = MODULE_ERROR_OK;

    if (NULL == pxContext)
    {
        eError = MODULE_ERROR_INVALID_ARGUMENT;
    }

    if (MODULE_ERROR_OK == eError)
    {
        pxContext->u32Reserved = 0U;
    }

    return eError;
}

/**
 * @brief Execute one module operation.
 * @param[in] pxContext Initialized module context.
 * @param[in] u32Input Input value.
 * @param[out] pu32Output Output value.
 * @return MODULE_ERROR_OK on success, otherwise an error code.
 */
module_error_t module__run(module_context_t* pxContext,
                           uint32_t u32Input,
                           uint32_t* pu32Output)
{
    module_error_t eError = MODULE_ERROR_OK;
    bool bCleanupRequired = false;

    if ((NULL == pxContext) || (NULL == pu32Output))
    {
        eError = MODULE_ERROR_INVALID_ARGUMENT;
    }

    if (MODULE_ERROR_OK == eError)
    {
        *pu32Output = 0U;
    }

    if (MODULE_ERROR_OK == eError)
    {
        eError = module_validate_input(u32Input);
    }

    if (MODULE_ERROR_OK == eError)
    {
        eError = module__platform_hook(pxContext);
    }

    if (MODULE_ERROR_OK == eError)
    {
        bCleanupRequired = true;
        *pu32Output = u32Input;
    }

    if (true == bCleanupRequired)
    {
        module_cleanup(pxContext);
    }

    return eError;
}
```

Guidance:

- Keep `STATIC` helpers in the real production source so unit tests can expose them only when `UNIT_TEST` is defined.
- Keep `WEAK` override points explicit and narrow.
- Compile this production source directly into the unit-test target; mock only the called collaborators or override points.
