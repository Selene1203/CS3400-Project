#ifndef TRIAGECASE_H
#define TRIAGECASE_H

#include <iostream>
#include <string>
using namespace std;

class TriageCase {
private:
    int patient_id;
    string condition;
    int triage_level; // 1 = critical, 5 = mild
    string time_reported;

public:
    // Constructors
    TriageCase() {}
    TriageCase(int id, string cond, int level, string time)
        : patient_id(id), condition(cond), triage_level(level), time_reported(time) {}

    // Getters
    int getPatientID() const { return patient_id; }
    string getCondition() const { return condition; }
    int getLevel() const { return triage_level; }
    string getTimeReported() const { return time_reported; }

    // Display
    void display() const {
        cout << "Patient ID: " << patient_id
             << " | Level: " << triage_level
             << " | Condition: " << condition
             << " | Time: " << time_reported << endl;
    }

    // Comparison (lower number = higher priority)
    bool operator<(const TriageCase& other) const {
        return triage_level < other.triage_level;
    }

    bool operator==(const TriageCase& other) const {
        return patient_id == other.patient_id && triage_level == other.triage_level;
    }
};

#endif
