#include <guichan.hpp>
#include <typeinfo>
#include <gmodule.h>

#include "gcetextfield.hpp"
#include "editorGui.hpp"
#include "mouselistener.hpp"
#include "gcebase.hpp"

#include <iostream>

static gcn::Container *extendedProps;
static gcn::TextField *textEdit;

static void doExtended()
{
    // actually update the caption text field
    textEdit->setText(((gcn::TextField*)currentWidget)->getText());
}

class tfActionListener : public gcn::ActionListener
{
    void action(const gcn::ActionEvent& actionEvent);
};

static tfActionListener *tfListener;

void tfActionListener::action(const gcn::ActionEvent& actionEvent)
{
    if (actionEvent.getId() == "newTfield")
    {
        gceTextField *t=new gceTextField();
        t->setText("********");
        t->adjustSize();
        t->setText("");
        t->setPosition(16,16);
        ((gceBase*)t)->emptyMouseListeners();
        t->addMouseListener(&MListener);   // all components must add editors global mouse listener
        top->add(t);
        currentWidget=t;
        doExtended();
        updateBaseProperties();
    }
    
    if (actionEvent.getId() == "textEdit") ((gceTextField*)currentWidget)->setText(textEdit->getText());

}


extern "C" gcn::Button *initComponent()
{
    extendedProps = new gcn::Container();
    extendedProps->setSize(SHEET_WIDTH,SHEET_HEIGHT);
        
    tfListener=new tfActionListener();
    gcn::Button *t=new gcn::Button("TextField");
    t->adjustSize();
    t->setHeight(t->getHeight()-6);
    t->setActionEventId("newTfield");
    t->addActionListener(tfListener);
    
    textEdit=new gcn::TextField();
    textEdit->setSize(84,18);    
    textEdit->setActionEventId("textEdit");
    textEdit->addActionListener(tfListener);
    
    gcn::Label *tl=new gcn::Label("Text");
    tl->setFont(labelFont);
    extendedProps->add(tl,8,0);

    extendedProps->add(textEdit,8,14); 
    extendedProps->setBaseColor(gcn::Color(255, 128, 128, 0));
    
    return t;
}

extern "C" gboolean canParent()
{
    return false;
}
        
extern "C" gboolean currentIsThisType()
{
    if (typeid(*currentWidget) == typeid(gceTextField))
    {
        return true;
    } else {
        return false;
    }
}

extern "C" gcn::Widget *newInstance() // doesnt add to "top" 
{
    gceTextField *c=new gceTextField();
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
    node->SetAttribute("text",((gcn::TextField*)currentWidget)->getText().c_str());
}

extern "C" void setExtendedFromNode(TiXmlElement *node)
{
    ((gcn::TextField*)currentWidget)->setText(node->Attribute("text"));    
}

const char textfieldName[]="gcn::TextField";
extern "C" const char* componentName()
{
    return &textfieldName[0];
}
