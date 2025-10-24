# Copilot instructions — CS3400-Project

Purpose: give an AI coding agent the minimal, concrete knowledge needed to be productive in this repository.

1) Big-picture
- This is a small, text-file backed CLI hospital simulation (Week 1 deliverable). The intended implementation language is C++ (per README), and the program is a menu-driven CLI that manipulates plain text files in the repo root.
- Core subsystems: patient registration (hash table), emergency triage (priority queue), bed allocation (binary tree), and patient logs (linked list). Persistent state is stored in pipe-delimited files such as `patients.txt`, `triage.txt`, `beds.txt`, `rooms.txt`, `bed_assignments.txt`, and `patient_logs.txt`.

2) Key data conventions (discoverable in `README.md`)
- File format: pipe-delimited records (example: `1|John|Doe|1995-06-12|M|+266-5551234|Maseru|10001`).
- Date format: `YYYY-MM-DD`. Timestamp format used in examples: `YYYY-MM-DD HH:MM`.
- Boolean fields use `true`/`false` for `occupied` in `beds.txt`.
- Triage priority: lower `triage_level` number = higher priority.

3) Where to change things
- If adding or modifying code, place C++ sources under `src/` and keep a single `main` entrypoint (e.g. `src/main.cpp`). If you add build files, include a `Makefile` or `CMakeLists.txt` at repo root.
- File I/O handlers should read/write the pipe-delimited files listed above. Keep file structure stable; tests and CLI flows rely on exact field order.

4) Coding guidance for agents (concrete, repo-specific)
- When you update record structure (add/remove fields), update the corresponding `README.md` table and all places that parse that file. Example: changing `patients.txt` fields requires updating code that parses `patient_id|first_name|...|national_id`.
- Follow the data examples in `README.md` when generating fixtures; use the same separators and date formats.
- Use append-on-write semantics for logs and triage entries (the README shows appending new lines for persistence).
- For bed assignment, prefer a deterministic traversal matching README pseudocode (check current node, then left, then right) so saved `beds.txt` ordering and `bed_id` mapping remain stable.

5) Build / run / debug notes (what I found)
- No source files or build configuration were detected in the repo when this file was generated — only `README.md` is present. If you want me to generate C++ skeletons or a `Makefile`/`CMakeLists.txt`, say so.
- Example build command to use on development machines (Windows `cmd.exe`):
  - `g++ -std=c++17 -O2 -Iinclude -o hospital.exe src\*.cpp` (adjust sources as added)
- Run the CLI by executing the produced binary; data files live adjacent to the executable by default according to README examples.

6) Tests and CI
- No tests or CI configs were detected. If you add tests, keep them focused on the parsing and persistence boundary (round-trip read/write of the pipe-delimited files) and on the priority ordering for the triage queue.

7) When uncertain, prefer conservative changes
- Don't rename or reformat existing data files without updating `README.md` and any parsing code. Small, local changes that preserve on-disk formats are preferred.

8) Quick pointers for reviewers
- Verify any new code uses the same field ordering as the `README.md` examples.
- Confirm timestamps are written as `YYYY-MM-DD HH:MM` and booleans as `true`/`false` in `beds.txt`.

If anything above is incomplete or you'd like me to scaffold a `src/` layout, a `Makefile`, or add a basic C++ implementation for the four data structures, tell me which piece to generate next.
