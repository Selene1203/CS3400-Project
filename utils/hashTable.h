#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "linkedList.h"
#include <iostream>
#include <functional>
using namespace std;

template <typename Key, typename Value>
struct Pair {
    Key key;
    Value value;

    bool operator==(const Pair& other) const {
        return key == other.key;
    }
};

template <typename Key, typename Value>
class HashTable {
private:
    static const int TABLE_SIZE = 10;
    LinkedList<Pair<Key, Value>> table[TABLE_SIZE];

    int hashFunction(Key key) {
        return key % TABLE_SIZE;
    }

public:
    void insert(Key key, Value value) {
        Pair<Key, Value> p = {key, value};
        int index = hashFunction(key);
        table[index].insertAtEnd(p);
    }

    Value* search(Key key) {
        int index = hashFunction(key);
        Node<Pair<Key, Value>>* temp = table[index].getHead();
        while (temp != nullptr) {
            if (temp->data.key == key)
                return &temp->data.value;
            temp = temp->next;
        }
        return nullptr;
    }

    void remove(Key key) {
        int index = hashFunction(key);
        Pair<Key, Value> p = {key, Value()};
        table[index].remove(p);
    }

    void display() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            cout << "Bucket " << i << ": ";
            Node<Pair<Key, Value>>* temp = table[i].getHead();
            while (temp != nullptr) {
                cout << "(" << temp->data.key << ", " << temp->data.value << ") -> ";
                temp = temp->next;
            }
            cout << "NULL" << endl;
        }
    }

    // Iterate through all entries (non-const). Callback receives (key, value&)
    void forEach(const std::function<void(const Key&, Value&)>& fn) {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            Node<Pair<Key, Value>>* temp = table[i].getHead();
            while (temp != nullptr) {
                fn(temp->data.key, temp->data.value);
                temp = temp->next;
            }
        }
    }

    // Iterate through all entries (const). Callback receives (key, const value&)
    void forEachConst(const std::function<void(const Key&, const Value&)>& fn) const {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            Node<Pair<Key, Value>>* temp = table[i].getHead();
            while (temp != nullptr) {
                fn(temp->data.key, temp->data.value);
                temp = temp->next;
            }
        }
    }
};

#endif
