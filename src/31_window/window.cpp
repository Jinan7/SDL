#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <sstream>

using namespace std;
const int WW = 720;
const int WH = 600;


class Window
{

    public:

    //constructor
    Window();
    //initialize window
    bool init();
    //createwindowRenderer
    SDL_Renderer* createRenderer();
    //handle window events
    void handleEvent(SDL_Event& e, SDL_Renderer *renderer);
    //deallocate memory
    void free();

    //getters and setters
    int get_height();
    int get_width();
    void set_height(int h);
    void set_width(int w);
    bool has_mouse_focus();
    bool has_keyboard_focus();
    bool is_minimized();



    private:

    SDL_Window* window;
    int m_height;
    int m_width;

    bool m_mouse_focus;
    bool m_keyboard_focus;
    bool m_fullscreen;
    bool m_minimized;

};

Window window = Window();
SDL_Renderer *w_renderer;

bool init()
{
    window.init();
    w_renderer = window.createRenderer();

    return true;
}

void close()
{
    SDL_DestroyRenderer(w_renderer);
    window.free();
    SDL_Quit();
}
int main()
{

    init();
    SDL_Event e;
    bool quit = false;

    while(!quit)
    {
        while(SDL_PollEvent(&e))
        {
            if(e.type == SDL_QUIT)
            {
                quit = true;
            }
            window.handleEvent(e, w_renderer);
        }


        if (!window.is_minimized())
        {
            SDL_SetRenderDrawColor(w_renderer, 0,0,0,255);
            SDL_RenderClear(w_renderer);
            SDL_RenderPresent(w_renderer);
        }
    }
    return 0;
}

Window::Window()
{
    this->window = NULL;
    this->m_height = 0;
    this->m_width = 0;
    this->m_mouse_focus = false;
    this->m_fullscreen = false;
    this->m_minimized = false;
    this->m_keyboard_focus = false;
}
void Window::free()
{
    SDL_DestroyWindow(this->window);
}


bool Window::init()
{
    this->window = SDL_CreateWindow("window events", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WW, WH, SDL_WINDOW_SHOWN |SDL_WINDOW_RESIZABLE);

    if (window != NULL)
    {
        m_mouse_focus = true;
        m_keyboard_focus = true;
        m_width = true;
        m_height = true;
        return true;
    }

    return false;
}

SDL_Renderer* Window::createRenderer()
{
    SDL_Renderer* renderer;
    renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED |SDL_RENDERER_PRESENTVSYNC);
    return renderer;
}

void Window::handleEvent(SDL_Event &e, SDL_Renderer* renderer)
{
    if (e.type == SDL_WINDOWEVENT)
    {
        bool updateCaption = false;

        switch (e.window.event)
        {
            case SDL_WINDOWEVENT_SIZE_CHANGED:
            this->m_height = e.window.data2;
            this->m_width = e.window.data1;
            SDL_RenderPresent(renderer);
            break;

            case SDL_WINDOWEVENT_EXPOSED:
            SDL_RenderPresent(renderer);
            break;

            case SDL_WINDOWEVENT_ENTER:
            m_mouse_focus = true;
            updateCaption = true;
            break;

            case SDL_WINDOWEVENT_LEAVE:
            m_mouse_focus = false;
            updateCaption = true;
            break;

            case SDL_WINDOWEVENT_FOCUS_GAINED:
            m_keyboard_focus = true;
            updateCaption = true;

            case SDL_WINDOWEVENT_FOCUS_LOST:
            m_keyboard_focus = false;
            updateCaption = true;
            break;

            case SDL_WINDOWEVENT_MINIMIZED:
            m_minimized = true;
            break;

            case SDL_WINDOWEVENT_MAXIMIZED:
            m_minimized = false;
            break;
        }


        if (updateCaption)
        {
            stringstream caption;
            caption <<"MouseFocus "<< (m_mouse_focus ? "on " : "off ")<<"KeyboardFocus "<<(m_keyboard_focus? "on " : "off ");
            SDL_SetWindowTitle(this->window, caption.str().c_str());
        }
    } else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN)
    {
        if (m_fullscreen)
        {
            SDL_SetWindowFullscreen(window, 0);
            m_fullscreen = false;
        } else{
            SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
            m_fullscreen = true;
            m_minimized = false;
        }
    }
}

int Window::get_height()
{
    return this->m_height;
}

int Window::get_width()
{
    return this->m_width;
}

void Window::set_height(int h)
{
    this->m_height = h;
}

void Window::set_width(int w)
{
    this->m_width = w;
}

bool Window::has_mouse_focus()
{
    return this->m_mouse_focus;
}

bool Window::has_keyboard_focus()
{
    return this->m_keyboard_focus;
}

bool Window::is_minimized()
{
    return this->m_minimized;
}
