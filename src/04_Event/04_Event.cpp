#include <SDL2/SDL.h>


const int WINDOWWIDTH = 720;
const int WINDOWHEIGHT = 680;

SDL_Window *window;
SDL_Surface *window_surface;

bool init()
{
    
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("%s\n", SDL_GetError());
        return false;
    }
    window = SDL_CreateWindow("Event Driven Programming", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOWWIDTH, WINDOWHEIGHT, SDL_WINDOW_SHOWN);

    if (window == NULL )
    {
        printf("%s\n", SDL_GetError());
        return false;
    }
    window_surface = SDL_GetWindowSurface(window);

    return true;
}

bool create()
{
    ;
   
}

int quit()
{
    SDL_DestroyWindow(window);
    window = NULL;
    return 0;
}

int main(int argc, char * argv)
{

    if (!init())
    {
        return 0;
    }


    bool quit = false;
    SDL_Event e;
    while (quit == false)
    {
        while ( SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
        }

        // SDL_UpdateWindowSurface( window );
    }

    return 0;
}