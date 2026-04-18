# Plan

## Objective

Add a safe way to recheck available serial ports and support automatic ESP32 serial-port selection when the configured port changes.

## Steps

1. Create the request tracker files.
2. Add shared PowerShell helpers to enumerate and resolve serial ports.
3. Add a workspace task to list the currently available serial ports.
4. Update the ESP-IDF wrapper to support automatic port selection.
5. Validate the scripts and update the tracker.
