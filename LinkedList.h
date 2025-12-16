#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include "Display.h"

using namespace std;

template <typename T>
struct Node {
    T data;
    Node* next;

    Node(T val) : data(val), next(nullptr) {}
};

template <typename T>
class LinkedList {
private:
    Node<T>* head;
    int count;

public:
    LinkedList() : head(nullptr), count(0) {}

    ~LinkedList() {
        clear();
    }

    void insertHead(T val) {
        Node<T>* newNode = new Node<T>(val);
        newNode->next = head;
        head = newNode;
        count++;
    }

    void insertTail(T val) {
        Node<T>* newNode = new Node<T>(val);
        if (!head) {
            head = newNode;
        } else {
            Node<T>* temp = head;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
        count++;
    }

    bool remove(T val) {
        if (!head) return false;

        if (head->data == val) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
            count--;
            return true;
        }

        Node<T>* current = head;
        while (current->next) {
            if (current->next->data == val) {
                Node<T>* temp = current->next;
                current->next = temp->next;
                delete temp;
                count--;
                return true;
            }
            current = current->next;
        }
        return false;
    }

    bool search(T val) const {
        Node<T>* temp = head;
        while (temp) {
            if (temp->data == val) return true;
            temp = temp->next;
        }
        return false;
    }

    void display() const {
        if (!head) {
            cout << "List is empty.\n";
            return;
        }
        Node<T>* temp = head;
        while (temp) {
            cout << temp->data << " -> ";
            temp = temp->next;
        }
        cout << "NULL\n";
    }

    void clear() {
        Node<T>* temp = head;
        while (temp) {
            Node<T>* nextNode = temp->next;
            delete temp;
            temp = nextNode;
        }
        head = nullptr;
        count = 0;
    }

    bool isEmpty() const {
        return head == nullptr;
    }

    int size() const {
        return count;
    }

    // Copy Constructor
    LinkedList(const LinkedList& other) : head(nullptr), count(0) {
        Node<T>* temp = other.head;
        while (temp) {
            insertTail(temp->data);
            temp = temp->next;
        }
    }

    // Assignment Operator
    LinkedList& operator=(const LinkedList& other) {
        if (this != &other) {
            clear();
            Node<T>* temp = other.head;
            while (temp) {
                insertTail(temp->data);
                temp = temp->next;
            }
        }
        return *this;
    }

    // Get data by index (0-based)
    T get(int index) const {
        if (index < 0 || index >= count) {
            throw out_of_range("Index out of bounds");
        }
        Node<T>* temp = head;
        for (int i = 0; i < index; i++) {
            temp = temp->next;
        }
        return temp->data;
    }

    // Iterator-like access for traversal if needed
    Node<T>* getHead() const {
        return head;
    }
};

#endif
