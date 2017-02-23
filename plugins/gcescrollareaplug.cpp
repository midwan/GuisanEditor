#include <guichan.hpp>
#include <typeinfo>
#include <gmodule.h>

#include "gcescrollarea.hpp"
#include "editorGui.hpp"
#include "mouselistener.hpp"

#include "gcebase.hpp"

static gcn::Container *extendedProps;


// TODO there is a problem with moving scroll areas that have a child

// TODO add scroll bar policy settings etc in extended properties sheet

static void doExtended()
{

}

class saActionListener : public gcn::ActionListener
{
    void action(const gcn::ActionEvent& actionEvent);
};

static saActionListener *saListener;

void saActionListener::action(const gcn::ActionEvent& actionEvent)
{
    if (actionEvent.getId() == "newScrollArea")
    {
        gceScrollArea *c=new gceScrollArea();
        c->setPosition(16,16);
        c->setSize(100,100);
//        ((gceBase*)c)->emptyMouseListeners();
        c->addMouseListener(&MListener);   // all components must add editors global mouse listener
        top->add(c);
        currentWidget=c;
        doExtended();
        updateBaseProperties();
    }
}

extern "C" gcn::Widget *newInstance() // doesnt add to "top" 
{
    gceScrollArea *c=new gceScrollArea();
//    ((gceBase*)c)->emptyMouseListeners();
    c->addMouseListener(&MListener);

    return c;
}

extern "C" gcn::Button *initComponent()
{
    extendedProps = new gcn::Container();
    extendedProps->setSize(SHEET_WIDTH,SHEET_HEIGHT);
        
    saListener=new saActionListener();
    gcn::Button *b=new gcn::Button("ScrollArea"); 
    b->adjustSize();
    b->setHeight(b->getHeight()-6);

    b->setActionEventId("newScrollArea");
    b->addActionListener(saListener);
    
    extendedProps->setBaseColor(gcn::Color(255, 128, 128, 0));
    
    return b;
}

extern "C" gboolean canParent()
{
    return true;
}
        
extern "C" gboolean currentIsThisType()
{
    if (typeid(*currentWidget) == typeid(gceScrollArea))
    {
        return true;
    } else {
        return false;
    }
}

extern "C" void updateExtendedProperties()
{
    if (oldExtendedProps!=extendedProps)
    {
        if (oldExtendedProps!=NULL) extended->remove(oldExtendedProps);
        extended->add(extendedProps,0,0);
    }  // every pluing must do this
    
    doExtended();
    
    oldExtendedProps=extendedProps;  // every plugin must do this
}

extern "C" void exportNodeExtended(TiXmlElement *node)
{
    
}

extern "C" void setExtendedFromNode(TiXmlElement *node)
{

}

const char scrollName[]="gcn::ScrollArea";
extern "C" const char* componentName()
{
    return &scrollName[0];
}
