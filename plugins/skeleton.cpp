
#include <guichan.hpp>
#include "gceskeleton.hpp"
#include "editorGui.hpp"

#include "tinyxml.h"


// this overload is specific to the editor and not needed in a "loader" plugin
void gceSkeleton::draw(gcn::Graphics* g)
{

    // this should be whatever class you are extending not Widget
    Widget::draw(g);

    if (currentWidget==this)
    {
        g->setColor(gcn::Color(255,0,0,128));        
        g->fillRectangle(gcn::Rectangle(0,0,12,12));
        int w=getWidth();
        int h=getHeight();
        g->fillRectangle(gcn::Rectangle(w-12,h-12,w,h));
    }
}

// some widget may need other overloads to play nicely in the editorGui

// custom widget implementation could be put in here


