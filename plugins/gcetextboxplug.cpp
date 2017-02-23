#include <guichan.hpp>
#include <typeinfo>
#include <gmodule.h>

#include "gcetextbox.hpp"
#include "editorGui.hpp"
#include "mouselistener.hpp"

#include "gcebase.hpp"

static gcn::Container *extendedProps;


static void doExtended()
{

}

class tbActionListener : public gcn::ActionListener
{
    void action(const gcn::ActionEvent& actionEvent);
};

static tbActionListener *tbListener;

void tbActionListener::action(const gcn::ActionEvent& actionEvent)
{
    if (actionEvent.getId() == "newTextBox")
    {
        gceTextBox *c=new gceTextBox();
//        c->setText("********");
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
    gceTextBox *c=new gceTextBox();
//    c->setText("********");
    //((gceBase*)c)->emptyMouseListeners();
    c->addMouseListener(&MListener);

    return c;
}

extern "C" gcn::Button *initComponent()
{
    extendedProps = new gcn::Container();
    extendedProps->setSize(SHEET_WIDTH,SHEET_HEIGHT);
        
    tbListener=new tbActionListener();
    gcn::Button *b=new gcn::Button("TextBox"); 
    b->adjustSize();
    b->setHeight(b->getHeight()-6);

    b->setActionEventId("newTextBox");
    b->addActionListener(tbListener);
    
    extendedProps->setBaseColor(gcn::Color(255, 128, 128, 0));
    
    return b;
}

extern "C" gboolean canParent()
{
    return false;
}
        
extern "C" gboolean currentIsThisType()
{
    if (typeid(*currentWidget) == typeid(gceTextBox))
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

// TODO implement content lines as individual xml children
extern "C" void exportNodeExtended(TiXmlElement *node)
{
    
}

extern "C" void setExtendedFromNode(TiXmlElement *node)
{

}

const char tbName[]="gcn::TextBox";
extern "C" const char* componentName()
{
    return &tbName[0];
}
