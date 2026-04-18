# Plan

## Objective

Fix the root-workspace live-attach flow so starting OpenOCD for an attach session no longer leaves the ESP32-S3 sitting in a reset-halted state before GDB attaches.

## Steps

1. Create the request tracker files.
2. Add an explicit OpenOCD startup mode that resumes the target for live-attach workflows.
3. Update the live-attach tasks to use the new startup mode without changing the reset-and-load flow.
4. Update the documentation and tracker with the validated behavior.

## Current State

Completed.
