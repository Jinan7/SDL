#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>

using namespace std;

//declare texture class
class Texture
{

    public:
    //constructor
    Texture();
    //Destructor
    ~Texture();
    //memory deallocator
    void free();
    //render function
    void render(SDL_Renderer *renderer, int x, int y, SDL_Rect *src);
    //create texture from img
    bool loadFromFile(SDL_Renderer * renderer, string path);
    //height getter
    int get_height();
    //height setter
    void set_height(int h);
    //width getter
    int get_width();
    //width setter
    void set_width(int w);

    //new function
    //set color modulation
    void set_color(int red, int green, int blue);

    private:

    //hardware texture
    SDL_Texture *m_texture;
    //width
    int width;
    //height
    int height;
};



//declare global variables
SDL_Window *window;
SDL_Renderer *w_renderer;
Texture *texture = new Texture();
const int UDF = SDL_WINDOWPOS_UNDEFINED;
const int WW = 720;
const int WH = 420;
void print_error();
int close();
bool init();
bool loadMedia(Texture *texture, string path);

int r = 255;
int g = 255;
int b = 255;

//declare global functions

int main()
{
    init();
    loadMedia(texture, "./colors.png");
    bool quit = false;
    SDL_Event e;

    while(quit==false)
    {
        while(SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            } else if (e.type == SDL_KEYDOWN)
            {
                switch(e.key.keysym.sym)
                {
                    case SDLK_q:
                        r += 32;
                        break;
                    case SDLK_w:
                        g += 32;
                        break;

                    case SDLK_e:
                        b += 32;
                        break;
                    
                    case SDLK_a:
                        r -= 32;
                        break;
                    case SDLK_s:
                        g -= 32;
                        break;

                    case SDLK_d:
                        b -= 32;
                        break;
        
                }
            }
        }

    
        SDL_SetRenderDrawColor(w_renderer,255,255,255,255);
        SDL_RenderClear(w_renderer);
        texture->render(w_renderer, 0, 0, NULL);
        texture->set_color(r, g, b);
        SDL_RenderPresent(w_renderer);
    }
}

//define global functions
void print_error()
{
    ;
}

//initialization
bool init()
{
    //initialize sdl
    int res = SDL_Init(SDL_INIT_VIDEO);
    //if error return false and print error
    if (res < 0)
    {
        print_error();
        return false;
    }
    //create window
    window = SDL_CreateWindow("modulation", UDF,UDF,WW,WH,SDL_WINDOW_SHOWN);

    //if error return false and print error
    if (window == NULL )
    {
        print_error();
        return false;
    }
    //create renderer
    w_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    //if error return false and print error
    if (w_renderer == NULL)
    {
        print_error();
        return false;
    }
    //initialize image
    int imgflags = IMG_INIT_PNG;
    res = IMG_Init(imgflags)&imgflags;

    //if error return false and print error
    if (!res)
    {
        print_error();
        return false;
    }

    //return true

    return true;
}

//close
int close()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(w_renderer);
    free(texture);
    SDL_Quit();
    IMG_Quit();

    return 0;
}

//load media
bool loadMedia(Texture *texture, string path)
{
    //call texture load media function
    bool res =texture->loadFromFile(w_renderer, path);

    if (res == false) return false;

    return true;
}
//define texture functions 
Texture::Texture()
{
    this->width = 0;
    this->height = 0;
}

Texture::~Texture()
{
    this->free();
    m_texture = NULL;
}

void Texture::free()
{
    SDL_DestroyTexture(this->m_texture);
    this->m_texture = NULL;
}

bool Texture::loadFromFile(SDL_Renderer *renderer, string path)
{
    //load image surface
    SDL_Surface *img_surface = IMG_Load(path.c_str());

    //return false if image load failed
    if (img_surface == NULL )
    {
        print_error();
        return false;
    }

    //create texture from image surface
    m_texture = SDL_CreateTextureFromSurface(renderer, img_surface);

    //deallocate image surface and return false if failed
    if (m_texture == NULL )
    {
        SDL_FreeSurface(img_surface);
        img_surface = NULL;
        print_error();
        return false;
    }

    //extract height and width from surface and store 
    this->set_height(img_surface->h);
    this->set_width(img_surface->w);

    //deallocate image surface and return true
    SDL_FreeSurface(img_surface);
    img_surface = NULL;
    return true;
}

void Texture::render(SDL_Renderer *renderer, int x, int y, SDL_Rect *src)
{
    SDL_Rect dest {x, y, this->width, this->height};

    if (src != NULL)
    {
        dest.w = src->w;
        dest.h = src->h;
    }

    SDL_RenderCopy(renderer, this->m_texture, src, &dest);
}

void Texture::set_color(int r, int b, int g)
{
    SDL_SetTextureColorMod(this->m_texture, r, b, g);
}

void Texture::set_height(int h)
{
    this->height = h;
}

void Texture::set_width(int w)
{
    this->width = w;
}