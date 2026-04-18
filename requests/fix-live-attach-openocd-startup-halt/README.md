# Request

Fix the root-workspace attach-running debug flow so it no longer lands in the OpenOCD startup reset halt before the debugger can perform a practical late attach.

## Current Result

Completed. The repository now routes live-attach prepare tasks through a dedicated OpenOCD server mode that resumes the target after startup, so the attach-running profiles can halt application-side execution instead of inheriting the raw reset halt left by the default ESP32-S3 OpenOCD startup path. The reset-and-load path remains available through the plain OpenOCD server task.
