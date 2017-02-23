#include <guichan.hpp>
#include <typeinfo>
#include <gmodule.h>

#include "gceicon.hpp"


#include "gcecontainer.hpp"



#include "editorGui.hpp"
#include "mouselistener.hpp"

#include "gcebase.hpp"
#include "guichan/image.hpp"

#include <iostream>

// TODO is it worth creating a global list of shared images
// that auto deletes on zero references?


static gcn::Container *extendedProps;
static gcn::TextField *fileNameEdit;

static void idoExtended()
{
    fileNameEdit->setText(((gceIcon*)currentWidget)->getFileName());

}

class iActionListener : public gcn::ActionListener
{
    void action(const gcn::ActionEvent& actionEvent);
};

static iActionListener *iListener;

void iActionListener::action(const gcn::ActionEvent& actionEvent)
{
    if (actionEvent.getId() == "newIcon")
    {   
        
        gcn::Image *i=gcn::Image::load("images/broken.bmp");
        gceIcon *c=(gceIcon*) new gceIcon(i); 

        c->setPosition(16,16);
        c->setSize(32,32);
        ((gceBase*)c)->emptyMouseListeners();
        c->addMouseListener(&MListener);   // all components must add editors global mouse listener
        top->add(c);
        currentWidget=c;
        idoExtended();
        updateBaseProperties();
    }

    if (actionEvent.getId() == "fileNameEdit")   ((gceIcon*)currentWidget)->setIconImage(fileNameEdit->getText().c_str());


}

extern "C" gcn::Widget *newInstance() // doesnt add to "top" 
{
    gcn::Image *i=gcn::Image::load("images/broken.bmp");
    gceIcon *c=new gceIcon(i); 
    
    ((gceBase*)c)->emptyMouseListeners();
    c->addMouseListener(&MListener);

    return c;
}

extern "C" gcn::Button *initComponent()
{
    extendedProps = new gcn::Container();
    extendedProps->setSize(SHEET_WIDTH,SHEET_HEIGHT);
        
    iListener=new iActionListener();
    gcn::Button *b=new gcn::Button("Icon"); 
    b->adjustSize();
    b->setHeight(b->getHeight()-6);

    b->setActionEventId("newIcon");
    b->addActionListener(iListener);
    
    extendedProps->setBaseColor(gcn::Color(255, 128, 128, 0));
    
    fileNameEdit=new gcn::TextField();
    fileNameEdit->setSize(84,18);
    fileNameEdit->setActionEventId("fileNameEdit");
    fileNameEdit->addActionListener(iListener);

    extendedProps->add(fileNameEdit,8,8);
    
    return b;
}

extern "C" gboolean canParent()
{
    return false;   // getting this wrong will crash editor on save or delete
}
        
extern "C" gboolean currentIsThisType()
{
    if (typeid(*currentWidget) == typeid(gceIcon))
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
    
    idoExtended();
    
    oldExtendedProps=extendedProps;  // every plugin must do this
}

extern "C" void exportNodeExtended(TiXmlElement *node)
{
    node->SetAttribute("imageFileName",((gceIcon*)currentWidget)->getFileName());
    
}

extern "C" void setExtendedFromNode(TiXmlElement *node)
{
    const char *str=(const char *)node->Attribute("imageFileName");
    ((gceIcon*)currentWidget)->setIconImage(str);

}

const char containerName[]="gcn::Icon";
extern "C" const char* componentName()
{
    return &containerName[0];
}
