#ifndef HEAP_H
#define HEAP_H

#include <iostream>
#include "Display.h"

template <typename T>
class Heap {
private:
    T* arr;
    int capacity;
    int currentSize;

    void heapify(int i) {
        int smallest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < currentSize && arr[left] < arr[smallest])
            smallest = left;

        if (right < currentSize && arr[right] < arr[smallest])
            smallest = right;

        if (smallest != i) {
            T temp = arr[i];
            arr[i] = arr[smallest];
            arr[smallest] = temp;
            heapify(smallest);
        }
    }

public:
    Heap(int cap = 100) : capacity(cap), currentSize(0) {
        arr = new T[capacity];
    }

    ~Heap() {
        delete[] arr;
    }

    void insert(T val) {
        if (currentSize == capacity) {
            Display::printError("Heap Overflow");
            return;
        }

        currentSize++;
        int i = currentSize - 1;
        arr[i] = val;

        while (i != 0 && arr[(i - 1) / 2] > arr[i]) {
            T temp = arr[i];
            arr[i] = arr[(i - 1) / 2];
            arr[(i - 1) / 2] = temp;
            i = (i - 1) / 2;
        }
    }

    T extractMin() {
        if (currentSize <= 0) {
            Display::printError("Heap Underflow");
            return T(); 
        }
        if (currentSize == 1) {
            currentSize--;
            return arr[0];
        }

        T root = arr[0];
        arr[0] = arr[currentSize - 1];
        currentSize--;
        heapify(0);

        return root;
    }

    T getMin() const {
        if (currentSize <= 0) return T();
        return arr[0];
    }

    bool isEmpty() const {
        return currentSize == 0;
    }

    int size() const {
        return currentSize;
    }
};

#endif
