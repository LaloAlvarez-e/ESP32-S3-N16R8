# Doxygen Function Template

```cpp
/**
 * @brief Short action-focused summary.
 * @param[in] xContext Module or driver context.
 * @param[in] u32Input Input value or configuration.
 * @param[out] xOutput Output result.
 * @return ERROR_OK on success, otherwise an error code describing the failure.
 * @pre The caller provides a valid initialized context.
 */
error_t module__perform_operation(const module_context_t& xContext,
                                  uint32_t u32Input,
                                  module_result_t& xOutput);
```
