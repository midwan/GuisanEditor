#ifndef GCE_GUI_HPP
#define GCE_GUI_HPP

#include <guichan.hpp>
#include <guichan/sdl.hpp>
#include "gceColourSelector.hpp"
#include "dummyListModel.hpp"

extern "C" void updateBaseProperties(); // plugins call this on instance creation
extern "C" gcn::Image* loadImage(const char* s);

extern gcn::Widget*     currentWidget;
extern gcn::Container*  top;
extern gcn::Gui*        gui;

extern gcn::Window*     mainWindow;

extern gcn::Container*  oldExtendedProps;
extern gcn::Container*  extended;
extern gcn::Container*  global;
extern gcn::Container*  standard;
extern gcn::Container*  components;
extern gcn::Container*  lastSelected;

extern gcn::ImageFont*  labelFont;  

extern gcn::DropDown*   sheetSelector;

extern gcn::SDLImageLoader* imageLoader;
//std property widgets
extern gcn::Slider*        borderSize;
extern gcn::Label*         borderSizeLabel;
extern gceColourSelector*  baseColour;
extern gcn::Label*         baseColourLabel;
extern gceColourSelector*  backgroundColour;
extern gcn::Label*         backgroundColourLabel;
extern gceColourSelector*  foregroundColour;
extern gcn::Label*         foregroundColourLabel;
extern gceColourSelector*  selectionColour;
extern gcn::Label*         selectionColourLabel;
extern gcn::TextField*     actionEventId;
extern gcn::Label*         actionEventIdLabel;
extern gcn::TextField*     widgetId;
extern gcn::Label*         widgetIdLabel;

extern gcn::Button*        parent;
extern gcn::Button*        parentTop;
extern gcn::Button*        del;

extern int                 timesClicked;

extern std::vector<gcn::Widget*> widgetsToDelete;

extern DummyListModel dummyLM;

#define SHEET_WIDTH 160
#define SHEET_HEIGHT 320

#endif

