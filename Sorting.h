#ifndef SORTING_H
#define SORTING_H

// +==========================================================================+
// |                          SORTING ALGORITHMS                              |
// |  Bubble Sort, Selection Sort, Insertion Sort, Merge Sort, Quick Sort     |
// +==========================================================================+

#include "Display.h"

template <typename T>
class Sorting {
private:
    // =======================================================================
    // MERGE SORT HELPERS
    // =======================================================================
    static void merge(T arr[], int left, int mid, int right) {
        int n1 = mid - left + 1;
        int n2 = right - mid;

        T* L = new T[n1];
        T* R = new T[n2];

        for (int i = 0; i < n1; i++)
            L[i] = arr[left + i];
        for (int j = 0; j < n2; j++)
            R[j] = arr[mid + 1 + j];

        int i = 0, j = 0, k = left;

        while (i < n1 && j < n2) {
            if (L[i] <= R[j]) {
                arr[k] = L[i];
                i++;
            } else {
                arr[k] = R[j];
                j++;
            }
            k++;
        }

        while (i < n1) { arr[k] = L[i]; i++; k++; }
        while (j < n2) { arr[k] = R[j]; j++; k++; }

        delete[] L;
        delete[] R;
    }

    static void mergeSortRec(T arr[], int left, int right) {
        if (left < right) {
            int mid = left + (right - left) / 2;
            mergeSortRec(arr, left, mid);
            mergeSortRec(arr, mid + 1, right);
            merge(arr, left, mid, right);
        }
    }

    // =======================================================================
    // QUICK SORT HELPERS
    // =======================================================================
    static int partition(T arr[], int low, int high) {
        T pivot = arr[high];
        int i = (low - 1);

        for (int j = low; j <= high - 1; j++) {
            if (arr[j] < pivot) {
                i++;
                T temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
        T temp = arr[i + 1];
        arr[i + 1] = arr[high];
        arr[high] = temp;
        return (i + 1);
    }

    static void quickSortRec(T arr[], int low, int high) {
        if (low < high) {
            int pi = partition(arr, low, high);
            quickSortRec(arr, low, pi - 1);
            quickSortRec(arr, pi + 1, high);
        }
    }

public:
    // =======================================================================
    // BUBBLE SORT - O(n^2) - Compares adjacent elements and swaps
    // =======================================================================
    static void bubbleSort(T arr[], int size) {
        for (int i = 0; i < size - 1; i++) {
            bool swapped = false;
            for (int j = 0; j < size - i - 1; j++) {
                if (arr[j] > arr[j + 1]) {
                    // Swap adjacent elements
                    T temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                    swapped = true;
                }
            }
            // Optimization: if no swaps, array is sorted
            if (!swapped) break;
        }
    }

    // =======================================================================
    // SELECTION SORT - O(n^2) - Finds minimum and places at beginning
    // =======================================================================
    static void selectionSort(T arr[], int size) {
        for (int i = 0; i < size - 1; i++) {
            int minIdx = i;
            // Find minimum element in unsorted portion
            for (int j = i + 1; j < size; j++) {
                if (arr[j] < arr[minIdx]) {
                    minIdx = j;
                }
            }
            // Swap minimum with first unsorted element
            if (minIdx != i) {
                T temp = arr[i];
                arr[i] = arr[minIdx];
                arr[minIdx] = temp;
            }
        }
    }

    // =======================================================================
    // INSERTION SORT - O(n^2) - Inserts each element into sorted portion
    // =======================================================================
    static void insertionSort(T arr[], int size) {
        for (int i = 1; i < size; i++) {
            T key = arr[i];
            int j = i - 1;
            
            // Shift elements greater than key to the right
            while (j >= 0 && arr[j] > key) {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = key;
        }
    }

    // =======================================================================
    // MERGE SORT - O(n log n) - Divide and Conquer
    // =======================================================================
    static void mergeSort(T arr[], int size) {
        mergeSortRec(arr, 0, size - 1);
    }

    // =======================================================================
    // QUICK SORT - O(n log n) average - Pivot-based partitioning
    // =======================================================================
    static void quickSort(T arr[], int size) {
        quickSortRec(arr, 0, size - 1);
    }
};

#endif