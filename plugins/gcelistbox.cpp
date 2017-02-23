
#include <guichan.hpp>

#include "gcelistbox.hpp"
#include "editorGui.hpp"


void gceListBox::draw(gcn::Graphics* g)
{
    ListBox::draw(g);

    if (currentWidget==this)
    {
        g->setColor(gcn::Color(255,0,0,128));
        g->fillRectangle(gcn::Rectangle(0,0,12,12));
        int w=getWidth();
        int h=getHeight();
        g->fillRectangle(gcn::Rectangle(w-12,h-12,w,h));
    }
}


gceListBox::gceListBox(gcn::ListModel *lm) : gcn::ListBox(lm)
{

}
