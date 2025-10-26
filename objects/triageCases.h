#ifndef TRIAGECASES_H
#define TRIAGECASES_H

#include <iostream>
#include "../utils/priorityQueue.h"
#include "traigeCase.h" // current project file (struct Case)
#include <fstream>
#include <sstream>
#include <vector>

// Provide operator<< for Case so PriorityQueue::display() can print items.
inline std::ostream& operator<<(std::ostream& os, const Case& c) {
    os << "PatientID:" << c.getPatientID()
       << " | Level:" << c.getLevel()
       << " | " << c.getCondition();
    return os;
}

// TriageCases: thin wrapper around the project's PriorityQueue<Case>
// - Uses Case::getLevel() as the priority (lower level => higher priority)
// - Tracks size because PriorityQueue doesn't expose it
class TriageCases {
public:
    TriageCases() = default;

    // Insert a case into the queue. Lower triage level is higher priority.
    void push(const Case& c) {
        pq.insert(c, c.getLevel());
        ++count;
    }

    // Pop highest-priority item. If empty, returns a default Case.
    Case pop() {
        if (pq.isEmpty()) return Case();
        --count;
        return pq.removeHighestPriority();
    }

    // Try to pop into out; returns false if empty.
    bool tryPop(Case& out) {
        if (pq.isEmpty()) return false;
        out = pq.removeHighestPriority();
        --count;
        return true;
    }

    // Peek at top; if empty returns default Case.
    Case top() {
        if (pq.isEmpty()) return Case();
        return pq.peek();
    }

    bool empty() { return pq.isEmpty(); }
    size_t size() const { return count; }

    // Display using PriorityQueue's display (relies on operator<< above)
    void displayAll() { pq.display(); }

    // Clear queue
    void clear() {
        while (!pq.isEmpty()) {
            pq.removeHighestPriority();
        }
        count = 0;
    }

    // Persist triage cases to a file. Each line: patient_id|triage_level|condition|time_reported
    bool saveToFile(const std::string& path) const {
        std::ofstream out(path);
        if (!out.is_open()) return false;

        pq.forEachConst([&](const PQItem<Case>& item){
            const Case& c = item.data;
            out << c.getPatientID() << '|' << c.getLevel() << '|' << c.getCondition() << '|' << c.getTimeReported() << '\n';
        });

        out.close();
        return true;
    }

    // Load triage cases from file. If clearExisting true (default), clears current queue.
    bool loadFromFile(const std::string& path, bool clearExisting = true) {
        std::ifstream in(path);
        if (!in.is_open()) return false;

        if (clearExisting) clear();

        std::string line;
        while (std::getline(in, line)) {
            if (line.empty()) continue;
            std::istringstream ss(line);
            std::string token;
            std::vector<std::string> parts;
            while (std::getline(ss, token, '|')) parts.push_back(token);
            if (parts.size() != 4) continue;

            int pid = std::stoi(parts[0]);
            int level = std::stoi(parts[1]);
            std::string cond = parts[2];
            std::string time = parts[3];

            Case c(pid, cond, level, time);
            push(c);
        }

        in.close();
        return true;
    }

private:
    PriorityQueue<Case> pq;
    size_t count = 0;
};

#endif // TRIAGECASES_H