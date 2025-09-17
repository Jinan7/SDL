#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <iostream>
#include <vector>

using namespace std;


class Button
{

    public:
    //constructor
    Button();
    //destructor
    ~Button();
    //memory deallocator
    void free();
    //renderer
    void render(SDL_Renderer* renderer);
    //event handler
    void eventhandler(SDL_Event* event);

    void set_x(int x)
    {
        this->x = x;
    }

    void set_y(int y)
    {
        this->y = y;
    }

    private:
    //top coordinate
    int x;
    //bottom coordinate
    int y;
    //button color
    int r, g, b;
    

};

vector<Button> buttons(4, Button());
const int MW = 200;
const int MH = 60;
const int WW = 720;
const int WH = 560;
const int UDF = SDL_WINDOWPOS_UNDEFINED;
SDL_Window *window;
SDL_Renderer *w_renderer;

bool init()
{
    bool res = SDL_Init(SDL_INIT_VIDEO);

    if (res < 0)
    {
        cout<<SDL_GetError()<<endl;
        return false;
    }

    window = SDL_CreateWindow("Mouse Events", UDF, UDF, WW, WH, SDL_WINDOW_SHOWN);

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

    return true;
}

int close()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(w_renderer);
    window = NULL;
    w_renderer = NULL;

    return 0;
}
int main(int argc, char **argv)
{
    if (!init()) return close();

    SDL_Event e;
    bool quit = false;

    for(int i=0; i<4; i++)
    {
        buttons[i].set_x((WW / 2) - (MW / 2));
        buttons[i].set_y(i*(MH + 5) + 280);
    }

    while (!quit)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            } else if (e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP)
            {

                for(int i=0; i<4; i++)
                {
                    buttons[i].eventhandler(&e);
                }

            }
        }

        SDL_SetRenderDrawColor(w_renderer, 255,255,255,255);
        SDL_RenderClear(w_renderer);
        for(int i=0; i<4; i++)
        {
            buttons[i].render(w_renderer);
            
        }
        SDL_RenderPresent(w_renderer);
    }
    return close();
}

Button::Button()
{
    this->x =0;
    this->y =0;
    this->r =0;
    this->g =0;
    this->b =255;
}

Button::~Button()
{
    this->free();
}

void Button::eventhandler(SDL_Event *e)
{
    int x, y, x2, y2;
    SDL_GetMouseState(&x, &y);
    x2 = this->x + MW;
    y2 = this->y + MH;

    if ( x < this->x || x > x2 || y < this->y || y > y2)
    {
        this->r =0;
        this->g =0;
        this->b =255;
        return;
    }


    if (e->type == SDL_MOUSEBUTTONDOWN)
    {
        this->r = 255;
        this->g = 0;
        this->b = 0;
    } else if (e->type == SDL_MOUSEBUTTONUP)
    {
        this->r=0;
        this->g=0;
        this->b=255;
    } else if (e->type == SDL_MOUSEMOTION)
    {
        this->r=0;
        this->g=255;
        this->b=0;
    } 
}

void Button::render(SDL_Renderer *renderer)
{
    SDL_Rect dest = {this->x, this->y, MW, MH};
    SDL_SetRenderDrawColor(renderer, this->r, this->g,this->b, 255);
    SDL_RenderFillRect(renderer, &dest);
    
}

void Button::free()
{
    ;
}

