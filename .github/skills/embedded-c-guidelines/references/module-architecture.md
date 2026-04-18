# Module Architecture

## Core Rules

- Organize code by module folders.
- Every folder is treated as a module.
- Every folder must contain a folder-level header named after the folder.
- The folder-level header must aggregate the public headers that belong to that folder.
- Nested folders represent nested submodules.

## Dependency Direction

- Dependencies must stay vertical within a single branch of the tree.
- Nested modules must not include headers from parent folders.
- Nested modules must not call APIs owned by parent folders.
- Sibling modules must not depend directly on each other.
- Higher-level folders may compose lower-level nested modules.

## Upward API Exposure

- Although nested modules must not depend on parent APIs, parent folders may re-export child public headers upward.
- This allows top-level users to include a folder-level header instead of many individual headers.
- Keep upward exposure explicit and intentional in the folder-level header.

## Folder Header Rule

If the folder is `xModule/`, the folder must provide `xModule.h`.

Example:

```cpp
/* xModule.h */
#ifndef XMODULE_H
#define XMODULE_H

#include "xSource1.h"
#include "xSubModule/xSubModule.h"

#endif
```

## Example Nested Layout

```text
project/
    main.c
    main.h
    xModule/
        xSource1.c
        xSource1.h
        xSubModule/
            xSubSource.c
            xSubSource.h
            xNestedModule/
            xSubModule.h
        xModule.h
```

Notes:

- `main.c` and `main.h` are optional when the project does not need them.
- `xModule.h` aggregates the public headers owned by `xModule/`.
- `xSubModule.h` aggregates the public headers owned by `xSubModule/`.
- `xSubModule/` must not call APIs from `xModule/`.
