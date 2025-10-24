#ifndef LOG_H
#define LOG_H

#include <iostream>
#include <string>
using namespace std;

class Log {
private:
    int log_id;
    int patient_id;
    string activity;
    string timestamp;

public:
    // Constructors
    Log() {}
    Log(int lid, int pid, string act, string time)
        : log_id(lid), patient_id(pid), activity(act), timestamp(time) {}

    // Getters
    int getLogID() const { return log_id; }
    int getPatientID() const { return patient_id; }
    string getActivity() const { return activity; }
    string getTimestamp() const { return timestamp; }

    // Display
    void display() const {
        cout << "Log ID: " << log_id
             << " | Patient: " << patient_id
             << " | Activity: " << activity
             << " | Time: " << timestamp << endl;
    }

    // Comparison
    bool operator==(const Log& other) const {
        return log_id == other.log_id;
    }
};

#endif
