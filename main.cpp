#include "objects/room.h"

int main() {
    Room r1(101);

    r1.addBed(Bed(1, 101));
    r1.addBed(Bed(2, 101));
    r1.addBed(Bed(3, 101));

    r1.displayBeds();

    r1.assignBed(2);

    Bed* freeBed = r1.findFreeBed();
    if (freeBed != nullptr) {
        cout << "Next free bed: " << freeBed->getBedID() << endl;
    }

    return 0;
}
