#include <SDL2/SDL.h>
#include <iostream>

using namespace std;
SDL_Window *window;
SDL_Renderer *w_renderer;
SDL_Texture *w_texture;

const int UDF = SDL_WINDOWPOS_UNDEFINED;
const int WW = 720;
const int WH = 680;

void print_error()
{
    printf("%s", SDL_GetError());
}
bool init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        print_error();
        return false;
    }

    window = SDL_CreateWindow("Geometry", UDF, UDF, WW, WH, SDL_WINDOW_SHOWN );

    if (window == NULL )
    {
        print_error();
        return false;
    }

    w_renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED);

    if (w_renderer == NULL )
    {
        print_error();
        return false;
    }
    return true;
}

int close()
{
    SDL_DestroyRenderer(w_renderer);
    w_renderer = NULL;
    SDL_DestroyTexture(w_texture);
    w_texture = NULL;
    SDL_DestroyWindow(window);
    window = NULL;

    return 0;
}
int main(int argc, char **argv)
{
    if (!init()) return close();

    SDL_Event e;
    bool quit=false;


    while(quit==false)
    {
        while(SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
        }

        SDL_SetRenderDrawColor(w_renderer, 255,255,255, 255);
        SDL_RenderClear(w_renderer);

        SDL_Rect fillRect{WW/4,WH/4,WW/2,WH/2};
        SDL_SetRenderDrawColor(w_renderer, 255, 0,0,0);
        SDL_RenderFillRect(w_renderer, &fillRect);
        

        SDL_Rect outlineRect{WW/6,WH/6, WW *2 /3, WH*2/3}; 
        SDL_SetRenderDrawColor(w_renderer, 0,255,0,255);
        SDL_RenderDrawRect(w_renderer, &outlineRect);
        SDL_RenderPresent(w_renderer);
    }
    return 0;
}