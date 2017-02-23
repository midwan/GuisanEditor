
#include <guichan.hpp>
#include "gcelabel.hpp"
#include "editorGui.hpp"

#include "tinyxml.h"

void gceLabel::draw(gcn::Graphics* g)
{
    Label::draw(g);

    if (currentWidget==this)
    {
        g->setColor(gcn::Color(255,0,0,128));        
        g->fillRectangle(gcn::Rectangle(0,0,12,12));
        int w=getWidth();
        int h=getHeight();
        g->fillRectangle(gcn::Rectangle(w-12,h-12,w,h));
    }
}




