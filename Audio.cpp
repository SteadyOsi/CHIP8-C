#include "Audio.h"
#include <SDL2/SDL.h>
#include <cstdint>

static void audioCallback(void* userdata, Uint8* stream, int len)
{
    Audio* audio = (Audio*)userdata;

    static float phase = 0.0f;

    float frequency = 440.0f;
    float sampleRate = 44100.0f;

    int16_t* buffer = (int16_t*)stream;
    int samples = len / sizeof(int16_t);

    for(int i = 0; i < samples; i++)
    {
        if(audio->beep)
        {
            float value = (phase < 0.5f) ? 1.0f : -1.0f;
            buffer[i] = value * 3000;
        }
        else
        {
            buffer[i] = 0;
        }

        phase += frequency / sampleRate;
        if(phase >= 1.0f)
            phase -= 1.0f;
    }
}

void Audio::init()
{
    // SDL_Init(SDL_INIT_AUDIO);

    SDL_AudioSpec spec{};
    spec.freq = 44100;
    spec.format = AUDIO_S16SYS;
    spec.channels = 1;
    spec.samples = 1024;
    spec.callback = audioCallback;
    spec.userdata = this;   // IMPORTANT

    device = SDL_OpenAudioDevice(NULL, 0, &spec, NULL, 0);
    SDL_PauseAudioDevice(device, 0);
}

void Audio::setBeep(bool on)
{
    beep = on;
}

void Audio::shutdown()
{
    SDL_CloseAudioDevice(device);
    SDL_Quit();
}