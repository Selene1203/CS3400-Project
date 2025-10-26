### Purpose
Help an AI coding agent become productive quickly in this C++ Hospital CLI codebase.

### Big picture (what this repo implements)
- A small command-line Hospital Management system (patient registration, triage/priority queue, bed/room allocation, and logs).
- Core domain objects live under `objects/` (e.g. `Patient`, `Bed`, `Room`, `BedAssignment`, `Log`, `TriageCase`).
- Data-structure implementations are header-only templates in `utils/` (linked list, hash table, binary tree, priority queue).
- Tests/smoke-checks are in `tests/` and small example programs are in `main.cpp`.

### Key files and how pieces fit
- `objects/*.h` — domain models used by the CLI. Example: `Room` uses `LinkedList<Bed>` and returns pointers into list nodes (see `objects/room.h`).
- `utils/linkedList.h` — singly linked list template; exposes `Node<T>* getHead()` and uses `ListNode<T>` layout. Many consumers rely on direct access to `head`.
- `utils/hashTable.h` — simple chaining table using `LinkedList<Pair<Key,Value>>`. Note: hash function is `key % TABLE_SIZE` (assumes integer-like keys).
- `utils/priorityQueue.h` — ordered insertion into `LinkedList<PQItem<T>>`. It manipulates `LinkedList` internals (see the front-insert hack) — changing `LinkedList` internals can break this.
- `utils/binaryTree.h` — binary search tree storing beds; `findFreeBed()` searches for an unoccupied node.
- `tests/*.cpp` — small smoke tests demonstrating expected behavior and examples of using the utilities. Use these to learn how functions are intended to behave.

### Project-specific conventions & gotchas (be precise)
- Header-only templates: data structures are implemented entirely in headers. Add behavior by editing headers, not by adding separate .cpp for templates.
- LinkedList contract: other modules expect `Node<T>` and `getHead()` to be available. Avoid renaming `getHead()` or changing `ListNode` layout without updating all callers (PriorityQueue, HashTable, Room).
- HashTable only uses `operator%` on Key in `hashFunction`. Currently written for integer keys; generalizing requires adding a proper hash functor.
- Priority ordering: lower `triage_level` means higher priority (1 = critical). `TriageCase::operator<` and `PriorityQueue` follow this rule.
- Lifetime safety: many APIs return pointers to data inside linked-list/tree nodes (e.g., `Room::findBed()` returns `Bed*` into a list node). Be careful when removing nodes — callers may hold dangling pointers.

### Build & test (Windows / cmd.exe examples)
No build system detected. Suggested quick commands (works if you have g++/MinGW on PATH). Run from project root (cmd.exe):

```
:: Build main demo
g++ -std=c++17 -I. main.cpp -o main.exe

:: Build tests (each test is a small executable)
g++ -std=c++17 -I. tests/test_datastructures.cpp -o test_datastructures.exe
g++ -std=c++17 -I. tests/test_objects.cpp -o test_objects.exe

:: Run tests
test_datastructures.exe
test_objects.exe
```

If using MSVC (Visual Studio Developer Command Prompt), compile similarly with `cl` and appropriate include flags.

### How to extend safely (practical examples)
- To add persistence: README.md documents text file formats (patients.txt, triage.txt, beds.txt). Implement file I/O in a new `utils/file_io.h` and call from a new `cli.cpp` or extend `main.cpp`.
- To generalize `HashTable` to non-integer keys: add a hash-functor template parameter and replace `%` with functor(key) % TABLE_SIZE.
- To change `LinkedList` internals: first update all call sites that rely on `getHead()` or node layout (PriorityQueue and HashTable). Alternatively, add a safe `pushFront()`/`setHead()` API and migrate consumers.

### Tests and verification
- The `tests/` programs are the fastest way to confirm behavior — they perform small unit/smoke checks for each DS and object.
- When adding features, add a small test in `tests/` to exercise the new behavior (follow format of existing tests).

### Quick references (examples)
- Room returns a pointer into its `LinkedList<Bed>`: `Bed* free = room.findFreeBed();` (see `objects/room.h`).
- Priority queue semantics: insert data with `pq.insert(data, priority)` where smaller `priority` = earlier service (see `utils/priorityQueue.h`).

### When uncertain — ask these specific questions
- Is the intention to support non-integer hash keys? If so, I will add a hash functor and update call sites.
- Should persistence be implemented now (text-file format in README) or left for a later milestone?

---
If you'd like, I can: (a) merge this into an existing `.github/copilot-instructions.md` if present, (b) add small compile-and-run CI scripts, or (c) implement file-I/O for the txt formats described in `README.md`.
