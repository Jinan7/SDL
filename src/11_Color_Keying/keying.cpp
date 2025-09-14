#include <SDL2/SDL.h>
#include <string>
#include <iostream>
#include <SDL2/SDL_image.h>


using namespace std;

class Texture {

    public:

    //constructor
    Texture(){
        m_texture = NULL;
        width = 0;
        height = 0;
    };

    //destructor
    ~Texture()
    {
        free();
    }

    //memory deallocator
    void free();

    void render(int x, int y);

    //load texture from file
    bool loadFromFile(string path, SDL_Renderer *renderer);
   
    //getters and setters
    void set_width(int width);

    void set_height(int height);

    int get_width();

    int get_height();
    

    private:
    SDL_Texture *m_texture;

    int width;
    int height;
};


const int WW = 720;
const int WH = 680;
const int UDF = SDL_WINDOWPOS_UNDEFINED;

SDL_Window *window;
Texture bg_texture;
Texture w_texture;
SDL_Renderer *w_renderer;

// Texture background;
// Texture foo;

void print_error()
{
    cout<<SDL_GetError()<<endl;
}

bool init()
{
    if (SDL_Init(SDL_INIT_VIDEO)<0)
    {
        print_error();
        return false;
    }

    window = SDL_CreateWindow("Color Keying", UDF, UDF, WW, WH, SDL_WINDOW_SHOWN);

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

    int imgflags = IMG_INIT_PNG;

    if (!(IMG_Init(imgflags)&imgflags))
    {
        print_error();
        return false;
    }

    return true;
}

SDL_Texture* loadTexture(string path)
{

    SDL_Surface *surface = IMG_Load(path.c_str());

    if (surface == NULL )
    {
        print_error();
        return NULL;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(w_renderer, surface);

    if (texture == NULL )
    {
        print_error();
    }

    SDL_FreeSurface(surface);
    surface = NULL;
    return texture;

}

bool loadMedia(Texture *texture, string path)
{

    if (!texture->loadFromFile(path, w_renderer)) return false;

    return true;
}

int close()
{
    SDL_DestroyWindow( window);
    SDL_DestroyRenderer(w_renderer);
    // SDL_DestroyTexture(w_texture);
    window = NULL;
    w_renderer = NULL;
    

    IMG_Quit();
    SDL_Quit();

    return 0;
}
int main(int argc, char **argv)
{

    //initialize sdl
    init();

    bg_texture = Texture();
    w_texture = Texture();
    //load media
    loadMedia(&bg_texture, "background.png");
    loadMedia(&w_texture, "foo.png");
    


    //game loop
    SDL_Event e;
    bool quit=false;

    while (quit == false)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
        }

        SDL_SetRenderDrawColor(w_renderer, 255,255,255,255);
        bg_texture.render(0,0);
        w_texture.render(30,30);
        SDL_RenderPresent(w_renderer);
    }

    
    return 0;
}




void Texture::free()
{
    SDL_DestroyTexture(this->m_texture);
    this->m_texture = NULL;
    this->width = 0;
    this->height = 0; 
}

void Texture::render(int x, int y)
{
    SDL_Rect renderQuad {x, y, this->width, this->height};
    
    SDL_RenderCopy(w_renderer, this->m_texture, NULL, &renderQuad);
}


bool Texture::loadFromFile(string path, SDL_Renderer *renderer)
{
    this->free();
    SDL_Surface *img_surface = IMG_Load(path.c_str());
    
    if (img_surface== NULL)
    {
        SDL_FreeSurface(img_surface);
        return false;
    }
    SDL_SetColorKey(img_surface, SDL_TRUE, SDL_MapRGB(img_surface->format, 0, 255,255));

    m_texture = SDL_CreateTextureFromSurface(renderer, img_surface);
    if (m_texture == NULL)
    {
        SDL_FreeSurface(img_surface);
        return false;
    }
    this->set_height(img_surface->h);
    this->set_width(img_surface->w);

    SDL_FreeSurface(img_surface);
    return true;
}
//getters and setters
void Texture::set_width(int width)
{
    this->width = width;
}

void Texture::set_height(int height)
{
    this->height = height;
}

int Texture::get_width()
{
    return this->width;
}

int Texture::get_height()
{
    return this->height;
}


