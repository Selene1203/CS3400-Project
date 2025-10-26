#include <iostream>
#include "../objects/logging.h"

int main() {
    using std::cout; using std::endl;
    bool ok = true;

    Logging lg;
    if (!lg.loadFromFile("data/logging.txt")) { cout << "Logging: FAIL loadFromFile returned false\n"; return 1; }
    auto logs = lg.getLogsForPatient(1);
    if (logs.size() < 1) { cout << "Logging: FAIL expected logs for patient 1\n"; ok = false; } else cout << "Logging: load logs OK\n";

    // Append new log
    int newId = lg.append(2, "Follow-up call", "2025-10-26 13:00");
    if (newId <= 0) { cout << "Logging: FAIL append returned invalid id\n"; ok = false; }

    if (!lg.saveToFile("data/logging_out.txt")) { cout << "Logging: FAIL saveToFile returned false\n"; ok = false; }

    // Reload into fresh logging and verify new entry present
    Logging lg2;
    if (!lg2.loadFromFile("data/logging_out.txt")) { cout << "Logging: FAIL reload returned false\n"; return 1; }
    auto logs2 = lg2.getLogsForPatient(2);
    bool found = false;
    for (auto &l : logs2) if (l.getLogID() == newId) found = true;
    if (!found) { cout << "Logging: FAIL appended log not found after reload\n"; ok = false; } else cout << "Logging: append+reload OK\n";

    cout << (ok ? "ALL LOGGING TESTS PASSED\n" : "SOME LOGGING TESTS FAILED\n");
    return ok ? 0 : 1;
}
