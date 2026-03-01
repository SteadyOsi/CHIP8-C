#include <SDL2/SDL.h>
#include <iostream>
#include <array>

int main() {

    std::array<std::array<bool, 64>, 32> buffer;

    for(size_t i = 0; i < buffer.size(); i++){
        for(size_t j = 0; j < buffer[i].size(); j++){
            buffer[i][j] = false; 
        }
    }

    buffer[0][0] = true;

    buffer[1][1] = true;

    buffer[4][0] = true;
    buffer[4][1] = true;
    buffer[4][2] = true;

    int scale = 20;
    int window_Height = 32 * scale;
    int window_Width = 64 * scale;

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cout << "SDL Init failed\n";
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow(
        "CHIP8",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        window_Width, window_Height,
        SDL_WINDOW_SHOWN
    );

    if (!window) {
        std::cout << "Window creation failed: " << SDL_GetError() << "\n";
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(
        window, -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    bool running = true;
    SDL_Event e;

    int t = 0;

    while(running) {
        // 1) events 
        while(SDL_PollEvent(&e)){
            if (e.type == SDL_QUIT) running = false;
            if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) running = false;
        }


        // 2) Background colour (changes over time)
        // SDL_SetRenderDrawColor(renderer, R, G, B, A);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

        // 3) Clear screen (fills with current draw colour)
        SDL_RenderClear(renderer);

        for(int i = 0; i < buffer.size(); i++){
            for(int j = 0; j < buffer[i].size(); j++){
                if(buffer[i][j] == true){

                    // 4) Draw a filled rectangle
                    SDL_Rect rect {i*scale, j*scale, 1*scale, 1*scale };
                    SDL_SetRenderDrawColor(renderer, 240, 240, 240, 255);
                    SDL_RenderFillRect(renderer, &rect);

                    // 5) Draw rectangle outline
                    // SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                    // SDL_RenderDrawRect(renderer, &rect);
                } 
            }
        }

        // 6) Present frame (actually shows it)
        SDL_RenderPresent(renderer);

        t++;
    }

    // SDL_Delay(6000);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}