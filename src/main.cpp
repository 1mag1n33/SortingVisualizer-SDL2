#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <thread>
#include "sorts/sorts.h"
#include "utils.h"

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1090

bool quit = false;
int* array = nullptr;
int nodeSize = 0;
int sortingSpeed = 0;
int choice = 0;

int main(int argc, char* argv[]) {
    printf("Sorting Algorithm Visualizer\n");
    printf("1. Bubble Sort\n");
    printf("2. Selection Sort\n");
    printf("3. Insertion Sort\n");
    printf("4. Quit\n");

    int userChoice;
    do {
        printf("Enter your choice: ");
        scanf_s("%d", &userChoice);
        if (userChoice < 1 || userChoice > 4) {
            printf("Invalid choice. Please enter a number between 1 and 4.\n");
        }
    } while (userChoice < 1 || userChoice > 4);

    choice = userChoice;

    if (choice == 4) {
        printf("Quitting...\n");
        return 0;
    }

    printf("Enter node size: ");
    scanf_s("%d", &nodeSize);

    printf("Enter sorting speed (milliseconds per step): ");
    scanf_s("%d", &sortingSpeed);

    array = new int[nodeSize];
    for (int i = 0; i < nodeSize; ++i) {
        array[i] = rand() % (SCREEN_HEIGHT - 20) + 10;
    }

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }
    SDL_Window* window = SDL_CreateWindow("Sorting Visualizer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    int newSortingSpeed = sortingSpeed / 1000;
    newSortingSpeed = std::max(1, newSortingSpeed);
    std::thread renderThread(Utils::renderArrayThread, renderer, array, nodeSize, SCREEN_WIDTH, SCREEN_HEIGHT, newSortingSpeed, std::ref(quit));

    SDL_Event e;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true; // Use the global 'quit' variable
            }
        }

        // Ensure proper synchronization between main thread and rendering thread
        // Update shared variables if necessary
        switch (choice) {
        case 1:
        {
            Bubble bubble;
            bubble.bubbleSort(array, nodeSize, newSortingSpeed);
            break;
        }
        case 2:
            // Call function to visualize Selection Sort
            break;
        case 3:
            // Call function to visualize Insertion Sort
            break;
        default:
            break;
        }
    }

    renderThread.join();
    delete[] array; // Free allocated memory
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
