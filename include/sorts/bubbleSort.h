#pragma once
#include "SDL2/SDL.h"

class Bubble {
public:
    void bubbleSort(int array[], int n, int sortingSpeed) {
        printf("Starting bubble sort...\n");
        for (int i = 0; i < n - 1; ++i) {
            printf("Pass %d:\n", i + 1);
            for (int j = 0; j < n - i - 1; ++j) {
                if (array[j] > array[j + 1]) {
                    printf("Swapping elements at indices %d and %d\n", j, j + 1);
                    int temp = array[j];
                    array[j] = array[j + 1];
                    array[j + 1] = temp;

                    printf("Array after swap: ");
                    printArray(array, n);
                    SDL_Delay(sortingSpeed);
                }
            }
        }
        printf("Bubble sort completed.\n");
    }

    void printArray(int array[], int n) {
        for (int i = 0; i < n; ++i) {
            printf("%d ", array[i]);
        }
        printf("\n");
    }
};
