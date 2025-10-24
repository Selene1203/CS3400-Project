#ifndef PATIENT_H
#define PATIENT_H

#include <iostream>
#include <string>
using namespace std;

class Patient {
private:
    int patient_id;
    string first_name;
    string last_name;
    string gender;
    string dob;
    string phone;
    string address;
    int national_id;

public:
    // Constructors
    Patient() {}
    Patient(int id, string f, string l, string g, string d, string p, string a, int n)
        : patient_id(id), first_name(f), last_name(l), gender(g),
          dob(d), phone(p), address(a), national_id(n) {}

    // Getters
    int getID() const { return patient_id; }
    string getName() const { return first_name + " " + last_name; }
    string getGender() const { return gender; }
    string getPhone() const { return phone; }
    int getNationalID() const { return national_id; }

    // Setters
    void setPhone(string p) { phone = p; }
    void setAddress(string a) { address = a; }

    // Display
    void display() const {
        cout << "Patient ID: " << patient_id << endl;
        cout << "Name: " << first_name << " " << last_name << endl;
        cout << "Gender: " << gender << endl;
        cout << "DOB: " << dob << endl;
        cout << "Phone: " << phone << endl;
        cout << "Address: " << address << endl;
        cout << "National ID: " << national_id << endl;
    }

    // Comparison
    bool operator==(const Patient& other) const {
        return patient_id == other.patient_id;
    }
};

#endif
