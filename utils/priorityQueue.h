#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include "linkedList.h"
#include <iostream>
using namespace std;

template <typename T>
struct PQItem {
    int priority;
    T data;
};

// Custom comparison for equality
template <typename T>
bool operator==(const PQItem<T>& a, const PQItem<T>& b) {
    return (a.data == b.data && a.priority == b.priority);
}

template <typename T>
class PriorityQueue {
private:
    LinkedList<PQItem<T>> list;

public:
    // Insert in order (lower priority value = higher priority)
    void insert(T data, int priority) {
        PQItem<T> newItem = {priority, data};
        Node<PQItem<T>>* newNode = new Node<PQItem<T>>(newItem);

        Node<PQItem<T>>* head = list.getHead();

        // If list is empty or new item has higher priority
        if (head == nullptr || newItem.priority < head->data.priority) {
            newNode->next = head;
            *((Node<PQItem<T>>**)&list) = newNode; // place at front
            return;
        }

        // Otherwise, find correct spot
        Node<PQItem<T>>* current = head;
        while (current->next != nullptr && current->next->data.priority <= newItem.priority)
            current = current->next;

        newNode->next = current->next;
        current->next = newNode;
    }

    // Remove top priority
    T removeHighestPriority() {
        Node<PQItem<T>>* head = list.getHead();
        if (head == nullptr) {
            cout << "Queue empty!" << endl;
            return T();
        }

        PQItem<T> item = head->data;
        list.remove(head->data);
        return item.data;
    }

    // Peek at top
    T peek() {
        Node<PQItem<T>>* head = list.getHead();
        if (head == nullptr) {
            cout << "Queue empty!" << endl;
            return T();
        }
        return head->data.data;
    }

    bool isEmpty() {
        return list.isEmpty();
    }

    void display() {
        Node<PQItem<T>>* temp = list.getHead();
        while (temp != nullptr) {
            cout << "(" << temp->data.data << ", p=" << temp->data.priority << ") -> ";
            temp = temp->next;
        }
        cout << "NULL" << endl;
    }
};

#endif
