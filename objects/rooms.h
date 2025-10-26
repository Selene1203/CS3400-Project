#ifndef ROOMS_H
#define ROOMS_H

#include <iostream>
#include "../utils/binaryTree.h"
#include "bed.h"

// Provide operator<< for Bed so BinaryTree's display/assign messages compile when instantiated with Bed.
inline std::ostream& operator<<(std::ostream& os, const Bed& b) {
    os << b.getBedID();
    return os;
}

// Rooms: wrapper around an AVL BinaryTree<Bed> for hospital-wide bed management.
class Rooms {
public:
    Rooms() = default;

    // Insert a single bed into the tree. Bed ordering is by bed_id (Bed::operator<).
    void insertBed(const Bed& b) {
        tree.add(b);
    }

    // Assign a bed by id. Returns true if the bed was found and assigned.
    bool assignBedByID(int bed_id) {
        Bed probe(bed_id, 0);
        TreeNode<Bed>* node = tree.find(probe);
        if (node == nullptr) {
            std::cout << "Bed " << bed_id << " not found." << std::endl;
            return false;
        }
        if (node->occupied) {
            std::cout << "Bed " << bed_id << " already occupied." << std::endl;
            return false;
        }
        node->occupied = true;
        std::cout << "Bed " << bed_id << " assigned." << std::endl;
        return true;
    }

    // Find the next free bed (returns pointer into internal node data or nullptr)
    Bed* findFreeBed() {
        TreeNode<Bed>* node = tree.findFreeBed();
        return node ? &node->data : nullptr;
    }

    // Mark a bed free by id. Returns true if found and freed.
    bool releaseBedByID(int bed_id) {
        Bed probe(bed_id, 0);
        TreeNode<Bed>* node = tree.find(probe);
        if (!node) return false;
        node->occupied = false;
        std::cout << "Bed " << bed_id << " released." << std::endl;
        return true;
    }

    // Display all beds (in-order)
    void displayAll() {
        tree.display();
    }

private:
    BinaryTree<Bed> tree;
};

#endif // ROOMS_H
