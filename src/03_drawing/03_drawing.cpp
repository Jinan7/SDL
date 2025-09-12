#include <SDL2/SDL.h>
SDL_Window *window = NULL;
SDL_Surface *window_surface = NULL;
SDL_Surface *hello_world = NULL;
const int WINDOWHEIGHT = 480;
const int WINDOWWIDTH = 620;

bool init()
{
    bool res = true;
    if (SDL_Init( SDL_INIT_VIDEO) < 0)
    {
        printf("SDL Initialization failed SDL Error: %s\n", SDL_GetError());
    } else {
        window = SDL_CreateWindow("Drawing Images", SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,WINDOWWIDTH,WINDOWHEIGHT, SDL_WINDOW_SHOWN);

        if (window == NULL)
        {
            printf("%s\n", SDL_GetError());
            res = false;
        } else {
            window_surface = SDL_GetWindowSurface(window);
        }
    }

    return res;
}

bool load_media()
{
    bool res = true;
    hello_world = SDL_LoadBMP("hello_world.bmp");
    if (hello_world == NULL)
    {
        printf("%s\n", SDL_GetError());
        res = false;
    }


    return res;

}

void close()
{
    
    SDL_FreeSurface(hello_world);
    hello_world = NULL;

    SDL_DestroyWindow(window);
    window = NULL;

    SDL_Quit();

}

int main(int argc, char **argv)
{
    

    if (!init()) close();

    if (!load_media()) close();

    SDL_BlitSurface(hello_world, NULL, window_surface, NULL);
    SDL_UpdateWindowSurface(window);

    bool quit = false;
    SDL_Event e;
    while (quit == false)
    {
        while(SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT) quit = true;
        }
    }
    close();
    return 0;
}