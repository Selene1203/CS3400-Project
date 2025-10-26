#ifndef LOGGING_H
#define LOGGING_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "log.h"
#include "../utils/linkedList.h"

// Simple patient logging system.
// Stores Log entries in a linked list (chronological append). Provides query by patient id
// and persistence (save/load) using a simple '|' delimited text format:
// log_id|patient_id|timestamp|activity

class Logging {
public:
    Logging() : next_id(1) {}

    // Append a new log entry. Returns assigned log id.
    int append(int patient_id, const std::string& activity, const std::string& timestamp) {
        int id = next_id++;
        Log l(id, patient_id, activity, timestamp);
        entries.insertAtEnd(l);
        return id;
    }

    // Get all logs for a patient (ordered by insertion time)
    std::vector<Log> getLogsForPatient(int patient_id) const {
        std::vector<Log> out;
        Node<Log>* cur = entries.getHead();
        while (cur != nullptr) {
            if (cur->data.getPatientID() == patient_id) out.push_back(cur->data);
            cur = cur->next;
        }
        return out;
    }

    // Save logs to file. Returns true on success.
    bool saveToFile(const std::string& path) const {
        std::ofstream out(path);
        if (!out.is_open()) return false;
        Node<Log>* cur = entries.getHead();
        while (cur != nullptr) {
            const Log& l = cur->data;
            out << l.getLogID() << '|' << l.getPatientID() << '|' << l.getTimestamp() << '|' << l.getActivity() << '\n';
            cur = cur->next;
        }
        out.close();
        return true;
    }

    // Load logs from file. If clearExisting true (default) clears current logs.
    bool loadFromFile(const std::string& path, bool clearExisting = true) {
        std::ifstream in(path);
        if (!in.is_open()) return false;
        if (clearExisting) {
            entries = LinkedList<Log>();
            next_id = 1;
        }
        std::string line;
        while (std::getline(in, line)) {
            if (line.empty()) continue;
            std::istringstream ss(line);
            std::string token;
            std::vector<std::string> parts;
            while (std::getline(ss, token, '|')) parts.push_back(token);
            if (parts.size() < 4) continue; // malformed
            int lid = std::stoi(parts[0]);
            int pid = std::stoi(parts[1]);
            std::string ts = parts[2];
            std::string act = parts[3];
            Log l(lid, pid, act, ts);
            entries.insertAtEnd(l);
            if (lid >= next_id) next_id = lid + 1;
        }
        in.close();
        return true;
    }

    // Get all logs (copy)
    std::vector<Log> allLogs() const {
        std::vector<Log> out;
        Node<Log>* cur = entries.getHead();
        while (cur != nullptr) { out.push_back(cur->data); cur = cur->next; }
        return out;
    }

    bool empty() { return entries.isEmpty(); }

private:
    LinkedList<Log> entries;
    int next_id;
};

#endif // LOGGING_H
