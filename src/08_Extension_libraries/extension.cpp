#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

using namespace std;

SDL_Window *window;
SDL_Surface *w_surface, *img_surface;
const int WWIDTH =720;
const int WHEIGHT=600;
const int UDF = SDL_WINDOWPOS_UNDEFINED;


bool init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("%s", SDL_GetError());
        return false;
    }

    window = SDL_CreateWindow("Extension libs", UDF, UDF, WWIDTH, WHEIGHT, SDL_WINDOW_SHOWN);

    if (window == NULL)
    {
        printf("%s", SDL_GetError());
        return false;
    }

    int imgFlags = IMG_INIT_PNG;

    if (!(IMG_Init(imgFlags) & IMG_INIT_PNG))
    {
        printf("%s", SDL_GetError());
        return false;
    }

    w_surface = SDL_GetWindowSurface(window);

    return true;


}

SDL_Surface* loadSurface(string path)
{
    SDL_Surface *optimized = NULL;

    img_surface = IMG_Load(path.c_str());

    if (img_surface == NULL )
    {
        printf("%s", SDL_GetError());
    }

    optimized = SDL_ConvertSurface(img_surface, w_surface->format, 0);

    if (optimized == NULL)
    {
        printf("%s", SDL_GetError());
        
    }

    SDL_FreeSurface(img_surface);
    return optimized;

}

int close()
{

}
int main(){
    return 0;
}