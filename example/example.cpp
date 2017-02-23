#include "SDL.h"

#include <guichan.hpp>
#include <guichan/sdl.hpp>
#include <iostream>
#include <gmodule.h>

#include "loader.hpp"

bool                    running = true;

SDL_Surface*            screen;
SDL_Event               event;

gcn::SDLInput*          input;
gcn::SDLGraphics*       graphics;
gcn::SDLImageLoader*    imageLoader;

gcn::Gui*               gui;
gcn::ImageFont*         font;

gcn::Container*         top;



class exampleActionListener : public gcn::ActionListener
{
    void action(const gcn::ActionEvent& actionEvent)
    {
        if (actionEvent.getId() == "quit")
        {
            running=false;
        }
    }
};

exampleActionListener *guiListener;

void init()  
{
    SDL_Init(SDL_INIT_VIDEO);
    screen = SDL_SetVideoMode(800, 600 , 32, SDL_SWSURFACE);
    SDL_EnableUNICODE(1);
    SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);
    imageLoader = new gcn::SDLImageLoader();
    gcn::Image::setImageLoader(imageLoader);
    graphics = new gcn::SDLGraphics();
    graphics->setTarget(screen);
    input = new gcn::SDLInput();

    gui = new gcn::Gui();
    gui->setGraphics(graphics);
    gui->setInput(input);

    font = new gcn::ImageFont("../fonts/font.png", " abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.,!?-+/():;%&`'*#=[]\"");
    gcn::Widget::setGlobalFont(font);
    
    initialisePlugs();


    gcn::Container* top=loadGui("output.xml");
    gui->setTop(top);

    guiListener=new exampleActionListener();
    
    gcn::Button *b1;

    b1=(gcn::Button*)top->findWidgetById("exitButton");
    if(b1!=NULL)
    {
        b1->addActionListener(guiListener);
    }

}

void halt()
{

    delete font;
    delete gui;

    delete top;

    delete input;
    delete graphics;
    delete imageLoader;

    free_all_plugins();

    SDL_Quit();
}

void checkInput()
{
    while(SDL_PollEvent(&event))
    {
        if (event.type == SDL_KEYDOWN)
        {
            if (event.key.keysym.sym == SDLK_ESCAPE)
            {
                running = false;
            }
            if (event.key.keysym.sym == SDLK_f)
            {
                if (event.key.keysym.mod & KMOD_CTRL)
                {
                    SDL_WM_ToggleFullScreen(screen);
                }
            }
        }
        else if(event.type == SDL_QUIT)
        {
            running = false;
        }
        input->pushInput(event);
    }
}

void run()
{
    while(running)
    {
        checkInput();
        gui->logic();

        gui->draw();
        SDL_Flip(screen);
        SDL_Delay(20);
    }
}

int main(int argc, char **argv)
{

    try
    {
        init();
        run();
        halt();
    }
    catch (gcn::Exception e)
    {
        std::cerr << e.getMessage() << std::endl;
        return 1;
    }

    return 0;
}

