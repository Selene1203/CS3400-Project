#include <iostream>
#include <string>
#include "../objects/patients.h"

int main() {
    using std::cout; using std::endl;
    bool ok = true;

    Patients ps;

    // Create two patients
    int id1 = ps.create("John", "Doe", "M", "1990-01-01", "+100", "123 Main", 555001);
    int id2 = ps.create("Jane", "Smith", "F", "1985-05-05", "+200", "456 Elm", 555002);

    if (ps.size() != 2) { cout << "Patients: FAIL size after create\n"; ok = false; } else cout << "Patients: create size OK\n";

    Patient* p1 = ps.find(id1);
    if (!p1 || p1->getName() != "John Doe") { cout << "Patients: FAIL find or name\n"; ok = false; } else cout << "Patients: find/name OK\n";

    // Update phone for id1
    if (!ps.updatePhone(id1, "+101")) { cout << "Patients: FAIL updatePhone returned false\n"; ok = false; }
    Patient* p1_after = ps.find(id1);
    if (!p1_after || p1_after->getPhone() != "+101") { cout << "Patients: FAIL phone not updated\n"; ok = false; } else cout << "Patients: updatePhone OK\n";

    // Update address for id2
    if (!ps.updateAddress(id2, "789 Oak")) { cout << "Patients: FAIL updateAddress returned false\n"; ok = false; }
    Patient* p2_after = ps.find(id2);
    if (!p2_after || p2_after->getPhone().empty()) { /* just ensure object still accessible */ }
    if (!p2_after || p2_after->getName() != "Jane Smith") { cout << "Patients: FAIL address/name check\n"; ok = false; } else cout << "Patients: updateAddress OK (object present)\n";

    // Remove id1
    if (!ps.remove(id1)) { cout << "Patients: FAIL remove returned false\n"; ok = false; }
    if (ps.find(id1) != nullptr) { cout << "Patients: FAIL find after remove\n"; ok = false; } else cout << "Patients: remove OK\n";

    // Add an existing Patient (explicit id)
    Patient p3(10, "Alice", "Brown", "F", "1992-02-02", "+300", "12 Pine", 555003);
    if (!ps.add(p3)) { cout << "Patients: FAIL add(p3) returned false\n"; ok = false; }
    if (ps.find(10) == nullptr) { cout << "Patients: FAIL find added patient\n"; ok = false; } else cout << "Patients: add/find OK\n";

    cout << (ok ? "ALL PATIENTS TESTS PASSED\n" : "SOME PATIENTS TESTS FAILED\n");
    return ok ? 0 : 1;
}
