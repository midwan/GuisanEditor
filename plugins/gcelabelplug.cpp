#include <guichan.hpp>
#include <typeinfo>
#include <gmodule.h>

#include "gcelabel.hpp"
#include "editorGui.hpp"
#include "mouselistener.hpp"

#include "gcebase.hpp"

// each component type has its own extended property "sheet" (extendedProps)
static gcn::Container *extendedProps;
static gcn::TextField *lcaptionEdit;
static int labelIndex;
static gcn::RadioButton *alignL;
static gcn::RadioButton *alignC;
static gcn::RadioButton *alignR;




// this routine actually updates the proprties, its static so
// the plugin can call it, as well as the plugins public function
static void doExtended()
{
    lcaptionEdit->setText(((gcn::Label*)currentWidget)->getCaption());
    
    if (((gcn::Label*)currentWidget)->getAlignment()==gcn::Graphics::LEFT)  alignL->setSelected(true);
    if (((gcn::Label*)currentWidget)->getAlignment()==gcn::Graphics::CENTER)  alignC->setSelected(true);
    if (((gcn::Label*)currentWidget)->getAlignment()==gcn::Graphics::RIGHT)  alignR->setSelected(true);
    
}


// The action listener deals with the "creation" button and the actions
// of the extended property container (basic gcn::Widget properties of 
// the plugin are dealt with by the editor)

class labelActionListener : public gcn::ActionListener
{
    void action(const gcn::ActionEvent& actionEvent);
};

static labelActionListener *lListener;

void labelActionListener::action(const gcn::ActionEvent& actionEvent)
{
    if (actionEvent.getId() == "newLabel")
    {
        labelIndex++;
        char s[256];
        sprintf(s,"Label%i",labelIndex);
        gceLabel *b=new gceLabel();
        
        ((gceBase*)b)->emptyMouseListeners();
        b->setCaption(s);
        b->adjustSize();
        b->setPosition(16,16);
        b->addMouseListener(&MListener);   // all components must add editors global mouse listener

        top->add(b);
        currentWidget=b;
        // never do updateExtendedProperties(); as you will get the routine from the first plugin!
        doExtended();
        updateBaseProperties();
    }
    
    // a property pane widget wants to change the edited widgets properties
    if (actionEvent.getId() == "captionEdit")   ((gceLabel*)currentWidget)->setCaption(lcaptionEdit->getText());
    if (actionEvent.getId() == "aL")            ((gceLabel*)currentWidget)->setAlignment(gcn::Graphics::LEFT);
    if (actionEvent.getId() == "aC")            ((gceLabel*)currentWidget)->setAlignment(gcn::Graphics::CENTER);
    if (actionEvent.getId() == "aR")            ((gceLabel*)currentWidget)->setAlignment(gcn::Graphics::RIGHT);

}


extern "C" gcn::Button *initComponent()
{
    extendedProps = new gcn::Container();
    extendedProps->setSize(SHEET_WIDTH,SHEET_HEIGHT);
    
    lListener=new labelActionListener();
    gcn::Button *b=new gcn::Button("Label"); 
    b->adjustSize();
    b->setHeight(b->getHeight()-6);
    b->setActionEventId("newLabel");
    b->addActionListener(lListener);
    
    lcaptionEdit=new gcn::TextField();
    lcaptionEdit->setSize(84,18);
    lcaptionEdit->setActionEventId("captionEdit");
    lcaptionEdit->addActionListener(lListener);
    
    gcn::Label* captionLabel=new gcn::Label("Caption");
    captionLabel->setFont(labelFont);
    
    alignL=new gcn::RadioButton("LEFT", "buttonA", true);
    alignC=new gcn::RadioButton("CENTER", "buttonA");
    alignR=new gcn::RadioButton("RIGHT", "buttonA");
    alignL->setActionEventId("aL");
    alignC->setActionEventId("aC");
    alignR->setActionEventId("aR");
    alignL->addActionListener(lListener);
    alignC->addActionListener(lListener);
    alignR->addActionListener(lListener);
    
    gcn::Label *al=new gcn::Label("Alignment");
    al->setFont(labelFont);
    extendedProps->add(alignL,8,48);
    extendedProps->add(alignC,8,66);
    extendedProps->add(alignR,8,84);
    extendedProps->add(al,8,33);
    
    extendedProps->add(lcaptionEdit,8,14);
    extendedProps->add(captionLabel,8,0);
     
    extendedProps->setBaseColor(gcn::Color(255, 128, 128, 0));

    return b; // editor adds button, sizes and positions it
}

extern "C" gboolean canParent()
{
    return false;
}
        
        
extern "C" gboolean currentIsThisType()
{
    if (typeid(*currentWidget) == typeid(gceLabel))
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
    }
    
    doExtended();
        
    oldExtendedProps=extendedProps;  // so we know if update is needed for extended prop container
}

extern "C" gcn::Widget *newInstance() // doesnt add to "top"
{
    gceLabel *c=new gceLabel();
    ((gceBase*)c)->emptyMouseListeners();
    c->addMouseListener(&MListener);

    return c;
}

extern "C" void exportNodeExtended(TiXmlElement *node)
{
    // currentWidget is set by iteration
    node->SetAttribute("caption",((gceLabel*)currentWidget)->getCaption().c_str());
    switch (((gceLabel*)currentWidget)->getAlignment())
    {
        case gcn::Graphics::LEFT:
            node->SetAttribute("alignment","LEFT");
            break;
        case gcn::Graphics::CENTER:
            node->SetAttribute("alignment","CENTRE");
            break;
        case gcn::Graphics::RIGHT:
            node->SetAttribute("alignment","RIGHT");
            break;
    }

}


extern "C" void setExtendedFromNode(TiXmlElement *node)
{
    ((gcn::Label*)currentWidget)->setCaption(node->Attribute("caption"));

    if (strcmp("LEFT",node->Attribute("alignment"))==0) ((gceLabel*)currentWidget)->setAlignment(gcn::Graphics::LEFT);
    if (strcmp("CENTRE",node->Attribute("alignment"))==0) ((gceLabel*)currentWidget)->setAlignment(gcn::Graphics::CENTER);
    if (strcmp("RIGHT",node->Attribute("alignment"))==0) ((gceLabel*)currentWidget)->setAlignment(gcn::Graphics::RIGHT);
    
}

const char labelName[]="gcn::Label";
extern "C" const char* componentName()
{
    return &labelName[0];
}

