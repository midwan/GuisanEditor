#include <guichan.hpp>
#include <typeinfo>
#include <gmodule.h>

#include "gcecontainer.hpp"
#include "editorGui.hpp"
#include "mouselistener.hpp"

#include "gcebase.hpp"

static gcn::Container *extendedProps;


static void doExtended()
{

}

class cActionListener : public gcn::ActionListener
{
    void action(const gcn::ActionEvent& actionEvent);
};

static cActionListener *cListener;

void cActionListener::action(const gcn::ActionEvent& actionEvent)
{
    if (actionEvent.getId() == "newContainer")
    {
        gceContainer *c=new gceContainer();
        c->setPosition(16,16);
        c->setSize(100,100);
        ((gceBase*)c)->emptyMouseListeners();
        c->addMouseListener(&MListener);   // all components must add editors global mouse listener
        top->add(c);
        currentWidget=c;
        doExtended();
        updateBaseProperties();
    }
    

}

extern "C" gcn::Widget *newInstance() // doesnt add to "top" 
{
    gceContainer *c=new gceContainer();
    ((gceBase*)c)->emptyMouseListeners();
    c->addMouseListener(&MListener);

    return c;
}

extern "C" gcn::Button *initComponent()
{
    extendedProps = new gcn::Container();
    extendedProps->setSize(SHEET_WIDTH,SHEET_HEIGHT);
        
    cListener=new cActionListener();
    gcn::Button *b=new gcn::Button("Container"); 
    b->adjustSize();
    b->setHeight(b->getHeight()-6);

    b->setActionEventId("newContainer");
    b->addActionListener(cListener);
    
    extendedProps->setBaseColor(gcn::Color(255, 128, 128, 0));
    
    return b;
}

extern "C" gboolean canParent()
{
    return true;
}
        
extern "C" gboolean currentIsThisType()
{
    if (typeid(*currentWidget) == typeid(gceContainer))
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

const char containerName[]="gcn::Container";
extern "C" const char* componentName()
{
    return &containerName[0];
}
