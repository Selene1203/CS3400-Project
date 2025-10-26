#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include <string>
using namespace std;

// Node structure
template <typename T>
struct ListNode {
    T data;
    ListNode* next;
    ListNode(T val) : data(val), next(nullptr) {}
};

// Provide a compatibility alias expected by other headers
template <typename T>
using Node = ListNode<T>;

// Linked List ADT
template <typename T>
class LinkedList {
private:
    ListNode<T>* head;

public:
    LinkedList() : head(nullptr) {}

    // Expose head for other utilities that rely on direct access
    Node<T>* getHead() {
        return head;
    }
    // const overload
    Node<T>* getHead() const {
        return head;
    }

    // Add item at end
    void insertAtEnd(T value) {
        ListNode<T>* newNode = new ListNode<T>(value);
        if (head == nullptr) {
            head = newNode;
            return;
        }
        ListNode<T>* temp = head;
        while (temp->next != nullptr)
            temp = temp->next;
        temp->next = newNode;
    }

    // Remove item
    void remove(T value) {
        if (head == nullptr) return;
        if (head->data == value) {
            ListNode<T>* temp = head;
            head = head->next;
            delete temp;
            return;
        }
        ListNode<T>* prev = head;
        ListNode<T>* curr = head->next;
        while (curr != nullptr) {
            if (curr->data == value) {
                prev->next = curr->next;
                delete curr;
                return;
            }
            prev = curr;
            curr = curr->next;
        }
    }

    // Search item
    ListNode<T>* search(T value) {
        ListNode<T>* temp = head;
        while (temp != nullptr) {
            if (temp->data == value)
                return temp;
            temp = temp->next;
        }
        return nullptr;
    }

    // Display items
    void display() {
        ListNode<T>* temp = head;
        while (temp != nullptr) {
            cout << temp->data << " -> ";
            temp = temp->next;
        }
        cout << "NULL" << endl;
    }

    bool isEmpty() {
        return head == nullptr;
    }
};

#endif
