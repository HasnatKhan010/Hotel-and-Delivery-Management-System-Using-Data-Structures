#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <string>
#include "LinkedList.h"

using namespace std;

template <typename K, typename V>
struct HashEntry {
    K key;
    V value;

    HashEntry(K k, V v) : key(k), value(v) {}
    HashEntry() {} // Default constructor

    bool operator==(const HashEntry& other) const {
        return key == other.key;
    }
    
    // Output stream operator for display
    friend ostream& operator<<(ostream& os, const HashEntry& entry) {
        os << "[" << entry.key << ": " << entry.value << "]";
        return os;
    }
};

template <typename K, typename V>
class HashTable {
private:
    static const int TABLE_SIZE = 100;
    LinkedList<HashEntry<K, V>>* table;

    int hashFunction(int key) const {
        return key % TABLE_SIZE;
    }

    int hashFunction(const string& key) const {
        int hash = 0;
        for (char c : key) {
            hash = (hash * 31 + c) % TABLE_SIZE;
        }
        return (hash < 0) ? -hash : hash;
    }

public:
    HashTable() {
        table = new LinkedList<HashEntry<K, V>>[TABLE_SIZE];
    }

    ~HashTable() {
        delete[] table;
    }

    void insert(K key, V value) {
        int index = hashFunction(key);
        // Ideally check if key exists and update, or just insert
        // For simplicity, just inserting (chaining handles collisions)
        // But to avoid duplicates, we might want to search first.
        // Since LinkedList::search checks exact match, we need a way to find by key.
        // For now, let's just append.
        table[index].insertTail(HashEntry<K, V>(key, value));
    }

    bool get(K key, V& outValue) const {
        int index = hashFunction(key);
        Node<HashEntry<K, V>>* current = table[index].getHead();
        while (current) {
            if (current->data.key == key) {
                outValue = current->data.value;
                return true;
            }
            current = current->next;
        }
        return false;
    }

    void remove(K key) {
        // This is tricky because LinkedList::remove takes a value (HashEntry)
        // We'd need to construct a dummy HashEntry with the key to remove it,
        // assuming operator== only checks key (which I did above).
        // However, we need a dummy value for V.
        // If V is a pointer or has default constructor, it works.
        int index = hashFunction(key);
        // We need to iterate and find to remove correctly or rely on operator==
        // Let's rely on operator== in HashEntry
        // But we need to construct a dummy entry.
        // This might be limited if V doesn't have a default constructor.
        // For this project, let's assume V has default constructor.
        V dummyVal = V(); 
        table[index].remove(HashEntry<K, V>(key, dummyVal));
    }

    void display() const {
        for (int i = 0; i < TABLE_SIZE; i++) {
            if (!table[i].isEmpty()) {
                cout << "Bucket " << i << ": ";
                table[i].display();
            }
        }
    }
};

#endif
