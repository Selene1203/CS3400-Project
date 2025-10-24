#ifndef BED_H
#define BED_H

#include <iostream>
#include <string>
using namespace std;

class Bed {
private:
    int bed_id;
    int room_id;
    bool occupied;

public:
    // Constructors
    Bed() : bed_id(0), room_id(0), occupied(false) {}
    Bed(int b, int r, bool o = false) : bed_id(b), room_id(r), occupied(o) {}

    // Getters
    int getBedID() const { return bed_id; }
    int getRoomID() const { return room_id; }
    bool isOccupied() const { return occupied; }

    // Setters
    void setOccupied(bool o) { occupied = o; }

    // Display
    void display() const {
        cout << "Bed ID: " << bed_id
             << " | Room ID: " << room_id
             << " | Occupied: " << (occupied ? "Yes" : "No") << endl;
    }

    // Comparison
    bool operator<(const Bed& other) const {
        return bed_id < other.bed_id;
    }

    bool operator==(const Bed& other) const {
        return bed_id == other.bed_id;
    }
};

#endif
