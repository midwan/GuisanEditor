
#include <guichan.hpp>

#include "gcedropdown.hpp"
#include "editorGui.hpp"

#include <iostream>

void gceDropDown::draw(gcn::Graphics* g)
{
    DropDown::draw(g);

    if (currentWidget==this)
    {
        g->setColor(gcn::Color(255,0,0,128));
        g->fillRectangle(gcn::Rectangle(0,0,12,12));
        int w=getWidth();
        int h=getHeight();
        g->fillRectangle(gcn::Rectangle(w-12,h-12,w,h));
    }
}

gceDropDown::gceDropDown(gcn::ListModel *lm,gcn::ScrollArea *sa,gcn::ListBox *lb) : gcn::DropDown(lm,sa,lb)
{
    
}

