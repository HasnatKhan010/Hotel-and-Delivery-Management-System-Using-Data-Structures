#ifndef SORTING_H
#define SORTING_H
//sorting algorithms: merge sort and quick sort
#include "Display.h"

template <typename T>
class Sorting {
private:
    static void merge(T arr[], int left, int mid, int right) {
        int n1 = mid - left + 1;
        int n2 = right - mid;

        T* L = new T[n1];
        T* R = new T[n2];

        for (int i = 0; i < n1; i++)
            L[i] = arr[left + i];
        for (int j = 0; j < n2; j++)
            R[j] = arr[mid + 1 + j];

        int i = 0;
        int j = 0;
        int k = left;

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

        while (i < n1) {
            arr[k] = L[i];
            i++;
            k++;
        }

        while (j < n2) {
            arr[k] = R[j];
            j++;
            k++;
        }

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
    static void mergeSort(T arr[], int size) {
        mergeSortRec(arr, 0, size - 1);
    }

    static void quickSort(T arr[], int size) {
        quickSortRec(arr, 0, size - 1);
    }
};

#endif
