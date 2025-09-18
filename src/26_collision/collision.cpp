#include <SDL2/SDL.h>

class Dot
{
  
    public:
    Dot(float x, float y);
    void handleEvent(SDL_Event *e);
    void render(SDL_Renderer* renderer);
    void move(Dot *b);
    bool hasCollided(Dot *b);
    float get_x()
    {
        return this->x_pos;
    }

    float get_y()
    {
        return this->y_pos;
    }

    int get_height()
    {
        return this->height;
    }

    int get_width()
    {
        return this->width;
    }

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

bool Dot::hasCollided(Dot *b)
{
    float a_top = this->get_y();
    float a_left = this->get_x();
    float a_right = this->get_x() + this->get_width();
    float a_bottom = this->get_y() + this->get_height();

    float b_top = b->get_y();
    float b_left = b->get_x();
    float b_right = b->get_x() + b->get_width();
    float b_bottom = b->get_y() + b->get_height();

    if (a_bottom < b_top) return false;
    if (a_top > b_bottom) return false;
    if (a_right < b_left) return false;
    if (a_left > b_right) return false;

    return true;
}
int main(int argc, char **argv)
{
    init();

    Dot dot = Dot(0,0);
    Dot dot2 = Dot(WW/2, WH/2);
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
        dot.move(&dot2);
        dot2.move(&dot);
        dot.render(w_renderer);
        dot2.render(w_renderer);
        
        SDL_RenderPresent(w_renderer);
    }
    return 0;
}



Dot::Dot(float x, float y)
{
    this->x_pos=x;
    this->y_pos=y;
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

void Dot::move(Dot *b)
{
    this->x_pos +=  this->x_vel;
    this->y_pos += this->y_vel;

    if (this->x_pos + this->width > WW || this->x_pos < 0 || this->hasCollided(b))
    {
        this->x_pos -=  this->x_vel;
    }

    if (this->y_pos + this->height > WH || this->y_pos < 0 || this->hasCollided(b))
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