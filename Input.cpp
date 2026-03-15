#include "Input.h"
#include <SDL2/SDL.h>
#include <iostream>

int Input::mapKey(SDL_Keycode key)
{
    // Key pad mapping is as so: 

    // 1 2 3 C      1 2 3 4      0 1 2 3 
    // 4 5 6 D  =>  q w e r  =>  4 5 6 7
    // 7 8 9 E  =>  a s d f  =>  8 9 10 11
    // A 0 B F      z x c v      12 13 14 15
    
    switch(key)
    {
        case SDLK_1: return 0x1;
        case SDLK_2: return 0x2;
        case SDLK_3: return 0x3;
        case SDLK_4: return 0xC;

        case SDLK_q: return 0x4;
        case SDLK_w: return 0x5;
        case SDLK_e: return 0x6;
        case SDLK_r: return 0xD;

        case SDLK_a: return 0x7;
        case SDLK_s: return 0x8;
        case SDLK_d: return 0x9;
        case SDLK_f: return 0xE;

        case SDLK_z: return 0xA;
        case SDLK_x: return 0x0;
        case SDLK_c: return 0xB;
        case SDLK_v: return 0xF;
    }

    return -1;
};

void Input::processInputs(bool& CPUrunning, CHIP8_cpu& cpu)
{
    SDL_Event e;

    while(SDL_PollEvent(&e))
    {
        if(e.type == SDL_QUIT)// sdl quit 
        { 
            CPUrunning = false;
        }    

        if(e.type == SDL_KEYDOWN)// key down 
        {
            int key = mapKey(e.key.keysym.sym);
            if(key != -1){
                cpu.keys[key] = true;
            }
            
        }

        if(e.type == SDL_KEYUP)// key up 
        {
            int key = mapKey(e.key.keysym.sym);
            if(key != -1)
            {
                cpu.keys[key] = false;
            }
            
        }
    }
};