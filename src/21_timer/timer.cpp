#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <SDL2/SDL_ttf.h>
#include <sstream>
using namespace std;

class Text
{
    public:
    Text();
    ~Text();
    void free();
    void render(SDL_Renderer* renderer, int x, int y);
    int loadText(SDL_Renderer *renderer, TTF_Font *font, string *text, const SDL_Color *color);
    int get_height();
    int get_width();
    void set_height();
    void set_width();


    private:

    SDL_Texture *mtexture;
    int width;
    int height;
};

const int WW=720;
const int WH=480;
const int UDF = SDL_WINDOWPOS_UNDEFINED;
SDL_Window *window;
SDL_Renderer *w_renderer;
TTF_Font *font;
Text test = Text();
Text header = Text();
string headertext = "Press Enter to reset start time";
string text = "nothing for now";
stringstream timeText;
SDL_Color color = {0,0,0,255};

int init()
{
    //cout<<"init begin"<<endl;
    if(SDL_Init(SDL_INIT_VIDEO)<0)
    {
        cout<<SDL_GetError()<<endl;
        return 0;
    }
    //cout<<"init stage 2"<<endl;
    window = SDL_CreateWindow("timer", UDF, UDF, WW, WH, SDL_WINDOW_SHOWN);

    if (window == NULL )
    {
        cout<<SDL_GetError()<<endl;
        return 0;
    }
    
    //cout<<"init state 3"<<endl;
    w_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (w_renderer == NULL )
    {
        cout<<SDL_GetError()<<endl;
        return 0;
    }
    //cout<<"init success"<<endl;

    if(TTF_Init()<0)
    {
        cout<<TTF_GetError()<<endl;
        return 0;
    }
    return 1;
}

int load_media()
{
    font = TTF_OpenFont("./lazy.ttf" , 28);
    
    header.loadText(w_renderer, font, &headertext, &color);
    return 1;
}

int close()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(w_renderer);
    TTF_CloseFont(font);
    window = NULL;
    w_renderer = NULL;

    return 0;
}
int main(int argc, char **argv)
{
    
    if (init()==0) return close();
    load_media();
    bool quit = false;
    SDL_Event e;
    Uint32 startTime = 0;
    test.loadText(w_renderer, font, &text, &color);
    while (!quit)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT){
                quit = true;
            }
            if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_r)
            {
                startTime = SDL_GetTicks();
            }
        }
        Uint32 elapsedTime = SDL_GetTicks() - startTime;
        timeText.str("");
        timeText<<"Milliseconds since start time "<<elapsedTime;
        SDL_SetRenderDrawColor(w_renderer, 255,255,255,255);
        SDL_RenderClear(w_renderer);
        text = timeText.str();
        test.loadText(w_renderer, font, &text, &color);
        test.render(w_renderer, (WW-test.get_width())/2,(WH-test.get_height())/2 );
        header.render(w_renderer, (WW-header.get_width())/2, 50 );
        SDL_RenderPresent(w_renderer);

    }


    return 0;
}

void Text::free()
{
    SDL_DestroyTexture(this->mtexture);
    this->mtexture = NULL;
}

Text::Text()
{
    this->width = 0;
    this->height = 0;
}

Text::~Text()
{
    this->free();   
}

int Text::loadText(SDL_Renderer *renderer, TTF_Font *font, string *text, const SDL_Color *color)
{
    SDL_Surface *text_surface = TTF_RenderText_Solid(font, text->c_str(),*color);

    if (text_surface == NULL)
    {
        cout<<TTF_GetError()<<endl;
        return 0;
    }

    //this line is very important because it almost caused my system to crash
    //always always always deallocate a pointer before reassigning it
    this->free();
    this->mtexture = SDL_CreateTextureFromSurface(renderer, text_surface);

    
    if (this->mtexture == NULL)
    {
        SDL_FreeSurface(text_surface);
        cout<<SDL_GetError()<<endl;
        return 0;
    }

    this->width = text_surface->w;
    this->height = text_surface->h;

    return 1;
}

void Text::render(SDL_Renderer *renderer, int x, int y)
{
    SDL_Rect dest = {x, y, this->width, this->height};
    SDL_RenderCopy(renderer, this->mtexture, NULL, &dest);
}

int Text::get_height()
{
    return this->height;
}

int Text::get_width()
{
    return this->width;
}