#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

using namespace std;
const int WW = 720;
const int WH = 600;
const int UDF = SDL_WINDOWPOS_UNDEFINED;

SDL_Window * window;
SDL_Surface *w_surface, *img_surface;
SDL_Renderer *w_renderer;
SDL_Texture *texture;

void print_error()
{
    printf("%s", SDL_GetError());
}

bool init()
{

    if(SDL_Init(SDL_INIT_VIDEO)<0)
    {
        print_error();
        return false;
    }

    window = SDL_CreateWindow("Textures", UDF, UDF,WW, WH, SDL_WINDOW_SHOWN);

    if (window == NULL )
    {
        print_error();
        return false;
    }

    w_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (w_renderer == NULL )
    {
        print_error();
        return false;
    }

    SDL_SetRenderDrawColor(w_renderer, 0xFF, 0xFF, 0xFF, 0xFF);

    int img_flags = IMG_INIT_PNG;

    if(!(IMG_Init(img_flags)&img_flags))
    {
        print_error();
        return false;
    };

    return true;

}

int close()
{
    SDL_DestroyWindow( window );
    window = NULL;

    SDL_DestroyRenderer(w_renderer);
    w_renderer = NULL;

    SDL_DestroyTexture(texture);
    texture = NULL;
    SDL_FreeSurface(img_surface);
    img_surface = NULL;

    IMG_Quit();
    SDL_Quit();

    return 0;

}

SDL_Texture* loadTexture(string path)
{
    img_surface = IMG_Load(path.c_str());

    if (img_surface == NULL)
    {
        print_error();
    }

    texture = SDL_CreateTextureFromSurface(w_renderer, img_surface);

    if (texture == NULL){
        print_error();
    }
    SDL_FreeSurface(img_surface);
    return texture;
}

bool loadMedia()
{
    texture = loadTexture("./texture.png");
    if (texture == NULL)
    {
        print_error();
        return false;
    }
    return true;
}
int main(int argc, char *argv)
{
    init();
    loadMedia();
    bool quit = false;
    SDL_Event e;

    while (quit == false)
    {
        while (SDL_PollEvent(&e)>0)
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
        }

        SDL_RenderClear(w_renderer);
        SDL_RenderCopy(w_renderer, texture, NULL, NULL);
        SDL_RenderPresent( w_renderer);

    }


    return close();
}