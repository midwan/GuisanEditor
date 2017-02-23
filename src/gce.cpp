
#include <iostream>
#include <guichan.hpp>
#include <guichan/sdl.hpp>
#include "SDL.h"
#include <glib.h>
#include <gmodule.h>
#include <vector>

#include "mouselistener.hpp"
#include "plugin.hpp"

#include "gceStringList.hpp"
#include "actionlistener.hpp"


//#include "gcecontainer.hpp"

#include "gceColourSelector.hpp"

#include "dummyListModel.hpp"

Plugin::~Plugin() 
{
	if (!g_module_close (mModule))
		std::cout << "couldn't close plugin " << std::endl;
}

Plugin::Plugin(const char *PluginName) 
{
    mError=false;
    mModule=g_module_open(PluginName, G_MODULE_BIND_LAZY);
	if (!mModule)
	{
		std::cout << "couldn't open plugin " << PluginName << "  error: " << g_module_error() << std::endl;
	    mError=true;
	} 
	else 
	{
        // TODO issue warning for a specific function when bailing
    	if ( !g_module_symbol (mModule, "initComponent", (gpointer *)&mInitComponent) ||
            !g_module_symbol (mModule, "currentIsThisType", (gpointer *)&mCurrentIsThisType) ||
            !g_module_symbol (mModule, "updateExtendedProperties", (gpointer *)&mUpdateExtendedProperties) ||
            !g_module_symbol (mModule, "componentName", (gpointer *)&mComponentName) ||
            !g_module_symbol (mModule, "canParent", (gpointer *)&mCanParent) ||
            !g_module_symbol (mModule, "newInstance", (gpointer *)&mNewInstance) ||
            !g_module_symbol (mModule, "exportNodeExtended", (gpointer *)&mExportNodeExtended) ||
            !g_module_symbol (mModule, "setExtendedFromNode", (gpointer *)&mSetExtendedFromNode)
           )
        {
    		std::cout << "couldn't find a function " << std::endl;
    		
    	    if (!g_module_close (mModule))
    			std::cout << "couldn't close plugin " << std::endl;
    	    mError=true;
    	}
    	else
    	{
        	if (mInitComponent == NULL ||
        	    mCurrentIsThisType == NULL ||
        	    mUpdateExtendedProperties == NULL )
        	{
        		std::cout << "null function pointer " << std::endl;

        	    if (!g_module_close (mModule))
        			std::cout << "couldn't close plugin " << std::endl;
        	    mError=true;
        	}  //endif function null
    	} //endelse function found
	} //endelse cant open module
}
    


GList *Plugins;



bool running = true;

SDL_Surface* screen;
SDL_Event event;

gcn::SDLInput*      input;               // Input driver
gcn::SDLGraphics*   graphics;         // Graphics driver
gcn::SDLImageLoader* imageLoader;   // For loading images

gcn::Gui*           gui;                      // A Gui object - binds it all together
gcn::ImageFont*     font;               // A font
gcn::ImageFont*     labelFont;


//gcn::Container*
//gceContainer*     top;                // A top container
gcn::Container*     top;

gcn::Window*        mainWindow;
gcn::Container*     global;
gcn::Container*     components;
gcn::Container*     extended;
gcn::Container*     standard;
gcn::Container*     oldExtendedProps;       // last plugin child of extended
gcn::Container*     lastSelected;
gcn::Widget*        currentWidget;          // current/last widget being edited

gcn::DropDown*      sheetSelector;          
gceStringList*      sl;

//std property widgets
gcn::Slider*        borderSize;
gcn::Label*         borderSizeLabel;
gceColourSelector*  baseColour;
gcn::Label*         baseColourLabel;
gceColourSelector*  backgroundColour;
gcn::Label*         backgroundColourLabel;
gceColourSelector*  foregroundColour;
gcn::Label*         foregroundColourLabel;
gceColourSelector*  selectionColour;
gcn::Label*         selectionColourLabel;
gcn::TextField*     actionEventId;
gcn::Label*         actionEventIdLabel;
gcn::TextField*     widgetId;
gcn::Label*         widgetIdLabel;

gcn::Button*        toFront;
gcn::Button*        toBack;
gcn::Button*        parent;
gcn::Button*        parentTop;
gcn::Button*        del;


std::vector<gcn::Widget*> widgetsToDelete;  //glib glist candidate??

DummyListModel dummyLM;

