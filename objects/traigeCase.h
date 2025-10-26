#ifndef TRIAGECASE_H
#define TRIAGECASE_H

#include <iostream>
#include <string>

struct Case {
    int patient_id = 0;
    std::string condition;
    int triage_level = 5; // 1 = critical, 5 = mild
    std::string time_reported;

    Case() = default;
    Case(int id, const std::string& cond, int level, const std::string& time)
        : patient_id(id), condition(cond), triage_level(level), time_reported(time) {}

    int getPatientID() const { return patient_id; }
    const std::string& getCondition() const { return condition; }
    int getLevel() const { return triage_level; }
    const std::string& getTimeReported() const { return time_reported; }

    void display() const {
        std::cout << "Patient ID: " << patient_id
                  << " | Level: " << triage_level
                  << " | Condition: " << condition
                  << " | Time: " << time_reported << std::endl;
    }

    bool operator<(const Case& other) const {
        return triage_level < other.triage_level;
    }

    bool operator==(const Case& other) const {
        return patient_id == other.patient_id && triage_level == other.triage_level;
    }
};



#endif
