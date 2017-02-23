#include <guichan.hpp>
#include <typeinfo>
#include <gmodule.h>

#include "examplebutton.hpp"
#include "editorGui.hpp"
#include "mouselistener.hpp"

#include "gcebase.hpp"

// straight copy of the button plugin with some name changes

// each component type has its own extended property "sheet" (extendedProps)
static gcn::Container *extendedProps;
static gcn::TextField *captionEdit;
static int buttonIndex;
static gcn::RadioButton *alignL;
static gcn::RadioButton *alignC;
static gcn::RadioButton *alignR;
static gcn::Slider *spacing;



// this routine actually updates the proprties, its static so
// the plugin can call it, as well as the plugins public function
static void doExtended()
{
    captionEdit->setText(((gcn::Button*)currentWidget)->getCaption());
    
    if (((gcn::Button*)currentWidget)->getAlignment()==gcn::Graphics::LEFT)  alignL->setSelected(true);
    if (((gcn::Button*)currentWidget)->getAlignment()==gcn::Graphics::CENTER)  alignC->setSelected(true);
    if (((gcn::Button*)currentWidget)->getAlignment()==gcn::Graphics::RIGHT)  alignR->setSelected(true);
    
    spacing->setValue(((gcn::Button*)currentWidget)->getSpacing());
    
}


// The action listener deals with the "creation" button and the actions
// of the extended property container (basic gcn::Widget properties of 
// the plugin are dealt with by the editor)


class examplebuttonActionListener : public gcn::ActionListener
{
    void action(const gcn::ActionEvent& actionEvent);
};

static examplebuttonActionListener *ebListener;

void examplebuttonActionListener::action(const gcn::ActionEvent& actionEvent)
{
    if (actionEvent.getId() == "newButton")
    {
        buttonIndex++;
        char s[256];
        sprintf(s,"Button%i",buttonIndex);
        exampleButton *b=new exampleButton();       // create widgets with default constructor only for plugin uniformity
        
//        ((gceBase*)b)->emptyMouseListeners();
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
    if (actionEvent.getId() == "captionEdit")   ((exampleButton*)currentWidget)->setCaption(captionEdit->getText());
    if (actionEvent.getId() == "aL")            ((exampleButton*)currentWidget)->setAlignment(gcn::Graphics::LEFT);
    if (actionEvent.getId() == "aC")            ((exampleButton*)currentWidget)->setAlignment(gcn::Graphics::CENTER);
    if (actionEvent.getId() == "aR")            ((exampleButton*)currentWidget)->setAlignment(gcn::Graphics::RIGHT);
    if (actionEvent.getId() == "spacing")       ((exampleButton*)currentWidget)->setSpacing((unsigned int)spacing->getValue());

}


extern "C" gcn::Button *initComponent()
{

    exampleButton::loadThemeImage(std::string("images/buttonskin.png"));

    extendedProps = new gcn::Container();
    extendedProps->setSize(SHEET_WIDTH,SHEET_HEIGHT);
    
    ebListener=new examplebuttonActionListener();
    gcn::Button *b=new gcn::Button("exampleButton"); // a button for making new buttons!
    b->adjustSize();
    b->setHeight(b->getHeight()-6);
    b->setActionEventId("newButton");
    b->addActionListener(ebListener);
    
    captionEdit=new gcn::TextField();
    captionEdit->setSize(84,18);
    captionEdit->setActionEventId("captionEdit");
    captionEdit->addActionListener(ebListener);
    
    gcn::Label* captionLabel=new gcn::Label("Caption");
    captionLabel->setFont(labelFont);
    
    alignL=new gcn::RadioButton("LEFT", "buttonA", true);
    alignC=new gcn::RadioButton("CENTER", "buttonA");
    alignR=new gcn::RadioButton("RIGHT", "buttonA");
    alignL->setActionEventId("aL");
    alignC->setActionEventId("aC");
    alignR->setActionEventId("aR");
    alignL->addActionListener(ebListener);
    alignC->addActionListener(ebListener);
    alignR->addActionListener(ebListener);
    
    spacing=new gcn::Slider(128);
    spacing->setSize(130,10);
    spacing->setActionEventId("spacing");
    spacing->addActionListener(ebListener);
    gcn::Label *sl=new gcn::Label("Spacing");
    sl->setFont(labelFont);
    
    gcn::Label *al=new gcn::Label("Alignment");
    al->setFont(labelFont);
    extendedProps->add(alignL,8,48);
    extendedProps->add(alignC,8,66);
    extendedProps->add(alignR,8,84);
    extendedProps->add(al,8,33);
    
    extendedProps->add(captionEdit,8,14);
    extendedProps->add(captionLabel,8,0);
     
    extendedProps->add(sl,8,120);
    extendedProps->add(spacing,8,134);
    
    extendedProps->setBaseColor(gcn::Color(255, 128, 128, 0));

    return b; // editor adds button, sizes and positions it
}

extern "C" gboolean canParent()
{
    return false;
}
        
        
extern "C" gboolean currentIsThisType()
{
    if (typeid(*currentWidget) == typeid(exampleButton))
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
    exampleButton *c=new exampleButton();
//    ((gceBase*)c)->emptyMouseListeners();
    c->addMouseListener(&MListener);

    return c;
}

extern "C" void exportNodeExtended(TiXmlElement *node)
{
    // currentWidget is set by iteration
    node->SetAttribute("caption",((exampleButton*)currentWidget)->getCaption().c_str());
    switch (((exampleButton*)currentWidget)->getAlignment())
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
    node->SetAttribute("spacing",((exampleButton*)currentWidget)->getSpacing());
    
}


extern "C" void setExtendedFromNode(TiXmlElement *node)
{
    ((gcn::Button*)currentWidget)->setCaption(node->Attribute("caption"));
    int i;
    node->QueryIntAttribute("spacing",&i);
    ((gcn::Button*)currentWidget)->setSpacing(i);

    if (strcmp("LEFT",node->Attribute("alignment"))==0) ((exampleButton*)currentWidget)->setAlignment(gcn::Graphics::LEFT);
    if (strcmp("CENTRE",node->Attribute("alignment"))==0) ((exampleButton*)currentWidget)->setAlignment(gcn::Graphics::CENTER);
    if (strcmp("RIGHT",node->Attribute("alignment"))==0) ((exampleButton*)currentWidget)->setAlignment(gcn::Graphics::RIGHT);
    
}

const char exampleButtonName[]="exampleButton";
extern "C" const char* componentName()
{
    return &exampleButtonName[0];
}

