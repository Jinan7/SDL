#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <iostream>

using namespace std;

class Texture
{
    public:
    Texture();
    ~Texture();
    void free();
    void render(SDL_Renderer* renderer);
    bool load_text_surface(SDL_Renderer* renderer, TTF_Font *font, string *text, SDL_Color color);
    int get_width();
    int get_height();
    void set_width();
    void set_height();



    private:
    SDL_Texture *texture;
    int width;
    int height;
};

SDL_Window *window;
SDL_Renderer *w_renderer;
TTF_Font *w_font;
Texture w_texture = Texture();
string text = "The quick brown fox jumped over the lazy dog";
string file_path = "./lazy.ttf";

bool init()
{
    int res = SDL_Init(SDL_INIT_VIDEO);

    if (res < 0)
    {
        cout<<SDL_GetError()<<endl;
        return false;
    }

    window = SDL_CreateWindow("TTF", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,720,480, SDL_WINDOW_SHOWN);

    if (window == NULL)
    {
        cout<<SDL_GetError()<<endl;
        return false;
    }

    w_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (w_renderer == NULL)
    {
        cout<<SDL_GetError()<<endl;
        return false;
    }

    res = TTF_Init();

    if (res == -1)
    {
        cout<<TTF_GetError()<<endl;
        return false;
    }

    return true;
}

int close()
{
    TTF_CloseFont(w_font);
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(w_renderer);
    w_texture.free();
    TTF_Quit();
    SDL_Quit();
    IMG_Quit();
    return 0;
}

bool load_media(Texture *texture, string *font_path)
{
    w_font = TTF_OpenFont(font_path->c_str(), 50);

    if (w_font == NULL )
    {
        cout<<TTF_GetError()<<endl;
        return false;
    }
    SDL_Color c {0,255,0};
    texture->load_text_surface(w_renderer, w_font, &text, c);
    return true;
}

int main(int argc, char **argv)
{
    if (!init()) return close();
    if (!load_media(&w_texture, &file_path)) return close();

    bool quit = false;
    SDL_Event e;


    while (!quit)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
        }

        SDL_SetRenderDrawColor(w_renderer, 255,255,255,255);
        SDL_RenderClear(w_renderer);
        w_texture.render(w_renderer);
        SDL_RenderPresent(w_renderer);
    }
    return 0;
}

bool Texture::load_text_surface(SDL_Renderer* renderer, TTF_Font *font, string *text,  SDL_Color color)
{
    SDL_Surface *text_surface;
    
    text_surface = TTF_RenderText_Solid(font, text->c_str(), color);

    if (text_surface == NULL)
    {
        cout<<TTF_GetError()<<endl;
        return false;
    }

    this->texture = SDL_CreateTextureFromSurface(renderer, text_surface);

    if (this->texture == NULL)
    {
        cout<<SDL_GetError()<<endl;
        SDL_FreeSurface(text_surface);
        return false;
    }

    this->height = text_surface->h;
    this->width = text_surface->w;
    SDL_FreeSurface(text_surface);
    text_surface = NULL;
    return true;
}

void Texture::render(SDL_Renderer* renderer)
{
    SDL_Rect dest = {0,0,this->width, this->height};
    SDL_RenderCopy(renderer, this->texture, NULL, &dest);
}

void Texture::free()
{
    SDL_DestroyTexture(this->texture);
    this->texture = NULL;
}

Texture::Texture()
{
    this->width = 0;
    this->height = 0;
}

Texture::~Texture()
{
    this->free();
}