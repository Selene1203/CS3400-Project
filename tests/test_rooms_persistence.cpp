#include <iostream>
#include "../objects/rooms.h"

int main() {
    using std::cout; using std::endl;
    bool ok = true;

    Rooms r;
    if (!r.loadFromFile("data/rooms.txt")) {
        cout << "Rooms persistence: FAIL loadFromFile returned false\n";
        return 1;
    }

    if (r.size() != 4) { cout << "Rooms persistence: FAIL expected 4 beds got " << r.size() << "\n"; ok = false; } else cout << "Rooms persistence: load size OK\n";

    // initial free should be bed 1
    Bed* free1 = r.findFreeBed();
    if (!free1 || free1->getBedID() != 1) { cout << "Rooms persistence: FAIL initial free expected 1\n"; ok = false; } else cout << "Rooms persistence: initial free OK\n";

    // Save out, then reload into a fresh Rooms and verify occupied persisted
    if (!r.saveToFile("data/rooms_out.txt")) { cout << "Rooms persistence: FAIL saveToFile returned false\n"; ok = false; }
    Rooms r2;
    if (!r2.loadFromFile("data/rooms_out.txt")) { cout << "Rooms persistence: FAIL reload returned false\n"; return 1; }
    // bed 2 should be occupied (per sample)
    Bed* b2 = r2.findFreeBed();
    if (!b2) { cout << "Rooms persistence: FAIL no free beds on reload\n"; ok = false; }
    // Ensure that bed 2 is not the first free (since bed 2 was occupied in the sample)
    if (b2->getBedID() == 2) { cout << "Rooms persistence: FAIL reload first free unexpectedly 2\n"; ok = false; } else cout << "Rooms persistence: reload OK (first free not 2)\n";

    cout << (ok ? "ALL ROOMS PERSISTENCE TESTS PASSED\n" : "SOME ROOMS PERSISTENCE TESTS FAILED\n");
    return ok ? 0 : 1;
}
