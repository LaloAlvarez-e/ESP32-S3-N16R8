# common_os test

Isolated unit-test target for `common_os`.

- Compile the real production sources from `common_os/`.
- Override weak callbacks or linked symbols only inside this test target.
- Do not depend on test code from other folders.
