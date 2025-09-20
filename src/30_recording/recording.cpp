#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

class Text
{
    public:
    Text();
    ~Text();
    void free();
    bool load_text(SDL_Renderer* renderer, TTF_Font *font, string *text, SDL_Color *color);
    void render(SDL_Renderer *renderer, int x, int y);
    int get_width() {return this->width;}
    int get_height() {return this->height;}
    void set_width(int w) {this->width=w;}
    void set_height(int h) {this->height=h;}


    private:
    SDL_Texture *m_texture;
    int width;
    int height;
};
const int WW = 720;
const int WH = 480;
const int UDF = SDL_WINDOWPOS_UNDEFINED;
SDL_Window *window;
SDL_Renderer *w_renderer;

TTF_Font *font;



SDL_Color c = {0,0,0,255};
SDL_Color highlight = {255, 0,0,255};

Uint32 n_recording_devices;
string prompt = "Select your recording device ";
Text prompt_texture = Text();
stringstream audio_device_text;
Text audio_device_textures[10];


bool init()
{
    if (SDL_Init(SDL_INIT_VIDEO |SDL_INIT_AUDIO) < 0)
    {
        cout<<SDL_GetError()<<endl;
        return false;
    }

    window = SDL_CreateWindow("input", UDF, UDF, WW, WH, SDL_WINDOW_SHOWN);

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

    if (TTF_Init()<0)
    {
        cout<<SDL_GetError()<<endl;
        return false;
    }

    return true;

}

// bool load_data()
// {
//     SDL_RWops* file = SDL_RWFromFile("nums.bin", "r+b");

//     if (file==NULL)
//     {
//         cout<<SDL_GetError()<<endl;
//         file = SDL_RWFromFile("nums.bin", "w+b");

//         if (file == NULL)
//         {
//             cout<<SDL_GetError()<<endl;
//             return false;
//         }

//         cout<<"File created successfully"<<endl;

//         for (int i=0;i<10; i++)
//         {
//             userdata[i] = 0;
//             SDL_RWwrite(file, userdata + i, sizeof(userdata[i]), 1);
//         }
//     } else

//     {
//         for (int i = 0; i<10; i++)
//         {
//             Sint32 x;
//             SDL_RWread(file, &x, sizeof(x), 1);
//             userdata[i] = x;
//         }
//     }

//     return true;
// }

bool load_media()
{
    font = TTF_OpenFont("./playful.ttf", 28);

    if(font == NULL)
    {
        cout<<TTF_GetError()<<endl;
        return false;
    }

    n_recording_devices = SDL_GetNumAudioDevices(SDL_TRUE);
    return true;
}

// bool save_data()
// {
//     SDL_RWops* file = SDL_RWFromFile("nums.bin", "w+b");
//     for (int i=0;i<10; i++)
//     {
//         SDL_RWwrite(file, userdata + i, sizeof(userdata[i]), 1);
//     }

//     return true;
    
// }
int close()
{
    //save_data();
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(w_renderer);
    TTF_CloseFont(font);
    font = NULL;
    window = NULL;
    w_renderer = NULL;
    return 0;
}
int main(int argc, char ** argv)
{

    if (!init()) return close();
    load_media();
    prompt_texture.load_text(w_renderer,font, &prompt, &c);
   // audio_device_text.str("");
    bool quit = false;
    SDL_Event e;

    while (!quit)
    {
        while(SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
          
            
        }

        SDL_SetRenderDrawColor(w_renderer, 255,255,255,255);
        SDL_RenderClear(w_renderer);
        prompt_texture.render(w_renderer, 50,50);
        SDL_RenderPresent(w_renderer);
    }
    return close();
}

Text::Text()
{
    this->width = 0;
    this->height = 0;
    this->m_texture = NULL;
}

Text::~Text()
{
    this->free();
}

void Text::free()
{
    SDL_DestroyTexture(this->m_texture);
    this->m_texture = NULL;
    this->width = 0;
    this->height = 0;
    
}

bool Text::load_text(SDL_Renderer* renderer, TTF_Font *font, string *text, SDL_Color *color)
{
    SDL_Surface *text_surface;
    
    text_surface = TTF_RenderText_Solid(font, text->c_str(),*color);

    if (text_surface==NULL)
    {
        cout<<TTF_GetError()<<endl;
        return false;
    }

    this->free();
    this->m_texture = SDL_CreateTextureFromSurface(renderer, text_surface);

    if (this->m_texture == NULL)
    {
        SDL_FreeSurface(text_surface);
        text_surface = NULL;
        cout<<SDL_GetError()<<endl;
        return false;
    }

    this->set_width(text_surface->w);
    this->set_height(text_surface->h);
    SDL_FreeSurface(text_surface);
    text_surface=NULL;
    return true;
}

void Text::render(SDL_Renderer *renderer, int x, int y)
{
    SDL_Rect dest = {x, y, this->width, this->height};
    //SDL_SetRenderDrawColor(renderer, 0,0,0,255);
    SDL_RenderCopy(renderer, this->m_texture, NULL, &dest);
}