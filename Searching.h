#ifndef SEARCHING_H
#define SEARCHING_H

#include "Display.h"

template <typename T>
class Searching {
public:
    // Linear Search
    // Returns index if found, -1 otherwise
    static int linearSearch(T arr[], int size, T key) {
        for (int i = 0; i < size; i++) {
            if (arr[i] == key) {
                return i;
            }
        }
        return -1;
    }

    // Binary Search
    // Requires sorted array
    // Returns index if found, -1 otherwise
    static int binarySearch(T arr[], int size, T key) {
        int left = 0;
        int right = size - 1;

        while (left <= right) {
            int mid = left + (right - left) / 2;

            if (arr[mid] == key) {
                return mid;
            }

            if (arr[mid] < key) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        return -1;
    }
};

#endif
