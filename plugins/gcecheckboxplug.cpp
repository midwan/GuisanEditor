#include <guichan.hpp>
#include <typeinfo>
#include <gmodule.h>

#include "gcecheckbox.hpp"
#include "editorGui.hpp"
#include "mouselistener.hpp"

#include "gcebase.hpp"

// each component type has its own extended property "sheet" (extendedProps)
static gcn::Container *extendedProps;
static gcn::TextField *checkCaptionEdit;
static int checkBoxIndex;
static gcn::CheckBox *isChecked;


// this routine actually updates the proprties, its static so
// the plugin can call it, as well as the plugins public function
static void doExtended()
{
    checkCaptionEdit->setText(((gcn::Button*)currentWidget)->getCaption());
    isChecked->setSelected(((gcn::CheckBox*)currentWidget)->isSelected());
}


// The action listener deals with the "creation" button and the actions
// of the extended property container (basic gcn::Widget properties of 
// the plugin are dealt with by the editor)

class checkActionListener : public gcn::ActionListener
{
    void action(const gcn::ActionEvent& actionEvent);
};

static checkActionListener *ckListener;

void checkActionListener::action(const gcn::ActionEvent& actionEvent)
{
    if (actionEvent.getId() == "newCheckBox")
    {
        checkBoxIndex++;
        char s[256];
        sprintf(s,"CheckBox%i",checkBoxIndex);
        gceCheckBox *b=new gceCheckBox();       // create widgets with default constructor only for plugin uniformity
        
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
    if (actionEvent.getId() == "checkBoxEdit")   ((gceCheckBox*)currentWidget)->setCaption(checkCaptionEdit->getText());
    if (actionEvent.getId() == "isChecked") ((gceCheckBox*)currentWidget)->setSelected(isChecked->isSelected());

}


extern "C" gcn::Button *initComponent()
{
    extendedProps = new gcn::Container();
    extendedProps->setSize(SHEET_WIDTH,SHEET_HEIGHT);
    
    ckListener=new checkActionListener();
    gcn::Button *b=new gcn::Button("CheckBox"); // a button for making new buttons!
    b->adjustSize();
    b->setHeight(b->getHeight()-6);

    b->setActionEventId("newCheckBox");
    b->addActionListener(ckListener);
    
    checkCaptionEdit=new gcn::TextField();
    checkCaptionEdit->setSize(84,18);
    checkCaptionEdit->setActionEventId("checkBoxEdit");
    checkCaptionEdit->addActionListener(ckListener);
    
    gcn::Label* captionLabel=new gcn::Label("Caption");
    captionLabel->setFont(labelFont);
    
    isChecked=new gcn::CheckBox("Checked");
    isChecked->setActionEventId("isChecked");
    isChecked->addActionListener(ckListener);
        
    extendedProps->add(isChecked,8,48);
    
    extendedProps->add(checkCaptionEdit,8,14);
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
    if (typeid(*currentWidget) == typeid(gceCheckBox))
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
    gceCheckBox *c=new gceCheckBox();
    ((gceBase*)c)->emptyMouseListeners();
    c->addMouseListener(&MListener);

    return c;
}

extern "C" void exportNodeExtended(TiXmlElement *node)
{
    // currentWidget is set by iteration
    node->SetAttribute("caption",((gceCheckBox*)currentWidget)->getCaption().c_str());
    if (((gceCheckBox*)currentWidget)->isSelected())
    {
        node->SetAttribute("checked","true");
    } else {
        node->SetAttribute("checked","false");
    }
    
}


extern "C" void setExtendedFromNode(TiXmlElement *node)
{
    ((gcn::Button*)currentWidget)->setCaption(node->Attribute("caption"));
    if (strcmp("true",node->Attribute("checked"))==0) 
    {
        ((gceCheckBox*)currentWidget)->setSelected(true);
    } else {
        ((gceCheckBox*)currentWidget)->setSelected(false);
    }
    
}

const char checkName[]="gcn::CheckBox";
extern "C" const char* componentName()
{
    return &checkName[0];
}

