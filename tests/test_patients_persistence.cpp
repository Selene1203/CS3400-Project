#include <iostream>
#include <string>
#include "../objects/patients.h"

int main() {
    using std::cout; using std::endl;
    bool ok = true;

    Patients ps;

    // Load sample data
    if (!ps.loadFromFile("data/patients.txt")) {
        cout << "Patients persistence: FAIL loadFromFile returned false\n";
        return 1;
    }

    if (ps.size() != 3) {
        cout << "Patients persistence: FAIL expected size 3 got " << ps.size() << "\n";
        ok = false;
    } else cout << "Patients persistence: load size OK\n";

    Patient* p2 = ps.find(2);
    if (!p2 || p2->getName() != "Jane Smith") {
        cout << "Patients persistence: FAIL find or name mismatch for id 2\n";
        ok = false;
    } else cout << "Patients persistence: find/name OK\n";

    // Modify phone and save
    if (!ps.updatePhone(2, "+999")) {
        cout << "Patients persistence: FAIL updatePhone returned false\n";
        ok = false;
    }

    if (!ps.saveToFile("data/patients_out.txt")) {
        cout << "Patients persistence: FAIL saveToFile returned false\n";
        ok = false;
    } else cout << "Patients persistence: save OK\n";

    // Load into a fresh Patients and verify change persisted
    Patients ps2;
    if (!ps2.loadFromFile("data/patients_out.txt")) {
        cout << "Patients persistence: FAIL loadFromFile (out) returned false\n";
        return 1;
    }

    Patient* p2_after = ps2.find(2);
    if (!p2_after || p2_after->getPhone() != "+999") {
        cout << "Patients persistence: FAIL phone did not persist (expected +999)\n";
        ok = false;
    } else cout << "Patients persistence: phone persisted OK\n";

    cout << (ok ? "ALL PATIENTS PERSISTENCE TESTS PASSED\n" : "SOME PATIENTS PERSISTENCE TESTS FAILED\n");
    return ok ? 0 : 1;
}
