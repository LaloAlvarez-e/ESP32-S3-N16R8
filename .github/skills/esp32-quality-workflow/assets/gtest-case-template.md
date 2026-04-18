# GoogleTest Case Template

```cpp
/**
 * @brief Example GoogleTest and GoogleMock structure for production-code unit testing.
 */

#define UNIT_TEST

#include <gmock/gmock.h>
#include <gtest/gtest.h>

extern "C"
{
#include "module.h"
#include "dependency.h"
}

namespace
{
class dependency_mock
{
public:
    MOCK_METHOD(error_t, dependency__read, (const dependency_context_t* pxContext,
                                            uint32_t u32Input,
                                            dependency_result_t* pxResult));
};

static dependency_mock* gpDependencyMock = nullptr;

extern "C" error_t dependency__read(const dependency_context_t* pxContext,
                                     uint32_t u32Input,
                                     dependency_result_t* pxResult)
{
    return gpDependencyMock->dependency__read(pxContext, u32Input, pxResult);
}

class module_test : public ::testing::Test
{
protected:
    void SetUp() override
    {
        xContext = {};
        eError = ERROR_OK;
        gpDependencyMock = &xDependencyMock;
    }

    void TearDown() override
    {
        gpDependencyMock = nullptr;
    }

    module_context_t xContext;
    error_t eError;
    dependency_mock xDependencyMock;
};

TEST_F(module_test, returns_error_when_input_is_invalid)
{
    module_result_t xOutput = {};

    eError = module__perform_operation(xContext, 0U, xOutput);

    EXPECT_EQ(ERROR_INVALID_ARGUMENT, eError);
}

TEST_F(module_test, returns_success_for_valid_input)
{
    module_result_t xOutput = {};
    dependency_result_t xDependencyResult = {};

    EXPECT_CALL(xDependencyMock, dependency__read(testing::_, 1U, testing::_))
        .WillOnce(testing::DoAll(
            testing::SetArgPointee<2>(xDependencyResult),
            testing::Return(ERROR_OK)));

    eError = module__perform_operation(xContext, 1U, xOutput);

    EXPECT_EQ(ERROR_OK, eError);
}
}  // namespace
```

Rules shown in this template:

- The production headers are included directly.
- The production implementation under test is the code being compiled.
- The called dependency is mocked at the implementation symbol.
- `UNIT_TEST` is used to enable test-only visibility or override behavior when required by the production code.

Use this pattern when the test must replace linked collaborators without changing the production header contract.
