#include <SDL2/SDL.h>
#include <iostream>
#include <array>
#include "Graphics.h"
#include "CHIP8_cpu.h"

Graphics::Graphics()
{
}

void Graphics::init_Graphics(int scale){
    this->scale = scale;
    window_Width = 64 * scale;
    window_Height = 32 * scale;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        std::cout << "SDL Init failed\n";
    }

    window = SDL_CreateWindow(
        "CHIP8",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        window_Width, window_Height,
        SDL_WINDOW_SHOWN
    );

    if (!window) {
        std::cout << "Window creation failed: " << SDL_GetError() << "\n";
        SDL_Quit();
    }

    renderer = SDL_CreateRenderer(
        window, -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    if(!renderer){
        std::cout << "Renderer failed: " << SDL_GetError() << std::endl;
    }
}

void Graphics::Render_Graphics(const std::array<std::array<bool, 64>, 32>& cpuBuffer){
    // 2) Background colour (changes over time)
    // SDL_SetRenderDrawColor(renderer, R, G, B, A);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    // 3) Clear screen (fills with current draw colour)
    SDL_RenderClear(renderer);

    for(int y = 0; y < cpuBuffer.size(); y++){
        for(int x = 0; x < cpuBuffer[y].size(); x++){
            if(cpuBuffer[y][x] == true){

                // 4) Draw a filled rectangle
                SDL_Rect rect {x*scale, y*scale, scale, scale };
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
}

void Graphics::end_Game(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}