#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <sstream>
#include <iostream>

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

class Texture
{
    public:

    Texture();

    ~Texture();

    bool loadFromFile(SDL_Renderer *renderer, string path);

    void free();

    bool render(int x, int y, SDL_Rect *src, SDL_Renderer *renderer);

    int get_width();
    
    int get_height();

    void set_width(int w);

    void set_height(int h);


    private:

    SDL_Texture *m_texture;
    int width;
    int height;

};

Window window = Window();
SDL_Renderer *w_renderer;
Texture w_texture = Texture();

bool init()
{
    window.init();
    w_renderer = window.createRenderer();
    int img_flags = IMG_INIT_PNG;

    if(!(IMG_Init(img_flags)&img_flags))
    {    
        return false;
    };

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
    bool res = w_texture.loadFromFile(w_renderer, "./window.png");
    cout<<res<<endl;

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
            w_texture.render((window.get_width()-w_texture.get_width())/2,(window.get_height()-w_texture.get_height())/2,NULL, w_renderer);
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
        m_width = WW;
        m_height = WH;
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
            //SDL_RenderPresent(renderer);
            break;

            case SDL_WINDOWEVENT_EXPOSED:
            //SDL_RenderPresent(renderer);
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

//initialize withd and height of texture to 0
Texture::Texture()
{
    this->width = 0;
    this->height = 0;
}

//release texture memory when destructing object
Texture::~Texture()
{
    this->free();
}

//function to release texture memory
void Texture::free()
{
    SDL_DestroyTexture(this->m_texture);
    this->m_texture = NULL;
}

bool Texture::loadFromFile(SDL_Renderer *renderer, string path)
{
    //load image file as surface
    SDL_Surface *img_surface = IMG_Load(path.c_str());

    //return error if img load failed
    if (img_surface == NULL )
    {
        
        return false;
    }

    //color key image surface
    SDL_SetColorKey(img_surface, SDL_TRUE, SDL_MapRGB(img_surface->format,0,255,255));

    //convert image surface to texture with desired renderer
    //free m_texture before assigning
    this->free();
    m_texture = SDL_CreateTextureFromSurface(renderer, img_surface);

    if (m_texture == NULL)
    {
        SDL_FreeSurface(img_surface);
        img_surface = NULL;
        return false;
    }

    //store height and width of image as height and width of texture
    this->set_height(img_surface->h);
    this->set_width(img_surface->w);

    //free img surface
    SDL_FreeSurface(img_surface);
    img_surface = NULL;
    
    return true;
}

bool Texture::render(int x, int y, SDL_Rect *src, SDL_Renderer *renderer)
{
    
    SDL_Rect dest;
    
    dest.x = x;
    dest.y = y;
    dest.w = this->width;
    dest.h = this->height;

    if (src != NULL) 
    {
        dest.w = src->w;
        dest.h = src->h;
    }
    SDL_SetRenderDrawColor(w_renderer, 0,0,0,255);
    SDL_RenderCopy(renderer, this->m_texture, src, &dest);

    return true;
}

//texture height getter
int Texture::get_height()
{
    return this->height;
}

//texture width getter
int Texture::get_width()
{
    return this->width;
}

//texture height setter
void Texture::set_width(int w)
{
    this->width = w;
}

//texture width setter
void Texture::set_height(int h)
{
    this->height = h;
}
