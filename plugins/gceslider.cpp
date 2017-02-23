
#include <guichan.hpp>
#include "gceslider.hpp"
#include "editorGui.hpp"

#include "tinyxml.h"


// this overload is specific to the editor and not needed in a "loader" plugin
void gceSlider::draw(gcn::Graphics* g)
{
    Slider::draw(g);

    if (currentWidget==this)
    {
        g->setColor(gcn::Color(255,0,0,128));        
        g->fillRectangle(gcn::Rectangle(0,0,12,12));
        int w=getWidth();
        int h=getHeight();
        g->fillRectangle(gcn::Rectangle(w-12,h-12,w,h));
    }
}




