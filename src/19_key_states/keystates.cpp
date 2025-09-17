#include <SDL2/SDL.h>


SDL_Window *window;
SDL_Renderer *w_renderer;

const int WW=720;
const int WH = 480;
const int UDF = SDL_WINDOWPOS_UNDEFINED;

bool init()
{
    bool res = SDL_Init(SDL_INIT_VIDEO);

    if (res < 0)
    {
        return false;
    }

    window = SDL_CreateWindow("key states", UDF, UDF, WW, WH, SDL_WINDOW_SHOWN);

    w_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    return true;
}

int close()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(w_renderer);

    return 0;
}


int main(int argc, char **argv)
{
    if (!init()) return close();

    SDL_Event e;
    bool quit = false;
    int r = 255;
    int g = 255;
    int b = 255;

    while(!quit)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }

            const Uint8* keystates = SDL_GetKeyboardState(NULL);

            if (keystates[SDL_SCANCODE_UP])
            {
                r= 255;
                g= 0;
                b=0;
            }else

            if (keystates[SDL_SCANCODE_DOWN])
            {
                r= 0;
                g= 0;
                b=255;
            }else

            if (keystates[SDL_SCANCODE_LEFT])
            {
                r= 0;
                g= 255;
                b=0;
            }else

            if (keystates[SDL_SCANCODE_RIGHT])
            {
                r= 255;
                g= 0;
                b=255;
            }else
            {
                r = 255;
                g = 255;
                b = 255;
            }
        }

        SDL_SetRenderDrawColor(w_renderer, r,g,b,255);
        SDL_RenderClear( w_renderer);
        SDL_RenderPresent(w_renderer);
    }


    return close();
}