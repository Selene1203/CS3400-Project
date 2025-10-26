#include <iostream>
#include "../objects/rooms.h"
#include "../objects/bed.h"

int main() {
    using std::cout; using std::endl;
    bool ok = true;

    Rooms rooms;

    // Insert beds with IDs 1..4 (room id 101)
    rooms.insertBed(Bed(1, 101));
    rooms.insertBed(Bed(2, 101));
    rooms.insertBed(Bed(3, 101));
    rooms.insertBed(Bed(4, 101));

    // Initially, smallest free bed should be 1
    Bed* free1 = rooms.findFreeBed();
    if (!free1 || free1->getBedID() != 1) { cout << "Rooms: FAIL initial free expected 1\n"; ok = false; } else cout << "Rooms: initial free OK\n";

    // Assign bed 2 (non-smallest)
    if (!rooms.assignBedByID(2)) { cout << "Rooms: FAIL assignBedByID(2)\n"; ok = false; } else cout << "Rooms: assign 2 OK\n";

    // Free bed should still be 1
    Bed* free2 = rooms.findFreeBed();
    if (!free2 || free2->getBedID() != 1) { cout << "Rooms: FAIL free after assign 2 expected 1\n"; ok = false; } else cout << "Rooms: free after assign 2 OK\n";

    // Assign bed 1
    if (!rooms.assignBedByID(1)) { cout << "Rooms: FAIL assignBedByID(1)\n"; ok = false; } else cout << "Rooms: assign 1 OK\n";

    // Next free should be 3
    Bed* free3 = rooms.findFreeBed();
    if (!free3 || free3->getBedID() != 3) { cout << "Rooms: FAIL free after assign 1 expected 3\n"; ok = false; } else cout << "Rooms: free after assign 1 OK\n";

    // Release bed 2 -> now smallest free should be 2
    if (!rooms.releaseBedByID(2)) { cout << "Rooms: FAIL releaseBedByID(2)\n"; ok = false; } else cout << "Rooms: release 2 OK\n";
    Bed* free4 = rooms.findFreeBed();
    if (!free4 || free4->getBedID() != 2) { cout << "Rooms: FAIL free after release 2 expected 2\n"; ok = false; } else cout << "Rooms: free after release 2 OK\n";

    // Try assign non-existent bed
    if (rooms.assignBedByID(999)) { cout << "Rooms: FAIL assign non-existent should return false\n"; ok = false; } else cout << "Rooms: assign non-existent OK (false)\n";

    // Try release non-existent bed
    if (rooms.releaseBedByID(999)) { cout << "Rooms: FAIL release non-existent should return false\n"; ok = false; } else cout << "Rooms: release non-existent OK (false)\n";

    cout << (ok ? "ALL ROOMS TESTS PASSED\n" : "SOME ROOMS TESTS FAILED\n");
    return ok ? 0 : 1;
}
