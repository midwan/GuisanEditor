#include <guichan.hpp>
#include <typeinfo>
#include <gmodule.h>

#include "gcelistbox.hpp"
#include "editorGui.hpp"
#include "mouselistener.hpp"

#include "gcebase.hpp"

static gcn::Container *extendedProps;

static void doExtended()
{

}

class lbActionListener : public gcn::ActionListener
{
    void action(const gcn::ActionEvent& actionEvent);
};

static lbActionListener *lbListener;

void lbActionListener::action(const gcn::ActionEvent& actionEvent)
{
    if (actionEvent.getId() == "newListBox")
    {
        gceListBox *c=new gceListBox(&dummyLM);
        c->setPosition(16,16);
        c->setSize(100,24);
        //((gceBase*)c)->emptyMouseListeners();  DANGER WILL ROBINSON!
        c->removeMouseListener(c);
        c->addMouseListener(&MListener);   // all components must add editors global mouse listener
        top->add(c);
        currentWidget=c;
        doExtended();
        updateBaseProperties();
    }
    

}

extern "C" gcn::Widget *newInstance() // doesnt add to "top"
{
    gceListBox *c=new gceListBox(&dummyLM);
    //((gceBase*)c)->emptyMouseListeners();
    c->removeMouseListener(c);
    c->addMouseListener(&MListener);

    return c;
}

extern "C" gcn::Button *initComponent()
{
    extendedProps = new gcn::Container();
    extendedProps->setSize(SHEET_WIDTH,SHEET_HEIGHT);
        
    lbListener=new lbActionListener();
    gcn::Button *b=new gcn::Button("ListBox"); 
    b->adjustSize();
    b->setHeight(b->getHeight()-6);

    b->setActionEventId("newListBox");
    b->addActionListener(lbListener);
    
    extendedProps->setBaseColor(gcn::Color(255, 128, 128, 0));
    
    return b;
}

extern "C" gboolean canParent()
{
    return false;
}
        
extern "C" gboolean currentIsThisType()
{
    if (typeid(*currentWidget) == typeid(gceListBox))
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

const char lbName[]="gcn::ListBox";
extern "C" const char* componentName()
{
    return &lbName[0];
}
