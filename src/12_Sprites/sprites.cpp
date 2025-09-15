#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <iostream>

using namespace std;

//Define texture class

class Texture
{
    public:

    Texture();

    ~Texture();

    bool loadFromFile(SDL_Renderer *renderer, string path);

    void free();

    bool render(int x, int y, SDL_Rect *src, SDL_Renderer *renderer);

    int get_width();
    
    int get_height();

    void set_width(int w);

    void set_height(int h);


    private:

    SDL_Texture *m_texture;
    int width;
    int height;

};

SDL_Window *window;
SDL_Renderer *w_renderer;
SDL_Rect Clips[4];
Texture *w_texture = new Texture();

const int WW = 720;
const int WH = 620;
const int UDF = SDL_WINDOWPOS_UNDEFINED;

void print_error();

bool init();

bool loadMedia(Texture *texture, string path);

int close();

int main(int argc, char **argv)
{
    init();
    loadMedia(w_texture, "./dots.png");

    bool quit = false;
    SDL_Event e;
    while (quit == false)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
        }

        SDL_SetRenderDrawColor(w_renderer, 255, 255,255,255);
        SDL_RenderClear(w_renderer);

        w_texture->render(0, 0, &Clips[0], w_renderer);
        w_texture->render(WW-100, 0, &Clips[1], w_renderer);
        w_texture->render(0, WH-100, &Clips[2], w_renderer);
        w_texture->render(WW-100, WH-100, &Clips[3], w_renderer);
        SDL_RenderPresent(w_renderer);
    }

    close();
    
}

//app functions
//print error message
void print_error()
{
    cout<<SDL_GetError()<<endl;
}

//close
int close()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(w_renderer);
    free(w_texture);
    SDL_Quit();
    IMG_Quit();
    return 0;
}

//initialize SDL
bool init()
{
    //initialize sdl
    int res = SDL_Init(SDL_INIT_VIDEO);
    if (res < 0) 
    {
        print_error();
        return false;
    }
    //create window
    window = SDL_CreateWindow("Clip Rendering and Sprite Sheets", UDF, UDF, WW, WH, SDL_WINDOW_SHOWN);

    if (window == NULL )
    {
        print_error();
        return false;
    }

    //create renderer
    w_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (w_renderer == NULL)
    {
        print_error();
        return false;
    }

    //initialize sdl image
    int imgflags = IMG_INIT_PNG;

    res = IMG_Init(imgflags) & imgflags;
    if (!res)
    {
        print_error();
        return false;
    }

    return true;
}

bool loadMedia(Texture *texture, string path)
{

    bool res = texture->loadFromFile(w_renderer, path);

    if (!res)
    {
        print_error();
        return false;
    }

    //set top-left clip
    Clips[0].x = 0;
    Clips[0].y = 0;
    Clips[0].w = 100;
    Clips[0].h = 100;

    //set top-right clip
    Clips[1].x = 100;
    Clips[1].y = 0;
    Clips[1].w = 100;
    Clips[1].h = 100;

    //set bottom-left clip
    Clips[2].x = 0;
    Clips[2].y = 100;
    Clips[2].w = 100;
    Clips[2].h = 100;

    //set bottom-right clip
    Clips[3].x = 100;
    Clips[3].y = 100;
    Clips[3].w = 100;
    Clips[3].h = 100;

    return true;
}



//texture functions
//initialize withd and height of texture to 0
Texture::Texture()
{
    this->width = 0;
    this->height = 0;
}

//release texture memory when destructing object
Texture::~Texture()
{
    this->free();
}

//function to release texture memory
void Texture::free()
{
    SDL_DestroyTexture(this->m_texture);
    this->m_texture = NULL;
}

bool Texture::loadFromFile(SDL_Renderer *renderer, string path)
{
    //load image file as surface
    SDL_Surface *img_surface = IMG_Load(path.c_str());

    //return error if img load failed
    if (img_surface == NULL )
    {
        print_error();
        return false;
    }

    //convert image surface to texture with desired renderer
    //free m_texture before assigning
    this->free();
    m_texture = SDL_CreateTextureFromSurface(renderer, img_surface);

    if (m_texture == NULL)
    {
        SDL_FreeSurface(img_surface);
        img_surface = NULL;
        return false;
    }

    //store height and width of image as height and width of texture
    this->set_height(img_surface->h);
    this->set_width(img_surface->w);

    //free img surface
    SDL_FreeSurface(img_surface);
    img_surface = NULL;
    return true;
}

bool Texture::render(int x, int y, SDL_Rect *src, SDL_Renderer *renderer)
{
    if (src == NULL) return false;
    SDL_Rect dest;

    dest.x = x;
    dest.y = y;
    dest.w = src->w;
    dest.h = src->h;

    SDL_RenderCopy(renderer, this->m_texture, src, &dest);

    return true;
}

//texture height getter
int Texture::get_height()
{
    return this->height;
}

//texture width getter
int Texture::get_width()
{
    return this->width;
}

//texture height setter
void Texture::set_width(int w)
{
    this->width = width;
}

//texture width setter
void Texture::set_height(int h)
{
    this->height = height;
}