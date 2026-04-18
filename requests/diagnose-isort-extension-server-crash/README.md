# Request

Diagnose why the VS Code isort extension language server crashes repeatedly in this workspace and apply a workspace-level fix if one is available.

## Current Result

Completed. The repeated isort server crash was caused by VS Code selecting `C:/Python314/python.exe` for this workspace, and that executable fails to launch on this machine with `STATUS_DLL_NOT_FOUND`. The workspace now pins `isort.interpreter` to `C:\Users\avala\scoop\apps\python313\current\python.exe`, which was verified to import and start the bundled isort language server successfully.
