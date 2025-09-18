#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <string>

using namespace std;
Mix_Music *g_music = NULL;

Mix_Chunk *g_high = NULL;
Mix_Chunk *g_scratch = NULL;
Mix_Chunk *g_medium = NULL;
Mix_Chunk *g_low = NULL;

SDL_Window *window = NULL;
SDL_Renderer *w_renderer = NULL;

bool init()
{
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0)
    {
        cout<<SDL_GetError()<<endl;
        return false;
    }

    window = SDL_CreateWindow("Sound", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 400,400,SDL_WINDOW_SHOWN);
    w_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    int res = Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    if (res < 0)
    {
        cout<<Mix_GetError()<<endl;
    }

    return true;
}

int close()
{
    

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(w_renderer);
    Mix_FreeChunk(g_high);
    Mix_FreeChunk(g_low);
    Mix_FreeChunk(g_medium);
    Mix_FreeChunk(g_scratch);
    Mix_FreeMusic(g_music);

    return 0;
}

int main(int argc, char **argv)
{

    init();
    g_music = Mix_LoadMUS("./beat.wav");
    g_high = Mix_LoadWAV("./high.wav");
    g_low = Mix_LoadWAV("./low.wav");
    g_medium = Mix_LoadWAV("./medium.wav");
    g_scratch = Mix_LoadWAV("./scratch.wav");

    bool quit = false;
    SDL_Event e;

    while (!quit)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }else if (e.type == SDL_KEYDOWN)
            {
                if (e.key.keysym.sym == SDLK_1)
                {
                    cout<<"1"<<endl;
                    Mix_PlayChannel(-1, g_high, 0);
                }
                if (e.key.keysym.sym == SDLK_2)
                {
                    cout<<"2"<<endl;
                    Mix_PlayChannel(-1, g_medium, 0);
                }
                if (e.key.keysym.sym == SDLK_3)
                {
                    cout<<"3"<<endl;
                    Mix_PlayChannel(-1, g_low, 0);
                }
                if (e.key.keysym.sym == SDLK_4)
                {
                    cout<<"4"<<endl;
                    Mix_PlayChannel(-1, g_scratch, 0);
                }

                if (e.key.keysym.sym == SDLK_9)
                {
                    if (!Mix_PlayingMusic())
                    {
                        Mix_PlayMusic(g_music, -1);
                    }else{
                        if (Mix_PausedMusic())
                        {
                            Mix_ResumeMusic();
                        } else {
                            Mix_PauseMusic();
                        }
                    }

                    
                }

                if (e.key.keysym.sym == SDLK_0)
                {
                    Mix_HaltMusic();
                }
            }
        }
    }

    return close();
}