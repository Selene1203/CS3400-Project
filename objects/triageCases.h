#ifndef TRIAGECASES_H
#define TRIAGECASES_H

#include <iostream>
#include "../utils/priorityQueue.h"
#include "traigeCase.h" // current project file (struct Case)

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

private:
    PriorityQueue<Case> pq;
    size_t count = 0;
};

#endif // TRIAGECASES_H