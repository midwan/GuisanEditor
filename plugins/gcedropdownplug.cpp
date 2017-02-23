#include <guichan.hpp>
#include <typeinfo>
#include <gmodule.h>

#include "gcedropdown.hpp"
#include "editorGui.hpp"
#include "mouselistener.hpp"

#include "gcebase.hpp"



static gcn::Container *extendedProps;

static void doExtended()
{

}

class ddActionListener : public gcn::ActionListener
{
    void action(const gcn::ActionEvent& actionEvent);
};

static ddActionListener *ddListener;

void ddActionListener::action(const gcn::ActionEvent& actionEvent)
{
    if (actionEvent.getId() == "newDropDown")
    {
        gceDropDown *c=new gceDropDown(&dummyLM);
        c->setPosition(16,16);
        c->setSize(100,16);
        //((gceBase*)c)->emptyMouseListeners();  DANGER WILL ROBINSON!
        c->removeMouseListener(c);
        c->addMouseListener(&MListener);   // all components must add editors global mouse listener
        top->add(c);
        currentWidget=c;
        doExtended();
        updateBaseProperties();
    }
    

}

//extern "C" gceDropDown *newInstance() // why does this crash so strangly??
extern "C" gcn::Widget *newInstance() // doesnt add to "top" 
{
    gceDropDown *c=new gceDropDown(&dummyLM);
    
    
    //((gceBase*)c)->emptyMouseListeners();
    c->removeMouseListener(c);
    c->addMouseListener(&MListener);
    return c;
}

extern "C" gcn::Button *initComponent()
{
    extendedProps = new gcn::Container();
    extendedProps->setSize(SHEET_WIDTH,SHEET_HEIGHT);
        
    ddListener=new ddActionListener();
    gcn::Button *b=new gcn::Button("DropDown"); 
    b->adjustSize();
    b->setHeight(b->getHeight()-6);

    b->setActionEventId("newDropDown");
    b->addActionListener(ddListener);
    
    extendedProps->setBaseColor(gcn::Color(255, 128, 128, 0));
    
    return b;
}

extern "C" gboolean canParent()
{
    return false;
}

extern "C" gboolean currentIsThisType()
{
    if (typeid(*currentWidget) == typeid(gceDropDown))
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
    
//    doExtended();
    
    oldExtendedProps=extendedProps;  // every plugin must do this
}

extern "C" void exportNodeExtended(TiXmlElement *node)
{

}

extern "C" void setExtendedFromNode(TiXmlElement *node)
{

}

const char dropdownName[]="gcn::DropDown";
extern "C" const char* componentName()
{
    return &dropdownName[0];
}
