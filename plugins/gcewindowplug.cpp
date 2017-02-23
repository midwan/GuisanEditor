#include <guichan.hpp>
#include <typeinfo>
#include <gmodule.h>

#include "gcewindow.hpp"
#include "editorGui.hpp"
#include "mouselistener.hpp"

#include "gcebase.hpp"

static gcn::Container *extendedProps;
static gcn::TextField *captionEdit;

static void doExtended()
{
    captionEdit->setText(((gceWindow*)currentWidget)->getCaption());
}

class wActionListener : public gcn::ActionListener
{
    void action(const gcn::ActionEvent& actionEvent);
};

static wActionListener *wListener;

void wActionListener::action(const gcn::ActionEvent& actionEvent)
{
    if (actionEvent.getId() == "newWindow")
    {
        gceWindow *w=new gceWindow();
        w->setCaption("New Window");
        w->setPosition(16,16);
        w->setSize(100,100);
        ((gceBase*)w)->emptyMouseListeners();
        w->addMouseListener(&MListener);   // all components must add editors global mouse listener
        top->add(w);
        currentWidget=w;
        doExtended();
        updateBaseProperties();
    }
    
    if (actionEvent.getId() == "captionEdit") ((gceWindow*)currentWidget)->setCaption(captionEdit->getText());

}


extern "C" gcn::Button *initComponent()
{
    extendedProps = new gcn::Container();
    extendedProps->setSize(SHEET_WIDTH,SHEET_HEIGHT);
        
    wListener=new wActionListener();
    gcn::Button *w=new gcn::Button("Window"); 
    w->adjustSize();
    w->setHeight(w->getHeight()-6);

    w->setActionEventId("newWindow");
    w->addActionListener(wListener);
    
    captionEdit=new gcn::TextField();
    captionEdit->setSize(84,18);    
    captionEdit->setActionEventId("captionEdit");
    captionEdit->addActionListener(wListener);
    
    gcn::Label *tl=new gcn::Label("Caption");
    tl->setFont(labelFont);
    extendedProps->add(tl,8,0);

    extendedProps->add(captionEdit,8,14); 
    extendedProps->setBaseColor(gcn::Color(255, 128, 128, 0));
    
    return w;
}

extern "C" gboolean canParent()
{
    return true;
}
        
extern "C" gboolean currentIsThisType()
{
    if (typeid(*currentWidget) == typeid(gceWindow))
    {
        return true;
    } else {
        return false;
    }
}


extern "C" gcn::Widget *newInstance() // doesnt add to "top" 
{
    gceWindow *c=new gceWindow();
    ((gceBase*)c)->emptyMouseListeners();
    c->addMouseListener(&MListener);

    return c;
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
        node->SetAttribute("caption",((gcn::Window*)currentWidget)->getCaption().c_str());
}

extern "C" void setExtendedFromNode(TiXmlElement *node)
{
    ((gcn::Window*)currentWidget)->setCaption(node->Attribute("caption"));
}

const char windowName[]="gcn::Window";
extern "C" const char* componentName()
{
    return &windowName[0];
}
