#include <iostream>
#include "../objects/triageCases.h"

int main() {
    using std::cout; using std::endl;
    bool ok = true;

    TriageCases tc;

    if (!tc.loadFromFile("data/traigecases.txt")) {
        cout << "TriageCases persistence: FAIL loadFromFile returned false\n";
        return 1;
    }

    if (tc.size() != 3) { cout << "TriageCases persistence: FAIL expected size 3 got " << tc.size() << "\n"; ok = false; } else cout << "TriageCases persistence: load size OK\n";

    // Top should be the case with level 1 (patient 1)
    Case top = tc.top();
    if (top.getPatientID() != 1) { cout << "TriageCases persistence: FAIL top expected patient 1 got " << top.getPatientID() << "\n"; ok = false; } else cout << "TriageCases persistence: top OK\n";

    // Add a new critical case and save
    tc.push(Case(4, "Cardiac arrest", 1, "2025-10-26 09:10"));
    if (!tc.saveToFile("data/traigecases_out.txt")) { cout << "TriageCases persistence: FAIL saveToFile returned false\n"; ok = false; } else cout << "TriageCases persistence: save OK\n";

    // Reload into fresh object and ensure highest priority is one of the level-1 cases
    TriageCases tc2;
    if (!tc2.loadFromFile("data/traigecases_out.txt")) { cout << "TriageCases persistence: FAIL reload returned false\n"; return 1; }
    if (tc2.size() < 1) { cout << "TriageCases persistence: FAIL reload size\n"; ok = false; }
    Case top2 = tc2.top();
    if (top2.getLevel() != 1) { cout << "TriageCases persistence: FAIL expected top level 1 after reload got " << top2.getLevel() << "\n"; ok = false; } else cout << "TriageCases persistence: reload top level OK\n";

    cout << (ok ? "ALL TRIAGE PERSISTENCE TESTS PASSED\n" : "SOME TRIAGE PERSISTENCE TESTS FAILED\n");
    return ok ? 0 : 1;
}