void initWidgets()  
{
    
    oldExtendedProps=NULL;
    
    mainWindow = new gcn::Window("GCe");
    mainWindow->setBaseColor(gcn::Color(0, 64, 128, 128));
    mainWindow->setSize(160,480);
    top->add(mainWindow, 800-176, 16);
    
    standard=new gcn::Container();
    standard->setBaseColor(gcn::Color(0, 64, 128, 0));
    standard->setSize(160,480-32);

    extended=new gcn::Container();
    extended->setBaseColor(gcn::Color(0, 64, 128, 0));
    extended->setSize(160,480-32);    
        
    global=new gcn::Container();
    global->setBaseColor(gcn::Color(0, 64, 128, 0));
    global->setSize(160,480-32);    

    components=new gcn::Container();
    components->setBaseColor(gcn::Color(0, 64, 128, 0));
    components->setSize(160,480-32);
    
    sl=new gceStringList();
    sl->addString("Global");
    sl->addString("Components");
    sl->addString("Properties");
    sl->addString("Extra Props");

    sheetSelector=new gcn::DropDown(sl);
    sheetSelector->setWidth(160-16);
    sheetSelector->setActionEventId("sheetSelector");
    sheetSelector->addActionListener(&guiListener);
    mainWindow->add(sheetSelector,8,8);

    mainWindow->add(global, 0, 32);
    lastSelected=global;

    
    gcn::Button *save=new gcn::Button("Save");
    global->add(save,8,0);
    save->addActionListener(&guiListener);
    save->setActionEventId("save");
    
    gcn::Button *load=new gcn::Button("Load");
    global->add(load,8,30);
    load->addActionListener(&guiListener);
    load->setActionEventId("load");
    
    del=new gcn::Button("Delete Widget");
    global->add(del,8,60);
    del->addActionListener(&guiListener);
    del->setActionEventId("delete");

    parent=new gcn::Button("Parent");
    parent->addActionListener(&guiListener);
    parent->setActionEventId("parent");
    parentTop=new gcn::Button("Parent top");
    parentTop->addActionListener(&guiListener);
    parentTop->setActionEventId("parentTop");

    toBack=new gcn::Button("To back ");
    toFront=new gcn::Button("To front");
    toBack->addActionListener(&guiListener);
    toBack->setActionEventId("toBack");
    toFront->addActionListener(&guiListener);
    toFront->setActionEventId("toFront");

    global->add(toBack,8,90);
    global->add(toFront,8,120);
    global->add(parent,8,150);
    global->add(parentTop,8,180);



    // "standard" property sheet
    borderSize=new gcn::Slider(32);
    borderSize->setSize(100, 10);
    borderSize->setActionEventId("borderSize");
    borderSize->addActionListener(&guiListener);
    borderSizeLabel=new gcn::Label("Border Size");
    borderSizeLabel->setFont(labelFont);
    
    baseColour=new gceColourSelector();
    baseColour->addActionListener(&guiListener);
    baseColour->mActionId="baseColour";  // can you say kludge!
    baseColourLabel=new gcn::Label("Base Colour");
    baseColourLabel->setFont(labelFont);
    
    backgroundColour=new gceColourSelector();
    backgroundColour->addActionListener(&guiListener);
    backgroundColour->mActionId="backgroundColour";
    backgroundColourLabel=new gcn::Label("Background Colour");
    backgroundColourLabel->setFont(labelFont);
    
    foregroundColour=new gceColourSelector();
    foregroundColour->addActionListener(&guiListener);
    foregroundColour->mActionId="foregroundColour";
    foregroundColourLabel=new gcn::Label("Foreground Colour");
    foregroundColourLabel->setFont(labelFont);
    
    selectionColour=new gceColourSelector();
    selectionColour->addActionListener(&guiListener);
    selectionColour->mActionId="selectionColour";
    selectionColourLabel=new gcn::Label("Selection Colour");
    selectionColourLabel->setFont(labelFont);

    actionEventId=new gcn::TextField("############");
    actionEventId->adjustSize();
    actionEventId->setText("");
    actionEventId->addActionListener(&guiListener);
    actionEventId->setActionEventId("actionEventId");
    actionEventIdLabel=new gcn::Label("Action Event Id");
    actionEventIdLabel->setFont(labelFont);
    
    widgetId=new gcn::TextField("############");
    widgetId->adjustSize();
    widgetId->setText("");
    widgetId->addActionListener(&guiListener);
    widgetId->setActionEventId("widgetId");
    widgetIdLabel=new gcn::Label("Widget id");
    widgetIdLabel->setFont(labelFont);
    

    
    standard->add(borderSizeLabel,8,0);
    standard->add(borderSize,8,15);
    standard->add(baseColourLabel,38,32);
    standard->add(baseColour,8,32);    
    standard->add(backgroundColourLabel,38,62);
    standard->add(backgroundColour,8,62);
    standard->add(foregroundColourLabel,38,92);
    standard->add(foregroundColour,8,92);
    standard->add(selectionColourLabel,38,122);
    standard->add(selectionColour,8,122);
    standard->add(actionEventIdLabel,8,152);
    standard->add(actionEventId,8,166);
    standard->add(widgetIdLabel,8,182);
    standard->add(widgetId,8,196);


    
    
    
    // search for and load plugins (it creates widgets so do it here)
    GDir *dir=g_dir_open(PLUG_DIR,0,NULL);
    const gchar *file;
    int py=8;
    while ( (file=g_dir_read_name(dir))!=NULL )
    {
        if ( g_str_has_suffix(file,".plug") )
        {
            //std::cout << std::endl << "attempting to load " << file << std::endl;
            gchar *full=g_strconcat (PLUG_DIR,file,NULL);   
            Plugin *plug=new Plugin(full);
            delete full;
            if (plug->mError) 
            {
                std::cout << file << " aborted" << std::endl;
            } else {
                Plugins=g_list_append(Plugins,plug);
                gcn::Button *b=plug->mInitComponent();
                components->add(b,8,py); 
                std::cout << plug->mComponentName() << " component loaded. " << std::endl;
                py=py+4+b->getHeight();
            }
        }
    }    

}

