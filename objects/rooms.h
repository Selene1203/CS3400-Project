#ifndef ROOMS_H
#define ROOMS_H

#include <iostream>
#include "../utils/binaryTree.h"
#include "../utils/linkedList.h"
#include "bed.h"
#include <fstream>
#include <sstream>
#include <vector>

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
        // Find the tree node we just added and insert its Bed* into the local linked list
        TreeNode<Bed>* node = tree.find(b);
        if (node == nullptr) return; // shouldn't happen

        Bed* bedPtr = &node->data;
        Node<Bed*>* head = bedList.getHead();
        if (head == nullptr || bedPtr->getBedID() < head->data->getBedID()) {
            bedList.insertAtFront(bedPtr);
            return;
        }

        Node<Bed*>* cur = head;
        while (cur->next != nullptr && cur->next->data->getBedID() < bedPtr->getBedID())
            cur = cur->next;

        // Avoid inserting duplicates if the bed already exists in list
        if (cur->next != nullptr && cur->next->data->getBedID() == bedPtr->getBedID())
            return;

        Node<Bed*>* newNode = new Node<Bed*>(bedPtr);
        newNode->next = cur->next;
        cur->next = newNode;
    }

    // Assign a bed by id. Returns true if the bed was found and assigned.
    bool assignBedByID(int bed_id) {
        Bed probe(bed_id, 0);
        TreeNode<Bed>* node = tree.find(probe);
        if (node == nullptr) {
            std::cout << "Bed " << bed_id << " not found." << std::endl;
            return false;
        }
        if (node->data.isOccupied()) {
            std::cout << "Bed " << bed_id << " already occupied." << std::endl;
            return false;
        }
        node->data.setOccupied(true);
        std::cout << "Bed " << bed_id << " assigned." << std::endl;
        return true;
    }

    // Find the next free bed (returns pointer into internal node data or nullptr)
    Bed* findFreeBed() {
        // Prefer scanning our linked list (in-order) for first unoccupied bed
        Node<Bed*>* cur = bedList.getHead();
        while (cur != nullptr) {
            if (!cur->data->isOccupied()) return cur->data;
            cur = cur->next;
        }
        return nullptr;
    }

    // Mark a bed free by id. Returns true if found and freed.
    bool releaseBedByID(int bed_id) {
        Bed probe(bed_id, 0);
        TreeNode<Bed>* node = tree.find(probe);
        if (!node) return false;
        node->data.setOccupied(false);
        std::cout << "Bed " << bed_id << " released." << std::endl;
        return true;
    }

    // Display all beds (in-order)
    void displayAll() {
        Node<Bed*>* cur = bedList.getHead();
        std::cout << "Rooms (in-order) has " ;
        size_t cnt = 0;
        while (cur != nullptr) {
            cur->data->display();
            cur = cur->next;
            ++cnt;
        }
        if (cnt == 0) std::cout << "no beds\n";
    }

    // Number of beds
    size_t size() const {
        size_t cnt = 0;
        Node<Bed*>* cur = bedList.getHead();
        while (cur != nullptr) { ++cnt; cur = cur->next; }
        return cnt;
    }

    // Persist beds to a file. Format: bed_id|room_id|occupied(0/1) per line.
    bool saveToFile(const std::string& path) const {
        std::ofstream out(path);
        if (!out.is_open()) return false;
        Node<Bed*>* cur = bedList.getHead();
        while (cur != nullptr) {
            Bed* b = cur->data;
            out << b->getBedID() << '|' << b->getRoomID() << '|' << (b->isOccupied() ? 1 : 0) << '\n';
            cur = cur->next;
        }
        out.close();
        return true;
    }

    // Load beds from file. If clearExisting true (default) current data is cleared.
    bool loadFromFile(const std::string& path, bool clearExisting = true) {
        std::ifstream in(path);
        if (!in.is_open()) return false;

        if (clearExisting) {
            tree = BinaryTree<Bed>();
            bedList = LinkedList<Bed*>();
        }

        std::string line;
        while (std::getline(in, line)) {
            if (line.empty()) continue;
            std::istringstream ss(line);
            std::string token;
            std::vector<std::string> parts;
            while (std::getline(ss, token, '|')) parts.push_back(token);
            if (parts.size() < 2) continue;
            int bid = std::stoi(parts[0]);
            int rid = std::stoi(parts[1]);
            bool occ = false;
            if (parts.size() >= 3) occ = (parts[2] == "1");

            Bed b(bid, rid, occ);
            insertBed(b);
            if (occ) {
                // ensure occupancy is set on the actual Bed object
                TreeNode<Bed>* node = tree.find(b);
                if (node) node->data.setOccupied(true);
            }
        }

        in.close();
        return true;
    }

private:
    BinaryTree<Bed> tree;
    LinkedList<Bed*> bedList; // mirrors tree in-order for quick iteration
};

#endif // ROOMS_H
