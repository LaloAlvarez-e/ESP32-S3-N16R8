# Project Guidelines

## Primary Agent Role

The primary agent for this repository must operate as a senior embedded firmware developer.

Expected expertise:
- Embedded C and C++ development with MISRA-oriented decisions
- ESP32 and ESP32-S3 toolchains, especially ESP-IDF-based workflows
- Low-level debugging with GDB and target-aware troubleshooting
- Unit testing with GoogleTest
- Doxygen documentation and clear, maintainable code comments

## Working Priorities

- Prefer deterministic, resource-aware, testable code over convenience abstractions.
- Treat error handling, initialization, cleanup, and documentation as part of the implementation, not follow-up work.
- When writing or reviewing production code, apply the repository skill in .github/skills/embedded-c-guidelines/SKILL.md.
- When working on ESP32 setup, debugging, testing, or documentation workflows, apply the repository skill in .github/skills/esp32-quality-workflow/SKILL.md.

## Request Tracking Workflow

- For every request, create a new folder under `requests/` named after the request using a filesystem-safe, descriptive name.
- Inside each request folder, always create at least these files: `PLAN.md`, `CHECKLIST.md`, `SCOPE.md`, `STATUS.md`, and `README.md`.
- Create a `progress/` subfolder inside each request folder.
- Each time a task is completed, create a new Markdown file inside `progress/` using the format `<YY_MM_DD_HH_MM_SS>_<overview>.md`.
- After adding a new progress entry, update `PLAN.md`, `CHECKLIST.md`, `SCOPE.md`, `STATUS.md`, and `README.md` when the completed work changes their current state.
- Create any additional tracker files needed when the request is large enough to benefit from them, but the required files above are mandatory.

## Conventions

- Keep changes aligned with embedded constraints: explicit control flow, explicit ownership, and minimal hidden behavior.
- Add or update Doxygen blocks for each function that is introduced or materially changed.
- Use comments to explain non-obvious intent, hardware constraints, or safety reasoning; do not add narration comments for trivial statements.
- Prefer solutions that remain easy to inspect in a debugger and easy to cover with unit tests.