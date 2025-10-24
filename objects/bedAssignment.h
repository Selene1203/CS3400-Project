#ifndef BEDASSIGNMENT_H
#define BEDASSIGNMENT_H

#include <iostream>
#include <string>
using namespace std;

class BedAssignment {
private:
    int assignment_id;
    int patient_id;
    int bed_id;
    int room_id;
    string date_assigned;
    string status;  // e.g., "Assigned", "Released"

public:
    // Constructors
    BedAssignment() : assignment_id(0), patient_id(0), bed_id(0), room_id(0), status("Unassigned") {}

    BedAssignment(int a_id, int p_id, int b_id, int r_id, string date, string s = "Assigned")
        : assignment_id(a_id), patient_id(p_id), bed_id(b_id), room_id(r_id),
          date_assigned(date), status(s) {}

    // Getters
    int getAssignmentID() const { return assignment_id; }
    int getPatientID() const { return patient_id; }
    int getBedID() const { return bed_id; }
    int getRoomID() const { return room_id; }
    string getDateAssigned() const { return date_assigned; }
    string getStatus() const { return status; }

    // Setters
    void setStatus(string s) { status = s; }
    void setDate(string d) { date_assigned = d; }

    // Display
    void display() const {
        cout << "Assignment ID: " << assignment_id
             << " | Patient ID: " << patient_id
             << " | Room ID: " << room_id
             << " | Bed ID: " << bed_id
             << " | Date: " << date_assigned
             << " | Status: " << status << endl;
    }

    // Comparison
    bool operator==(const BedAssignment& other) const {
        return assignment_id == other.assignment_id;
    }
};

#endif
