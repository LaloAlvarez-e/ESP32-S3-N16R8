# Embedded Function Template

Use this template for new or heavily refactored functions.

```cpp
/**
 * @brief Perform the module operation.
 * @param[in] xContext Module context.
 * @param[in] u32Input Input value.
 * @param[out] xOutput Output result.
 * @return ERROR_OK on success, otherwise an error code.
 */
error_t module__perform_operation(const module_context_t& xContext,
                                  uint32_t u32Input,
                                  module_result_t& xOutput)
{
    error_t eError = ERROR_OK;
    bool bResourceInitialized = false;
    module_local_state_t xLocalState = {};

    xOutput = {};

    if (ERROR_OK == eError)
    {
        eError = module__validate_input(xContext, u32Input);
    }

    if (ERROR_OK == eError)
    {
        eError = module__init_local_state(xContext, xLocalState);
    }

    if (ERROR_OK == eError)
    {
        bResourceInitialized = true;
        eError = module__execute_step(xLocalState, u32Input, xOutput);
    }

    if (true == bResourceInitialized)
    {
        error_t eCleanupError = module__deinit_local_state(xLocalState);
        if ((ERROR_OK == eError) && (ERROR_OK != eCleanupError))
        {
            eError = eCleanupError;
        }
    }

    return eError;
}
```
