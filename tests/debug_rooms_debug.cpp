#include <iostream>
#include "../objects/rooms.h"

int main() {
    Rooms rooms;
    rooms.insertBed(Bed(1,101));
    rooms.insertBed(Bed(2,101));
    rooms.insertBed(Bed(3,101));
    rooms.insertBed(Bed(4,101));

    std::cout << "After inserts:\n";
    rooms.displayAll();

    std::cout << "Assign 2:\n";
    rooms.assignBedByID(2);
    rooms.displayAll();

    std::cout << "Assign 1:\n";
    rooms.assignBedByID(1);
    rooms.displayAll();

    std::cout << "Release 2:\n";
    rooms.releaseBedByID(2);
    rooms.displayAll();

    Bed* freeBed = rooms.findFreeBed();
    if (freeBed) std::cout << "First free bed: " << freeBed->getBedID() << "\n";
    else std::cout << "No free beds\n";

    return 0;
}
