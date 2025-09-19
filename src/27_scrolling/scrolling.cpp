#include <SDL2/SDL.h>

class Box
{
    public:
    Box(float x, float y);
    void move();
    void handleEvent(SDL_Event* e);
    void render(SDL_Renderer *renderer, SDL_Rect *camera, SDL_Rect* dest, Box* ref);
    void set_height();
    void set_width();
    int get_height() {return this->height;};
    int get_width() {return this->width;};

    private:
    float x_pos;
    float y_pos;
    float x_vel;
    float y_vel;
    int width;
    int height;
    float VEL = 0.1;

};
SDL_Window *window;
SDL_Renderer *w_renderer;
const int WW = 720;
const int WH = 480;
const int UDF = SDL_WINDOWPOS_UNDEFINED;


bool init()
{
    if (SDL_Init(SDL_INIT_VIDEO)<0)
    {
        return false;
    }

    window = SDL_CreateWindow("Scrolling", UDF, UDF, WW, WH, SDL_WINDOW_SHOWN);

    w_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    return true;
}

int close()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(w_renderer);
    return 0;
}

int main()
{
    init();
    Box a = Box(10,10);
    SDL_Rect a_dest = {(WW-a.get_width())/2, (WH-a.get_height())/2, a.get_width(), a.get_height()};
    
    Box b = Box(70,40);
    
    SDL_Rect camera = {WW/2, WH/2, WW, WH};

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
            a.handleEvent(&e);
        }

        SDL_SetRenderDrawColor(w_renderer, 255,255,255,255);
        SDL_RenderClear(w_renderer);
        a.move();
    
        a.render(w_renderer, NULL, &a_dest, &a);
        b.render(w_renderer, NULL, NULL, &a);
        SDL_RenderPresent(w_renderer);
    }
    return close();
}

Box::Box(float x, float y)
{
    this->x_pos = x;
    this->y_pos = y;
    this->width = 50;
    this->height = 50;
    this->x_vel = 0;
    this->y_vel = 0;
}
void Box::handleEvent(SDL_Event* e)
{
    if (e->type == SDL_KEYDOWN && e->key.repeat == 0)
    {
        switch (e->key.keysym.sym)
        {
            case SDLK_UP:
                this->y_vel = -VEL;
                break;
            case SDLK_DOWN:
                this->y_vel = VEL;
                break;
            case SDLK_LEFT:
                this->x_vel = -VEL;
                break;
            case SDLK_RIGHT:
                this->x_vel = VEL;
                break;
        }
    }

    if (e->type == SDL_KEYUP && e->key.repeat == 0)
    {
        switch (e->key.keysym.sym)
        {
            case SDLK_UP:
                this->y_vel = 0;
                break;
            case SDLK_DOWN:
                this->y_vel =0;
                break;
            case SDLK_LEFT:
                this->x_vel = 0;
                break;
            case SDLK_RIGHT:
                this->x_vel =0;
                break;
        }
    }
}

void Box::move()
{
    this->x_pos += this->x_vel;
    this->y_pos += this->y_vel;
}

void Box::render(SDL_Renderer *renderer, SDL_Rect *camera, SDL_Rect *dest, Box* ref)
{
    SDL_Rect d = {this->x_pos-ref->x_pos, this->y_pos-ref->y_pos, this->width, this->height};
    if (dest == NULL)
    {
        dest = &d;
    }
    SDL_SetRenderDrawColor(renderer, 0,0,0,255);
    SDL_RenderFillRect(renderer, dest);
}