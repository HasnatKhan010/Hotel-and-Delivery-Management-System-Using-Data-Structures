#ifndef STACK_H
#define STACK_H

#include "LinkedList.h"

template <typename T>
class Stack {
private:
    Node<T>* top;
    int count;

public:
    Stack() : top(nullptr), count(0) {}

    ~Stack() {
        while (!isEmpty()) {
            pop();
        }
    }

    void push(T val) {
        Node<T>* newNode = new Node<T>(val);
        newNode->next = top;
        top = newNode;
        count++;
    }

    void pop() {
        if (isEmpty()) {
            Display::printError("Stack Underflow");
            return;
        }
        Node<T>* temp = top;
        top = top->next;
        delete temp;
        count--;
    }

    T peek() const {
        if (isEmpty()) {
            // Depending on T, returning a default constructed object or throwing exception
            // For simplicity in this project, assuming caller checks isEmpty()
            // or returning a dummy value if T allows. 
            // Ideally should throw, but let's just return T() for now or handle carefully.
            return T(); 
        }
        return top->data;
    }

    bool isEmpty() const {
        return top == nullptr;
    }

    int size() const {
        return count;
    }
};

#endif
