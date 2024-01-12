#include <SDL2/SDL.h>
#include <math.h>

void drawLine(SDL_Renderer *renderer, int x0, int y0, int x1, int y1) {
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int steps = (dx > dy) ? dx : dy;

    float Xinc = dx / (float)steps;
    float Yinc = dy / (float)steps;

    float X = x0;
    float Y = y0;

    for (int i = 0; i <= steps; i++) {
        SDL_RenderDrawPoint(renderer, round(X), round(Y));
        X += Xinc;
        Y += Yinc;
    }
}

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window;
    SDL_Renderer *renderer;

    SDL_CreateWindowAndRenderer(800, 600, 0, &window, &renderer);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Set color to red

    drawLine(renderer, 20, 20, 200, 200);

    SDL_RenderPresent(renderer);

    // Event loop to keep the window open
    SDL_Event event;
    int quit = 0;

    while (!quit) {
        quit = 0;
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}