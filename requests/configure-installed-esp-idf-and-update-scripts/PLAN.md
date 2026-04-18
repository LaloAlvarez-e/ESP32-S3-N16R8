# Plan

## Objective

Detect the installed ESP-IDF toolchain paths and update the workspace settings and helper scripts to use the verified installation.

## Steps

1. Create the request tracker and required files.
2. Detect the installed ESP-IDF framework, OpenOCD, and GDB paths.
3. Update `.vscode/settings.json` and the helper scripts with the verified runtime behavior.
4. Validate the scripts with the installed toolchain and close the tracker.

## Outcome

The workspace now uses the detected ESP-IDF 6.0, OpenOCD, and Xtensa GDB paths. The helper scripts resolve the exported command behavior correctly, tolerate ESP-IDF activation stderr during import, and both ESP-IDF projects produce bootloader and ELF artifacts.