#include <SDL2/SDL.h>
#include <stdio.h>
#include <string.h>

const int WINDOWWIDTH = 720;
const int WINDOWHEIGHT = 480;

enum key_press_surfaces{
    KEYPRESSSURFACE_DEFAULT,
    KEYPRESSSURFACE_UP,
    KEYPRESSSURFACE_DOWN,
    KEYPRESSSURFACE_LEFT,
    KEYPRESSSURFACE_RIGHT,
    KEYPRESSSURFACE_TOTAL
};

SDL_Window *window;
SDL_Surface *w_surface;
SDL_Surface *current_surface;
SDL_Surface *key_press_surfaces[KEYPRESSSURFACE_TOTAL];



bool init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("%s\n", SDL_GetError());
        return false;
    }

    window = SDL_CreateWindow("Key Presses", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOWWIDTH, WINDOWHEIGHT, SDL_WINDOW_SHOWN);

    if (window == NULL)
    {
        printf("%s\n", SDL_GetError());
        return false;
    }

    w_surface = SDL_GetWindowSurface(window);

    return true;
}

SDL_Surface* loadSurface(char *path)
{
    SDL_Surface *image_surface;
    image_surface = SDL_LoadBMP(path);
    if (image_surface == NULL)
    {
        printf("%s\n", SDL_GetError());
    }
    return image_surface;
}

bool load_media()
{
    key_press_surfaces[KEYPRESSSURFACE_DEFAULT] = loadSurface("press.bmp"); 
    if (key_press_surfaces[KEYPRESSSURFACE_DEFAULT] == NULL) {
        printf("Error loading surface\n");
        return false;
    }
    key_press_surfaces[KEYPRESSSURFACE_UP] = loadSurface("up.bmp");
    if (key_press_surfaces[KEYPRESSSURFACE_UP] == NULL) {
        printf("Error loading surface\n");
        return false;
    }
    key_press_surfaces[KEYPRESSSURFACE_DOWN] = loadSurface("down.bmp");
    if (key_press_surfaces[KEYPRESSSURFACE_DOWN] == NULL) {
        printf("Error loading surface\n");
        return false;
    }
    key_press_surfaces[KEYPRESSSURFACE_LEFT] = loadSurface("left.bmp"); 
    if (key_press_surfaces[KEYPRESSSURFACE_LEFT] == NULL) {
        printf("Error loading surface\n");
        return false;
    }
    key_press_surfaces[KEYPRESSSURFACE_RIGHT] = loadSurface("right.bmp");  
    if (key_press_surfaces[KEYPRESSSURFACE_RIGHT] == NULL) {
        printf("Error loading surface\n");
        return false;
    }  
    
    return true;
}

int quit()
{
    SDL_DestroyWindow( window );
    window = NULL;

    SDL_FreeSurface(key_press_surfaces[KEYPRESSSURFACE_DEFAULT]);
    key_press_surfaces[KEYPRESSSURFACE_DEFAULT] = NULL;
    SDL_FreeSurface(key_press_surfaces[KEYPRESSSURFACE_UP]);
    key_press_surfaces[KEYPRESSSURFACE_UP] = NULL;
    SDL_FreeSurface(key_press_surfaces[KEYPRESSSURFACE_DOWN]);
    key_press_surfaces[KEYPRESSSURFACE_DOWN] = NULL;
    SDL_FreeSurface(key_press_surfaces[KEYPRESSSURFACE_LEFT]);
    key_press_surfaces[KEYPRESSSURFACE_LEFT] = NULL;
    SDL_FreeSurface(key_press_surfaces[KEYPRESSSURFACE_RIGHT]);
    key_press_surfaces[KEYPRESSSURFACE_RIGHT] = NULL;


    return 0;
}

int main(int argc, char *argv)
{

    if (!init()) return quit();
    if (!load_media()) return quit();

    bool e_quit=false;
    SDL_Event e;

    while (e_quit==false)
    {
        while(SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                return quit();
            }

            if (e.type == SDL_KEYDOWN)
            {
                switch(e.key.keysym.sym)
                {
                    case SDLK_UP:
                        current_surface = key_press_surfaces[KEYPRESSSURFACE_UP];
                        printf("Up button pressed\n");
                        break;
                    case SDLK_DOWN:
                        current_surface = key_press_surfaces[KEYPRESSSURFACE_DOWN];
                        printf("Down button pressed\n");
                        break;
                    case SDLK_LEFT:
                        current_surface = key_press_surfaces[KEYPRESSSURFACE_LEFT];
                        printf("Left button pressed\n");
                        break;
                    case SDLK_RIGHT:
                        current_surface = key_press_surfaces[KEYPRESSSURFACE_RIGHT];
                        printf("right button pressed\n");
                        break;
                    default:
                        current_surface = key_press_surfaces[KEYPRESSSURFACE_DEFAULT];
                        printf("Default button pressed\n");
                        break;
                }
            }
        }

        SDL_BlitSurface(current_surface, NULL, w_surface, NULL);
        SDL_UpdateWindowSurface( window );
    }
    return 0;
}