#ifndef PATIENTS_H
#define PATIENTS_H

#include <iostream>
#include <string>
#include "patient.h"
#include "../utils/hashTable.h"

// Provide a simple stream printer for Patient so HashTable::display() is readable.
inline std::ostream& operator<<(std::ostream& os, const Patient& p) {
    os << "[" << p.getID() << "] " << p.getName() << " | " << p.getPhone();
    return os;
}

class Patients {
public:
    Patients() : next_id(1), count(0) {}

    // Create a patient with auto-generated id and insert into table.
    // Returns the assigned patient id.
    int create(const std::string& first, const std::string& last,
               const std::string& gender, const std::string& dob,
               const std::string& phone, const std::string& address,
               int national_id) {
        int id = next_id++;
        Patient p(id, first, last, gender, dob, phone, address, national_id);
        ht.insert(id, p);
        ++count;
        return id;
    }

    // Insert an existing patient. Returns false if id already exists.
    bool add(const Patient& p) {
        if (ht.search(p.getID()) != nullptr) return false;
        ht.insert(p.getID(), p);
        ++count;
        if (p.getID() >= next_id) next_id = p.getID() + 1;
        return true;
    }

    // Find patient by id (returns pointer into HashTable storage). May return nullptr.
    Patient* find(int patient_id) {
        return ht.search(patient_id);
    }

    // Remove patient by id. Returns true if removed.
    bool remove(int patient_id) {
        if (ht.search(patient_id) == nullptr) return false;
        ht.remove(patient_id);
        if (count > 0) --count;
        return true;
    }

    // Update phone/address helpers (return false if not found)
    bool updatePhone(int patient_id, const std::string& phone) {
        Patient* p = ht.search(patient_id);
        if (!p) return false;
        p->setPhone(phone);
        return true;
    }

    bool updateAddress(int patient_id, const std::string& addr) {
        Patient* p = ht.search(patient_id);
        if (!p) return false;
        p->setAddress(addr);
        return true;
    }

    // Display all patients using HashTable::display(). Requires operator<< for Patient.
    void displayAll() {
        ht.display();
    }

    bool empty() const { return count == 0; }
    size_t size() const { return count; }
    int getNextID() const { return next_id; }

private:
    HashTable<int, Patient> ht;
    int next_id;
    size_t count;
};

#endif // PATIENTS_H
