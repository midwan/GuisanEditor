#include <guichan.hpp>
#include <typeinfo>
#include <gmodule.h>

#include "gceradiobutton.hpp"
#include "editorGui.hpp"
#include "mouselistener.hpp"

#include "gcebase.hpp"

// each component type has its own extended property "sheet" (extendedProps)
static gcn::Container *extendedProps;
static gcn::TextField *radioCaptionEdit;
static gcn::TextField *radioGroupEdit;
static int radioButtonIndex;
static gcn::CheckBox *isChecked;


// this routine actually updates the proprties, its static so
// the plugin can call it, as well as the plugins public function
static void doExtended()
{
    radioCaptionEdit->setText(((gcn::RadioButton*)currentWidget)->getCaption());
    radioGroupEdit->setText(((gcn::RadioButton*)currentWidget)->getGroup());
    isChecked->setSelected(((gcn::RadioButton*)currentWidget)->isSelected());
}


// The action listener deals with the "creation" button and the actions
// of the extended property container (basic gcn::Widget properties of 
// the plugin are dealt with by the editor)

class radioActionListener : public gcn::ActionListener
{
    void action(const gcn::ActionEvent& actionEvent);
};

static radioActionListener *rbListener;

void radioActionListener::action(const gcn::ActionEvent& actionEvent)
{
    if (actionEvent.getId() == "newRadioButton")
    {
        radioButtonIndex++;
        char s[256];
        sprintf(s,"RadioButton%i",radioButtonIndex);
        gceRadioButton *b=new gceRadioButton();       // create widgets with default constructor only for plugin uniformity
        
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
    if (actionEvent.getId() == "radioButtonEdit")   ((gceRadioButton*)currentWidget)->setCaption(radioCaptionEdit->getText());
    if (actionEvent.getId() == "radioGroupEdit")   ((gceRadioButton*)currentWidget)->setGroup(radioGroupEdit->getText());
    if (actionEvent.getId() == "isChecked") ((gceRadioButton*)currentWidget)->setSelected(isChecked->isSelected());

}


extern "C" gcn::Button *initComponent()
{
    extendedProps = new gcn::Container();
    extendedProps->setSize(SHEET_WIDTH,SHEET_HEIGHT);
    
    rbListener=new radioActionListener();
    gcn::Button *b=new gcn::Button("RadioButton"); // a button for making new buttons!
    b->adjustSize();
    b->setHeight(b->getHeight()-6);

    b->setActionEventId("newRadioButton");
    b->addActionListener(rbListener);
    
    radioCaptionEdit=new gcn::TextField();
    radioCaptionEdit->setSize(84,18);
    radioCaptionEdit->setActionEventId("radioButtonEdit");
    radioCaptionEdit->addActionListener(rbListener);
    
    radioGroupEdit=new gcn::TextField();
    radioGroupEdit->setSize(84,18);
    radioGroupEdit->setActionEventId("radioGroupEdit");
    radioGroupEdit->addActionListener(rbListener);
    
    gcn::Label* captionLabel=new gcn::Label("Caption");
    captionLabel->setFont(labelFont);
    
    gcn::Label* groupLabel=new gcn::Label("Group");
    groupLabel->setFont(labelFont);
    
    isChecked=new gcn::CheckBox("Checked");
    isChecked->setActionEventId("isChecked");
    isChecked->addActionListener(rbListener);
        
    extendedProps->add(isChecked,8,48);
    
    extendedProps->add(radioCaptionEdit,8,14);
    extendedProps->add(captionLabel,8,0);
    extendedProps->add(radioGroupEdit,8,92);
    extendedProps->add(groupLabel,8,78);
     
    extendedProps->setBaseColor(gcn::Color(255, 128, 128, 0));

    return b; // editor adds button, sizes and positions it
}

extern "C" gboolean canParent()
{
    return false;
}
        
        
extern "C" gboolean currentIsThisType()
{
    if (typeid(*currentWidget) == typeid(gceRadioButton))
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
    gceRadioButton *c=new gceRadioButton();
    ((gceBase*)c)->emptyMouseListeners();
    c->addMouseListener(&MListener);

    return c;
}

extern "C" void exportNodeExtended(TiXmlElement *node)
{
    // currentWidget is set by iteration
    node->SetAttribute("caption",((gceRadioButton*)currentWidget)->getCaption().c_str());
    node->SetAttribute("group",((gceRadioButton*)currentWidget)->getGroup().c_str());
    if (((gceRadioButton*)currentWidget)->isSelected())
    {
        node->SetAttribute("checked","true");
    } else {
        node->SetAttribute("checked","false");
    }
    
}


extern "C" void setExtendedFromNode(TiXmlElement *node)
{
    ((gcn::RadioButton*)currentWidget)->setCaption(node->Attribute("caption"));
    ((gcn::RadioButton*)currentWidget)->setGroup(node->Attribute("group"));
    if (strcmp("true",node->Attribute("checked"))==0) 
    {
        ((gceRadioButton*)currentWidget)->setSelected(true);
    } else {
        ((gceRadioButton*)currentWidget)->setSelected(false);
    }
    
}

const char radioName[]="gcn::RadioButton";
extern "C" const char* componentName()
{
    return &radioName[0];
}

