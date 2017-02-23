#include <guichan.hpp>
#include <typeinfo>
#include <gmodule.h>

#include "gceskeleton.hpp"
#include "editorGui.hpp"
#include "mouselistener.hpp"

#include "gcebase.hpp"

// each component type has its own extended property "sheet" (extendedProps)
static gcn::Container *extendedProps;

// here define a bunch of static widgets for use on the extended properties sheet


// this routine actually updates the proprties, its static so
// the plugin can call it, as well as the plugins public function
// this sets the widgets on the extendedProps sheet with the properties
// of the currentWidget being edited
static void doExtended()
{

}


// The action listener deals with the "creation" button and the actions
// of the extended property container (basic gcn::Widget properties of 
// the plugin are dealt with by the editor)

class skeletonActionListener : public gcn::ActionListener
{
    void action(const gcn::ActionEvent& actionEvent);
};

static skeletonActionListener *skelListener;

void skeletonActionListener::action(const gcn::ActionEvent& actionEvent)
{
    if (actionEvent.getId() == "newSkeleton")
    {
        // if the new widget needs a caption set it here
        // remove its default mouselistener's
        // add the editors mouselistener
        // add and position on the "top" widget
        // set currentWidget to this new widget

        // never do updateExtendedProperties(); as you will get the routine from the first plugin!
        doExtended();
        updateBaseProperties();
    }
    
    // if a property pane widget wants to change the edited widgets properties
    // so set currentWidget's properties acordingly
}


extern "C" gcn::Button *initComponent()
{
    extendedProps = new gcn::Container();
    extendedProps->setSize(SHEET_WIDTH,SHEET_HEIGHT);
    
    skelListener=new skeletonActionListener();

    gcn::Button *b=new gcn::Button("Skeleton"); // a button for making new skeletons!
    b->adjustSize();
    b->setHeight(b->getHeight()-6);

    b->setActionEventId("newSkeleton");
    b->addActionListener(rbListener);

    // initialise the extended property widgets
    // add the listener and and action id so
    // they can alter a widgets 
    // add them to extendedProps!
     
    extendedProps->setBaseColor(gcn::Color(255, 128, 128, 0));

    return b; // editor adds button, sizes and positions it
}

extern "C" gboolean canParent()
{
    return false;    // does the component maintain its own mWidgets list
}
        
        
extern "C" gboolean currentIsThisType()
{
    if (typeid(*currentWidget) == typeid(gceSkeleton))
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

extern "C" gceSkeleton *newInstance() // doesnt add to "top"
{
    gceSkeleton *c=new gceSkeleton();
    ((gceBase*)c)->emptyMouseListeners();
    c->addMouseListener(&MListener);

    return c;
}

extern "C" void exportNodeExtended(TiXmlElement *node)
{
    // currentWidget is set by iteration

    // set node's xml attributes from the extended properties
    // of currentWidget

}


extern "C" void setExtendedFromNode(TiXmlElement *node)
{
    // set currentWidget extended properties from the
    // node's attributes
}

const char skelName[]="gceSkeleton";
extern "C" const char* componentName()
{
    return &skelName[0];
}

