#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

using namespace std;

const int WW=720;
const int WH=680;

const int UDF = SDL_WINDOWPOS_UNDEFINED;

SDL_Window *window = NULL;
SDL_Texture *w_texture = NULL;
SDL_Renderer *w_renderer = NULL;

void print_error()
{
    cout<<SDL_GetError()<<endl;
}
bool init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        print_error();
        return false;
    }

    window = SDL_CreateWindow("viewport", UDF, UDF, WW, WH, SDL_WINDOW_SHOWN);

    if (window == NULL)
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

    int imgflags = IMG_INIT_PNG;
    if(!(IMG_Init(imgflags) & imgflags))
    {
        print_error();
        return false;
    }

    return true;
}

SDL_Texture* loadTexture(string path)
{
    SDL_Surface *img_surface = IMG_Load(path.c_str());

    if (img_surface == NULL )
    {
        print_error();
        return NULL;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(w_renderer, img_surface);

    if (w_texture == NULL)
    {
        print_error();
    }

    SDL_FreeSurface(img_surface);

    return texture;
}

bool loadMedia()
{
    w_texture = loadTexture("viewport.png");

    if (w_texture==NULL)
    {
        return false;
    }

    return true;
}


bool close()
{
    SDL_DestroyWindow( window );
    window = NULL;
    SDL_DestroyTexture ( w_texture ); 
    w_texture = NULL;
    SDL_DestroyRenderer( w_renderer );
    w_renderer = NULL;
}
int main()
{

    //initialize sdl
    if (!init()) return close();

    //load media
    if (!loadMedia()) return close();

    //load media


    //create top left viewport rect
    SDL_Rect topleft_vp;
    topleft_vp.x = 0;
    topleft_vp.y = 0;
    topleft_vp.w = WW / 2;
    topleft_vp.h = WH / 2;

    //create top left viewport rect
    SDL_Rect topRight_vp;
    topRight_vp.x = WW/2;
    topRight_vp.y = 0;
    topRight_vp.w = WW / 2;
    topRight_vp.h = WH / 2;

    

    //create bottom viewport;
    SDL_Rect bottom_vp;
    bottom_vp.x = 0;
    bottom_vp.y = WH / 2;
    bottom_vp.w = WW;
    bottom_vp.h = WH / 2;


    //initialize variables
    SDL_Event e;
    bool quit = false;

    //game loop
    while (quit == false)
    {
        while(SDL_PollEvent(&e))
        {
            if (e.type==SDL_QUIT) 
            {
                quit = true;
            }

            
        }

        SDL_SetRenderDrawColor(w_renderer, 255,255,255,255);
        SDL_RenderClear(w_renderer);

        SDL_SetRenderDrawColor(w_renderer, 255, 0,0,255);

        SDL_RenderSetViewport(w_renderer, &topleft_vp);
        SDL_RenderCopy(w_renderer, w_texture, NULL, NULL);

        SDL_RenderSetViewport(w_renderer, &bottom_vp);
        SDL_RenderCopy(w_renderer, w_texture, NULL, NULL);

        SDL_RenderSetViewport(w_renderer, &topRight_vp);
        SDL_RenderCopy(w_renderer, w_texture, NULL, NULL);
        





        SDL_RenderPresent(w_renderer);
    }
    return 0;
}