# Plan

1. Identified which VS Code views in the current debug layout are powered by the ESP-IDF `gdbtarget` adapter and which come from other extensions or generic view containers.
2. Determined that writable peripheral registers, generic PlatformIO Registers and Memory views, and forced Disassembly tracking for every editor selection are not fully supported by the current adapter stack.
3. Applied the supported workspace changes: unwanted recommendation for PlatformIO and the closest supported Disassembly settings.
4. Updated documentation to reflect the supported behavior and the remaining adapter limits.
5. Validated the changes and recorded the result.
