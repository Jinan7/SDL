#include <SDL2/SDL.h>


const int WINDOWWIDTH = 720;
const int WINDOWHEIGHT = 480;

SDL_Window * window;
SDL_Surface *w_surface;
SDL_Surface * img_surface;

bool init()
{
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("%s\n", SDL_GetError());
        return false;
    }

    window = SDL_CreateWindow("Soft Stretching", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOWWIDTH, WINDOWHEIGHT, SDL_WINDOW_SHOWN);

    if (window == NULL)
    {
        printf("%s\n", SDL_GetError());
        return false;
    }
    w_surface = SDL_GetWindowSurface( window );

    return true;
}

SDL_Surface * load_image(char *img_file)
{
    img_surface = SDL_LoadBMP(img_file);

    if (img_surface == NULL)
    {
        printf("%s\n", SDL_GetError());
        return NULL;
    }

    SDL_Surface * optimized = NULL; 

    optimized = SDL_ConvertSurface(img_surface, w_surface->format, 0);

    if (optimized == NULL)
    {
        printf("%s\n", SDL_GetError());
        
    }
    SDL_FreeSurface(img_surface);
    return optimized;
}

int close()
{
    SDL_DestroyWindow(window);
    window = NULL;
    SDL_FreeSurface(img_surface);
    img_surface = NULL;
    return 0;
}
int main(int argc, char * argv)
{
    
    if (!init())
    {
        return close();
    }

   img_surface = load_image("../../images/press.bmp");

    if (img_surface == NULL)
    {
        return close();
    }

    SDL_Event e;
    bool quit=false;

    while (quit == false)
    {
        while (SDL_PollEvent(&e) > 0)
        {
            if (e.type == SDL_QUIT)
            {
               quit=true;
            }
        }
        SDL_Rect stretchRect;
        stretchRect.x = 0;
        stretchRect.y = 0;
        stretchRect.w = WINDOWWIDTH;
        stretchRect.h = WINDOWHEIGHT;
        SDL_BlitScaled(img_surface, NULL, w_surface, &stretchRect);
        SDL_UpdateWindowSurface(window);
    }

    
    return close();
}