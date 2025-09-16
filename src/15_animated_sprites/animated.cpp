#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

//create texture class
class Texture
{
    public:
    Texture();
    ~Texture();
    void free();
    void render(SDL_Renderer* renderer, int x, int y, SDL_Rect *src);
    bool load_from_file(SDL_Renderer* renderer, string path);
    void set_color(int r, int g, int b);
    void set_blendmode(SDL_BlendMode blend);
    void set_alpha(int a);
    void set_height(int h);
    void set_width(int w);
    int get_height();
    int get_width();




    private:
    SDL_Texture* mtexture;
    int width;
    int height;
};


//create global variables
SDL_Window *window;
SDL_Renderer *w_renderer;
Texture w_texture = Texture();



const int WW = 720;
const int WH = 720;
const int UDF = SDL_WINDOWPOS_UNDEFINED;


//create main functions
void print_error();
bool init();
bool load_media(Texture *texture, string path);
int close();

int alpha = 255;
int main(int argc, char **argv)
{
    
    if (!init()) return close();
    load_media(&w_texture, "./foo.png");
    bool quit = false;
    SDL_Event e;
    SDL_Rect sprite{0,0,64,205};
    int sprite_idx = 0;
    int frame = 0;

    while (!quit)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            } else if (e.type == SDL_KEYDOWN)
            {

                if (e.key.keysym.sym == SDLK_a)
                {
                    alpha = min(255, alpha + 32);
                }

                if (e.key.keysym.sym == SDLK_s)
                {
                    alpha = max(0, alpha - 32);
                }
            }
        }
        sprite.x = sprite.w * sprite_idx;
        SDL_SetRenderDrawColor(w_renderer, 255,255,255, 255);
        SDL_RenderClear(w_renderer);
        w_texture.render(w_renderer, 0, 0, &sprite);
        SDL_RenderPresent(w_renderer);
        frame +=1;
        sprite_idx  = frame / 10;
        sprite_idx %= 4;

    }
}

//define main functions
//error logger
void print_error()
{
    cout<<SDL_GetError()<<endl;
}
//Initialization
bool init()
{
    //initialize sdl
    int res = SDL_Init(SDL_INIT_VIDEO);
    //check if initialization successful
    if (res < 0)
    {
        print_error();
        return false;
    }
    //create window
    window = SDL_CreateWindow("Alpha blending", UDF, UDF, WW, WH, SDL_WINDOW_SHOWN);
    //check if window creation successful
    if (window == NULL )
    {
        print_error();
        return false;
    }
    //create renderer
    w_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    //check if renderer creation successful
    if (w_renderer==NULL)
    {
        print_error();
        return false;
    }
    //initialize image
    int img_flags = IMG_INIT_PNG;
    res = IMG_Init(img_flags)&img_flags;
    //check if window creation successful
    if(!res)
    {
        print_error();
        return false;
    }

    //return true
    return true;
}

//load media
bool load_media(Texture *texture, string path)
{
    bool res = texture->load_from_file(w_renderer, path);
    if (!res) return false;  
    
    return true;
}
//close application
int close()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(w_renderer);
    SDL_Quit();
    IMG_Quit();
    return 0;
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
}

void Texture::set_height(int h)
{
    this->height = h;
}

void Texture::set_width(int w)
{
    this->width = w;
}

void Texture::free()
{
    SDL_DestroyTexture(mtexture);
    mtexture = NULL;
}

void Texture::render(SDL_Renderer *renderer, int x, int y, SDL_Rect *src = NULL)
{

    SDL_Rect dest {x, y, this->width, this->height};

    if (src != NULL)
    {
        dest.w = src->w;
        dest.h = src->h;
    }

    SDL_RenderCopy(renderer, this->mtexture, src, &dest);
}

void Texture::set_color(int r, int g, int b)
{
    SDL_SetTextureColorMod(this->mtexture, r, g, b);
}

void Texture::set_blendmode(SDL_BlendMode blend)
{
    SDL_SetTextureBlendMode(this->mtexture, blend);

}

void Texture::set_alpha(int a)
{
    SDL_SetTextureAlphaMod(this->mtexture, a);

}
bool Texture::load_from_file(SDL_Renderer* renderer, string path)
{
    //create image surface
    SDL_Surface *img_surface = IMG_Load(path.c_str());
    //check if successful
    if (img_surface == NULL )
    {
        print_error();
        return false;
    }

    //create texture from surface
    this->mtexture = SDL_CreateTextureFromSurface(renderer, img_surface);
    //check if successful
    if (this->mtexture==NULL)
    {
        print_error();
        //release img_surfaceif not successful
        SDL_FreeSurface(img_surface);
        return false;
    }

    //extract height and width from surface
    this->set_height(img_surface->h);
    this->set_width(img_surface->w);




    //destroy image surface
    SDL_FreeSurface(img_surface);
    img_surface = NULL;
    //return true
    return true;
}