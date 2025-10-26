#ifndef PATIENTS_H
#define PATIENTS_H

#include <iostream>
#include <string>
#include "patient.h"
#include "../utils/hashTable.h"
#include <fstream>
#include <sstream>

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

    // Persist patients to a simple text file. Each line is a record with fields
    // separated by '|': id|first_name|last_name|gender|dob|phone|address|national_id
    // Returns true on success.
    bool saveToFile(const std::string& path) const {
        std::ofstream out(path);
        if (!out.is_open()) return false;

        ht.forEachConst([&](const int& id, const Patient& p){
            out << p.getID() << '|' << p.getFirstName() << '|' << p.getLastName() << '|'
                << p.getGender() << '|' << p.getDOB() << '|' << p.getPhone() << '|'
                << p.getAddress() << '|' << p.getNationalID() << '\n';
        });

        out.close();
        return true;
    }

    // Load patients from file. If clearExisting is true (default) current data is cleared.
    // Expects same '|' separated format as saveToFile. Returns true on success.
    bool loadFromFile(const std::string& path, bool clearExisting = true) {
        std::ifstream in(path);
        if (!in.is_open()) return false;

        if (clearExisting) {
            // recreate internal hash table by creating a fresh instance
            ht = HashTable<int, Patient>();
            count = 0;
            next_id = 1;
        }

        std::string line;
        while (std::getline(in, line)) {
            if (line.empty()) continue;
            std::istringstream ss(line);
            std::string token;
            std::vector<std::string> parts;
            while (std::getline(ss, token, '|')) parts.push_back(token);
            if (parts.size() != 8) continue; // skip malformed lines

            int id = std::stoi(parts[0]);
            std::string first = parts[1];
            std::string last = parts[2];
            std::string gender = parts[3];
            std::string dob = parts[4];
            std::string phone = parts[5];
            std::string address = parts[6];
            int national = std::stoi(parts[7]);

            Patient p(id, first, last, gender, dob, phone, address, national);
            add(p);
        }

        in.close();
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
