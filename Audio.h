#include <SDL2/SDL.h>

class Audio {
public:
    void init();
    void shutdown();
    void setBeep(bool on);

    bool beep = false;

private:
    SDL_AudioDeviceID device;
};