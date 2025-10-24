#ifndef ROOM_H
#define ROOM_H

#include <iostream>
#include "bed.h"
#include "../utils/linkedList.h"
using namespace std;

class Room {
private:
    int room_id;
    int total_beds;
    LinkedList<Bed> beds; // Linked list to store all beds

public:
    // Constructors
    Room() : room_id(0), total_beds(0) {}
    Room(int id) : room_id(id), total_beds(0) {}

    // Add a new bed to the room
    void addBed(Bed bed) {
        beds.insertAtEnd(bed);
        total_beds++;
    }

    // Remove a bed from the room by ID
    void removeBed(int bed_id) {
        Bed b(bed_id, room_id);
        beds.remove(b);
        total_beds--;
    }

    // Find a specific bed by ID
    Bed* findBed(int bed_id) {
        Node<Bed>* current = beds.getHead();
        while (current != nullptr) {
            if (current->data.getBedID() == bed_id)
                return &(current->data);
            current = current->next;
        }
        return nullptr;
    }

    // Show all beds in the room
    void displayBeds() {
        cout << "Room " << room_id << " has " << total_beds << " beds:" << endl;
        Node<Bed>* temp = beds.getHead();
        while (temp != nullptr) {
            temp->data.display();
            temp = temp->next;
        }
    }

    // Get room ID
    int getRoomID() const { return room_id; }

    // Get total beds
    int getTotalBeds() const { return total_beds; }

    // Find and assign the first available bed
    Bed* findFreeBed() {
        Node<Bed>* temp = beds.getHead();
        while (temp != nullptr) {
            if (!temp->data.isOccupied())
                return &(temp->data);
            temp = temp->next;
        }
        return nullptr;
    }

    // Mark a bed as occupied
    bool assignBed(int bed_id) {
        Bed* bed = findBed(bed_id);
        if (bed != nullptr && !bed->isOccupied()) {
            bed->setOccupied(true);
            cout << "Bed " << bed_id << " in Room " << room_id << " assigned." << endl;
            return true;
        }
        cout << "Bed not available or already occupied." << endl;
        return false;
    }
};

#endif
