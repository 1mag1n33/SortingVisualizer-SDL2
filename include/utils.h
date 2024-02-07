#pragma once

#include <SDL2/SDL.h>
#include <stdio.h>

class Utils {
public:
    void drawArray(SDL_Renderer* renderer, int array[], int n, int SCREEN_WIDTH, int SCREEN_HEIGHT) {
        printf("Rendering array...\n");
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        // Set the width of each rectangle to 1 for minimal space between them
        int arrayElementWidth = 1;
        for (int i = 0; i < n; ++i) {
            // Adjust the position of the rectangles to eliminate gaps
            SDL_Rect rect = { i * arrayElementWidth, SCREEN_HEIGHT - array[i], arrayElementWidth, array[i] };
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderFillRect(renderer, &rect);
        }
        SDL_RenderPresent(renderer);
    }



    static void renderArrayThread(SDL_Renderer* renderer, int array[], int n, int SCREEN_WIDTH, int SCREEN_HEIGHT, int sortingSpeed, bool& quit) {
        Utils utils;
        while (!quit) {
            utils.drawArray(renderer, array, n, SCREEN_WIDTH, SCREEN_HEIGHT);
            SDL_Delay(sortingSpeed);
        }
    }

};

