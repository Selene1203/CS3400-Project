#include <iostream>
#include <string>
#include "../objects/bed.h"
#include "../objects/log.h"
#include "../objects/patient.h"
#include "../objects/traigeCase.h"

int main() {
    using std::cout; using std::endl;
    bool ok = true;

    // Bed
    Bed b(101, 12, false);
    if (b.getBedID() != 101) { cout<<"Bed: FAIL getBedID\n"; ok = false; } else cout<<"Bed: getBedID OK\n";
    if (b.getRoomID() != 12) { cout<<"Bed: FAIL getRoomID\n"; ok = false; } else cout<<"Bed: getRoomID OK\n";
    if (b.isOccupied()) { cout<<"Bed: FAIL initial occupied\n"; ok = false; } else cout<<"Bed: initial occupied OK\n";
    b.setOccupied(true);
    if (!b.isOccupied()) { cout<<"Bed: FAIL setOccupied\n"; ok = false; } else cout<<"Bed: setOccupied OK\n";

    // Patient
    Patient p(1, "Jane", "Doe", "F", "1990-05-01", "+100", "123 Main", 555555);
    if (p.getID() != 1) { cout<<"Patient: FAIL getID\n"; ok = false; } else cout<<"Patient: getID OK\n";
    if (p.getName() != "Jane Doe") { cout<<"Patient: FAIL getName ("<<p.getName()<<")\n"; ok = false; } else cout<<"Patient: getName OK\n";
    p.setPhone("+101");
    if (p.getPhone() != "+101") { cout<<"Patient: FAIL setPhone\n"; ok = false; } else cout<<"Patient: setPhone OK\n";

    // Log
    Log l(10, 1, "Checked vitals", "2025-10-24 10:00");
    if (l.getLogID() != 10) { cout<<"Log: FAIL getLogID\n"; ok = false; } else cout<<"Log: getLogID OK\n";
    if (l.getPatientID() != 1) { cout<<"Log: FAIL getPatientID\n"; ok = false; } else cout<<"Log: getPatientID OK\n";
    if (l.getActivity() != "Checked vitals") { cout<<"Log: FAIL getActivity\n"; ok = false; } else cout<<"Log: getActivity OK\n";

    // TriageCase
    TriageCase t1(1, "Broken arm", 3, "2025-10-24 09:00");
    TriageCase t2(2, "Cardiac arrest", 1, "2025-10-24 09:05");
    if (!(t2 < t1)) { cout<<"TriageCase: FAIL operator< (priority ordering)\n"; ok = false; } else cout<<"TriageCase: operator< OK\n";

    cout << (ok ? "ALL OBJECT TESTS PASSED\n" : "SOME OBJECT TESTS FAILED\n");
    return ok ? 0 : 1;
}
