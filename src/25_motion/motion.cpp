#include <SDL2/SDL.h>

class Dot
{
  
    public:
    Dot();
    void handleEvent(SDL_Event *e);
    void render(SDL_Renderer* renderer);
    void move();


    private:

    float x_pos;
    float y_pos;
    float x_vel;
    float y_vel;
    
    static const int width = 50;
    static const int height = 50;
    float vel = 0.1;
};

SDL_Window *window;
SDL_Renderer *w_renderer;
const int WW = 720;
const int WH = 430;
const int UDF = SDL_WINDOWPOS_UNDEFINED;

bool init()
{
    if (SDL_Init(SDL_INIT_VIDEO)<0)
    {
        return false;
    }

    window = SDL_CreateWindow("motion", UDF,UDF, WW, WH, SDL_WINDOW_SHOWN);
    w_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    return true;
}

int close()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(w_renderer);
    return 0;
}
int main(int argc, char **argv)
{
    init();

    Dot dot = Dot();
    bool quit = false;
    SDL_Event e;


    while (quit==false)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type==SDL_QUIT)
            {
                quit = true;
            }
            dot.handleEvent(&e);
        }

        SDL_SetRenderDrawColor(w_renderer,255,255,255,255);
        SDL_RenderClear(w_renderer);
        dot.move();
        dot.render(w_renderer);
        SDL_RenderPresent(w_renderer);
    }
    return 0;
}

Dot::Dot()
{
    this->x_pos=0;
    this->y_pos=0;
    this->x_vel=0;
    this->y_vel=0;
}

void Dot::handleEvent(SDL_Event *e)
{

    if (e->type == SDL_KEYDOWN && e->key.repeat == 0)
    {
        if (e->key.keysym.sym == SDLK_UP)
        {
            y_vel-=vel;
        } else
        if (e->key.keysym.sym == SDLK_DOWN)
        {
            y_vel+=vel;
        } else
        if (e->key.keysym.sym == SDLK_LEFT)
        {
            x_vel-=vel;
        } else
        if (e->key.keysym.sym == SDLK_RIGHT)
        {
            x_vel+=vel;
        }
    } else

    if (e->type == SDL_KEYUP && e->key.repeat == 0)
    {
        if (e->key.keysym.sym == SDLK_UP)
        {
            y_vel+=vel;
        } else
        if (e->key.keysym.sym == SDLK_DOWN)
        {
            y_vel-=vel;
        } else
        if (e->key.keysym.sym == SDLK_LEFT)
        {
            x_vel+=vel;
        } else
        if (e->key.keysym.sym == SDLK_RIGHT)
        {
            x_vel-=vel;
        }
    }
}

void Dot::move()
{
    this->x_pos +=  this->x_vel;
    this->y_pos += this->y_vel;

    if (this->x_pos + this->width > WW || this->x_pos < 0)
    {
        this->x_pos -=  this->x_vel;
    }

    if (this->y_pos + this->height > WH || this->y_pos < 0)
    {
        this->y_pos -=  this->y_vel;
    }
}
void Dot::render(SDL_Renderer *renderer)
{
    SDL_Rect dest {this->x_pos, this->y_pos, this->width, this->height};
    SDL_SetRenderDrawColor(renderer, 0,0,0,255);
    SDL_RenderFillRect(renderer, &dest);
}