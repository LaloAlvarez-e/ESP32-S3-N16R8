# Copilot Instructions

- Read the nearest `AGENTS.md` before starting substantial work so repository-wide rules, request tracking, and embedded development expectations are loaded first.
- Follow the request tracking workflow defined in `AGENTS.md` for every request.
- Load the required repository skill files before making code or documentation changes.
- Use `.github/skills/embedded-c-guidelines/SKILL.md` for embedded C/C++ implementation, refactoring, API design, and code review work.
- Use `.github/skills/esp32-quality-workflow/SKILL.md` for ESP32 toolchain, ESP-IDF, GDB debugging, GoogleTest, Doxygen, and code-comment tasks.
- Use `.github/agents/embedded-firmware.agent.md` as the primary repository subagent for embedded firmware tasks when a subagent is appropriate.
- Use `.github/agents/esp32-debug.agent.md` for ESP32 and GDB debugging tasks.
- Use `.github/agents/gtest-review.agent.md` for GoogleTest-focused review and test authoring tasks.
- Use `.github/agents/doxygen-doc.agent.md` for Doxygen and API documentation tasks.
- Use `.github/agents/api-design.agent.md` for embedded API design, header architecture, module boundary, and interface review tasks.
- Use `.github/agents/misra-review.agent.md` for MISRA-oriented code review, coding-rule checks, and embedded API conformance review.
- For agent customization tasks, load the appropriate customization guidance before editing instruction, agent, or skill files.
- If a suitable repository subagent exists for the task, invoke the most specific one only after reading `AGENTS.md` and the relevant skill files.
- If no repository subagent exists yet, continue with the primary agent while still applying `AGENTS.md` and the relevant skills.
- Keep changes deterministic, explicit, and easy to debug.
- Do not skip Doxygen, cleanup, or error-handling requirements when they apply to the task.