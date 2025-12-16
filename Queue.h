#ifndef QUEUE_H
#define QUEUE_H

#include "LinkedList.h"

template <typename T>
class Queue {
private:
    Node<T>* frontNode;
    Node<T>* rearNode;
    int count;

public:
    Queue() : frontNode(nullptr), rearNode(nullptr), count(0) {}

    ~Queue() {
        while (!isEmpty()) {
            dequeue();
        }
    }

    void enqueue(T val) {
        Node<T>* newNode = new Node<T>(val);
        if (isEmpty()) {
            frontNode = rearNode = newNode;
        } else {
            rearNode->next = newNode;
            rearNode = newNode;
        }
        count++;
    }

    void dequeue() {
        if (isEmpty()) {
            Display::printError("Queue Underflow");
            return;
        }
        Node<T>* temp = frontNode;
        frontNode = frontNode->next;
        if (frontNode == nullptr) {
            rearNode = nullptr;
        }
        delete temp;
        count--;
    }

    T front() const {
        if (isEmpty()) {
            return T(); // Caller should check isEmpty
        }
        return frontNode->data;
    }

    bool isEmpty() const {
        return frontNode == nullptr;
    }

    int size() const {
        return count;
    }
};

#endif