void free_all_plugins()
{
    GList *nlist;
	nlist=g_list_first(Plugins);
	do 
	{
	    Plugin *plug=(Plugin*)nlist->data;
        delete plug;
	} while ( (nlist=g_list_next(nlist))!=NULL );
	g_list_free(Plugins);
}

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

//    top = new gceContainer();
    top = new gcn::Container();  
    top->setDimension(gcn::Rectangle(0, 0, 800, 600));
    gui = new gcn::Gui();
    gui->setGraphics(graphics);
    gui->setInput(input);
    gui->setTop(top);
    font = new gcn::ImageFont("fonts/font.png", " abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.,!?-+/():;%&`'*#=[]\"");
    gcn::Widget::setGlobalFont(font);
    labelFont = new gcn::ImageFont("fonts/tiny.png", " abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.,!?-+/():;%&`'*#=[]\"");

    
    initWidgets();
}

extern "C" void updateBaseProperties()
{
    // set base property widgets
    char s[256];
    int i=currentWidget->getFrameSize();
    sprintf(s,"Border Size : %i",i);
    borderSizeLabel->setCaption(s);
    borderSize->setValue(i);
    
    baseColour->setSelectedColour(currentWidget->getBaseColor());
    backgroundColour->setSelectedColour(currentWidget->getBackgroundColor());
    foregroundColour->setSelectedColour(currentWidget->getForegroundColor());
    selectionColour->setSelectedColour(currentWidget->getSelectionColor());
    actionEventId->setText(currentWidget->getActionEventId());
    widgetId->setText(currentWidget->getId());
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



// rest of file boiler plate app framework code
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

int timesClicked;

void run()
{
    while(running)
    {
        checkInput();
        gui->logic();
        
        timesClicked=0;
        if (!widgetsToDelete.empty())
        {
          std::cout << "processing widgets to delete with " << widgetsToDelete.size() << " item(s) " << std::endl;
          for (unsigned int i=0; i < widgetsToDelete.size(); i++)
          {
              delete widgetsToDelete[i];
          }
          widgetsToDelete.clear();
        }
        
        gui->draw();
        SDL_Flip(screen);
        SDL_Delay(100);
    }
}

/*
#include <windows.h>

int WINAPI WinMain (HINSTANCE, HINSTANCE, LPSTR, int) {

  main(0,NULL);
  return 0;

}
*/

int main(int argc, char **argv)
{
/*
    try
    {
*/
        init();
        run();
        halt();
/*
    }
    catch (gcn::Exception e)
    {
        std::cerr << e.getMessage() << std::endl;
        return 1;
    }

    catch (std::exception e)
    {
        std::cerr << "Std exception: " << e.what() << std::endl;
        return 1;
    }
    catch (...)
    {
        std::cerr << "Unknown exception" << std::endl;
        return 1;
    }
*/
    return 0;
}


