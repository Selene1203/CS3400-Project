#ifndef SYSTEM_H
#define SYSTEM_H

#include <iostream>
#include <string>
#include <vector>
#include "patients.h"
#include "triageCases.h"
#include "rooms.h"
#include "logging.h"

// System: high-level facade to interact with hospital data (patients, triage, rooms, logs)
class System {
public:
    System(const std::string& dataDir = "data")
        : patientsPath(dataDir + "/patients.txt"),
          triagePath(dataDir + "/traigecases.txt"),
          roomsPath(dataDir + "/rooms.txt"),
          logsPath(dataDir + "/logging.txt") {}

    // Load all persisted data (returns true if all loads succeeded)
    bool loadAll() {
        bool ok = true;
        ok &= patients.loadFromFile(patientsPath);
        ok &= triage.loadFromFile(triagePath);
        ok &= rooms.loadFromFile(roomsPath);
        ok &= logs.loadFromFile(logsPath);
        return ok;
    }

    // Save all to disk
    bool saveAll() const {
        bool ok = true;
        ok &= patients.saveToFile(patientsPath);
        ok &= triage.saveToFile(triagePath);
        ok &= rooms.saveToFile(roomsPath);
        ok &= logs.saveToFile(logsPath);
        return ok;
    }

    // Register a new patient and log the event. Returns new patient id.
    int registerPatient(const std::string& first, const std::string& last,
                        const std::string& gender, const std::string& dob,
                        const std::string& phone, const std::string& address,
                        int national_id, const std::string& timestamp="") {
        int id = patients.create(first, last, gender, dob, phone, address, national_id);
        std::string ts = timestamp.empty() ? "now" : timestamp;
        logs.append(id, "Registered new patient", ts);
        return id;
    }

    // Add a triage case for a patient and log it
    void addTriageCase(int patient_id, int level, const std::string& condition, const std::string& time_reported) {
        Case c(patient_id, condition, level, time_reported);
        triage.push(c);
        logs.append(patient_id, "Added to triage: " + condition, time_reported);
    }

    // Assign the next free bed to a patient. Returns assigned bed id or -1 if none.
    int assignBedToPatient(int patient_id, const std::string& timestamp="") {
        Bed* freeBed = rooms.findFreeBed();
        if (!freeBed) return -1;
        int bedId = freeBed->getBedID();
        if (!rooms.assignBedByID(bedId)) return -1;
        logs.append(patient_id, "Assigned to bed " + std::to_string(bedId), timestamp.empty() ? "now" : timestamp);
        return bedId;
    }

    bool releaseBed(int bed_id, const std::string& timestamp="") {
        bool ok = rooms.releaseBedByID(bed_id);
        if (ok) logs.append(0, "Released bed " + std::to_string(bed_id), timestamp.empty() ? "now" : timestamp);
        return ok;
    }

    // Query helpers
    Patient* findPatient(int id) { return patients.find(id); }
    std::vector<Log> getPatientLogs(int id) { return logs.getLogsForPatient(id); }
    Case peekNextTriage() { return triage.top(); }
    Bed* findFreeBed() { return rooms.findFreeBed(); }

    // Simple interactive loop (blocking) for demo purposes
    void runCLI() {
        auto readLine = [&](const std::string &prompt)->std::string {
            std::string line;
            std::cout << prompt;
            if (!std::getline(std::cin, line)) return std::string();
            return line;
        };

        while (true) {
            std::cout << "\n===== Hospital CLI =====\n";
            std::cout << "1) Register patient\n2) Add triage case\n3) Assign next free bed to patient\n";
            std::cout << "4) Release bed\n5) View patient\n6) View patient logs\n7) Save and exit\n";

            std::string choiceStr = readLine("Choice (1-7): ");
            if (choiceStr.empty()) break; // EOF or empty

            int choice = 0;
            try { choice = std::stoi(choiceStr); } catch(...) { continue; }

            if (choice == 7) { saveAll(); break; }

            if (choice == 1) {
                // Prompt for each field on its own line so fields can contain spaces
                std::string f = readLine("First name (e.g. John): "); if (f.empty()) continue;
                std::string l = readLine("Last name (e.g. Doe): "); if (l.empty()) continue;
                std::string g = readLine("Gender (M/F/Other): ");
                std::string d = readLine("DOB (YYYY-MM-DD): ");
                std::string p = readLine("Phone (e.g. 555-1234): ");
                std::string a = readLine("Address (street, city): ");
                std::string nidStr = readLine("National ID (numbers): ");
                int nid = 0; try { nid = std::stoi(nidStr); } catch(...) { nid = 0; }
                int id = registerPatient(f,l,g,d,p,a,nid);
                std::cout << "Registered id=" << id << '\n';
            } else if (choice == 2) {
                std::string pidStr = readLine("Patient ID (numeric): "); if (pidStr.empty()) continue;
                std::string levelStr = readLine("Triage level (1=critical, higher=less urgent): "); if (levelStr.empty()) continue;
                std::string condition = readLine("Condition (brief description): ");
                std::string time = readLine("Time reported (e.g. 2025-10-26T12:00): ");
                int pid = 0; int level = 0;
                try { pid = std::stoi(pidStr); } catch(...) { pid = 0; }
                try { level = std::stoi(levelStr); } catch(...) { level = 0; }
                addTriageCase(pid, level, condition, time);
            } else if (choice == 3) {
                std::string pidStr = readLine("Patient ID (numeric): "); if (pidStr.empty()) continue;
                int pid = 0; try { pid = std::stoi(pidStr); } catch(...) { pid = 0; }
                int bid = assignBedToPatient(pid);
                if (bid < 0) std::cout << "No free bed available\n"; else std::cout << "Assigned bed " << bid << '\n';
            } else if (choice == 4) {
                std::string bidStr = readLine("Bed ID (numeric): "); if (bidStr.empty()) continue;
                int bid = 0; try { bid = std::stoi(bidStr); } catch(...) { bid = 0; }
                if (!releaseBed(bid)) std::cout << "Failed\n"; else std::cout << "Released\n";
            } else if (choice == 5) {
                std::string pidStr = readLine("Patient ID (numeric): "); if (pidStr.empty()) continue;
                int pid = 0; try { pid = std::stoi(pidStr); } catch(...) { pid = 0; }
                Patient* p = findPatient(pid);
                if (p) p->display(); else std::cout << "Not found\n";
            } else if (choice == 6) {
                std::string pidStr = readLine("Patient ID: "); if (pidStr.empty()) continue;
                int pid = 0; try { pid = std::stoi(pidStr); } catch(...) { pid = 0; }
                auto logsv = getPatientLogs(pid);
                for (auto &l : logsv) l.display();
            }
        }
    }

private:
    Patients patients;
    TriageCases triage;
    Rooms rooms;
    Logging logs;

    std::string patientsPath;
    std::string triagePath;
    std::string roomsPath;
    std::string logsPath;
};

#endif // SYSTEM_H
