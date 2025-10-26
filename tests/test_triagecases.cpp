#include <iostream>
#include <string>
#include "../objects/traigeCase.h"
#include "../objects/triageCases.h"

int main() {
    using std::cout; using std::endl;
    bool ok = true;

    // Prepare cases (in insertion order)
    Case c1(1, "Minor injury", 3, "2025-10-26 09:00");
    Case c2(2, "Cardiac arrest", 1, "2025-10-26 09:01");
    Case c3(3, "High fever", 2, "2025-10-26 09:02");
    Case c4(4, "Stroke", 1, "2025-10-26 09:03");

    TriageCases tc;
    tc.push(c1);
    tc.push(c2);
    tc.push(c3);
    tc.push(c4);

    Case out;

    // Expectation: c2 (level 1, inserted before c4), then c4 (level 1), then c3 (2), then c1 (3)
    if (!tc.tryPop(out) || out.getPatientID() != 2) { cout << "TriageCases: FAIL first pop (expected patient 2)\n"; ok = false; } else cout << "TriageCases: first pop OK\n";
    if (!tc.tryPop(out) || out.getPatientID() != 4) { cout << "TriageCases: FAIL second pop (expected patient 4)\n"; ok = false; } else cout << "TriageCases: second pop OK\n";
    if (!tc.tryPop(out) || out.getPatientID() != 3) { cout << "TriageCases: FAIL third pop (expected patient 3)\n"; ok = false; } else cout << "TriageCases: third pop OK\n";
    if (!tc.tryPop(out) || out.getPatientID() != 1) { cout << "TriageCases: FAIL fourth pop (expected patient 1)\n"; ok = false; } else cout << "TriageCases: fourth pop OK\n";

    cout << (ok ? "ALL TRIAGE TESTS PASSED\n" : "SOME TRIAGE TESTS FAILED\n");
    return ok ? 0 : 1;
}
