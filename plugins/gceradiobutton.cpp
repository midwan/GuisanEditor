
#include <guichan.hpp>
#include "gceradiobutton.hpp"
#include "editorGui.hpp"

#include "tinyxml.h"

// this is standard code all editor widgets should overload draw exactly like this
void gceRadioButton::draw(gcn::Graphics* g)
{
    RadioButton::draw(g);

    if (currentWidget==this)
    {
        g->setColor(gcn::Color(255,0,0,128));        
        g->fillRectangle(gcn::Rectangle(0,0,12,12));
        int w=getWidth();
        int h=getHeight();
        g->fillRectangle(gcn::Rectangle(w-12,h-12,w,h));
    }
}




