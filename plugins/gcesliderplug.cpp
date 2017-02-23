#include <guichan.hpp>
#include <typeinfo>
#include <gmodule.h>

#include "gceslider.hpp"
#include "editorGui.hpp"
#include "mouselistener.hpp"

#include "gcebase.hpp"

// each component type has its own extended property "sheet" (extendedProps)
static gcn::Container *extendedProps;

// here define a bunch of static widgets for use on the extended properties sheet
static gcn::TextField *markerLength;
static gcn::CheckBox *vertical;
static gcn::TextField *scaleEnd;
static gcn::TextField *scaleStart;
static gcn::TextField *stepLength;


static void doExtended()
{
    char tmp[256];
    int l=((gcn::Slider*)currentWidget)->getMarkerLength();
    sprintf(tmp,"%i",l);
    markerLength->setText(tmp);

    if (((gcn::Slider*)currentWidget)->getOrientation()==gcn::Slider::VERTICAL)
    {
        vertical->setSelected(true);
    } else {
        vertical->setSelected(false);
    }

    float f=((gcn::Slider*)currentWidget)->getScaleEnd();
    sprintf(tmp,"%f",f);
    scaleEnd->setText(tmp);

    f=((gcn::Slider*)currentWidget)->getScaleStart();
    sprintf(tmp,"%f",f);
    scaleStart->setText(tmp);

    f=((gcn::Slider*)currentWidget)->getStepLength();
    sprintf(tmp,"%f",f);
    stepLength->setText(tmp);
}


// The action listener deals with the "creation" button and the actions
// of the extended property container (basic gcn::Widget properties of 
// the plugin are dealt with by the editor)

class sliderActionListener : public gcn::ActionListener
{
    void action(const gcn::ActionEvent& actionEvent);
};

static sliderActionListener *slListener;

void sliderActionListener::action(const gcn::ActionEvent& actionEvent)
{
    if (actionEvent.getId() == "newSlider")
    {
        gceSlider *c=new gceSlider();
        c->setPosition(16,16);
        c->setSize(140,14);
//        ((gceBase*)c)->emptyMouseListeners();
        c->addMouseListener(&MListener);   // all components must add editors global mouse listener
        top->add(c);
        currentWidget=c;

        // never do updateExtendedProperties(); as you will get the routine from the first plugin!
        doExtended();
        updateBaseProperties();
    }
    
    // if a property pane widget wants to change the edited widgets properties
    // so set currentWidget's properties acordingly

    if (actionEvent.getId() == "markerLength")
    {
        ((gcn::Slider*)currentWidget)->setMarkerLength(atoi(markerLength->getText().c_str()));
    }

    if (actionEvent.getId() == "vertical")
    {
        if (vertical->isSelected())
        {
            ((gcn::Slider*)currentWidget)->setOrientation(gcn::Slider::VERTICAL); 
        } else {
            ((gcn::Slider*)currentWidget)->setOrientation(gcn::Slider::HORIZONTAL); 
        }
        int w=currentWidget->getWidth();
        int h=currentWidget->getHeight();
        currentWidget->setSize(h,w); // yes that way round! ;)
    }

    if (actionEvent.getId() == "scaleStart")
    {
        ((gcn::Slider*)currentWidget)->setScaleStart(atof(scaleStart->getText().c_str()));
    }

    if (actionEvent.getId() == "scaleEnd")
    {
        ((gcn::Slider*)currentWidget)->setScaleEnd(atof(scaleEnd->getText().c_str()));
    }

    if (actionEvent.getId() == "stepLength")
    {
        ((gcn::Slider*)currentWidget)->setStepLength(atof(stepLength->getText().c_str()));
    }
}


extern "C" gcn::Button *initComponent()
{
    extendedProps = new gcn::Container();
    extendedProps->setSize(SHEET_WIDTH,SHEET_HEIGHT);
    
    slListener=new sliderActionListener();

    gcn::Button *b=new gcn::Button("Slider"); // a button for making new skeletons!
    b->adjustSize();
    b->setHeight(b->getHeight()-6);

    b->setActionEventId("newSlider");
    b->addActionListener(slListener);

    // initialise the extended property widgets
    // add the listener and and action id so
    // they can alter a widgets 
    // add them to extendedProps!
    markerLength=new gcn::TextField("");
    markerLength->setWidth(100);
    markerLength->setActionEventId("markerLength");
    markerLength->addActionListener(slListener);
    extendedProps->add(markerLength,8,18);
    
    vertical=new gcn::CheckBox("Vertical");
    vertical->setWidth(100);
    vertical->setActionEventId("vertical");
    vertical->addActionListener(slListener);
    extendedProps->add(vertical,8,48);

    scaleStart=new gcn::TextField("");
    scaleStart->setWidth(100);
    scaleStart->setActionEventId("scaleStart");
    scaleStart->addActionListener(slListener);
    extendedProps->add(scaleStart,8,88);
     
    scaleEnd=new gcn::TextField("");
    scaleEnd->setWidth(100);
    scaleEnd->setActionEventId("scaleEnd");
    scaleEnd->addActionListener(slListener);
    extendedProps->add(scaleEnd,8,128);
     
    stepLength=new gcn::TextField("");
    stepLength->setWidth(100);
    stepLength->setActionEventId("stepLength");
    stepLength->addActionListener(slListener);
    extendedProps->add(stepLength,8,168);

    gcn::Label *bw=new gcn::Label("Bar width");
    bw->setFont(labelFont);
    extendedProps->add(bw,8,2);

    gcn::Label *ss=new gcn::Label("Start");
    ss->setFont(labelFont);
    extendedProps->add(ss,8,74);

    gcn::Label *se=new gcn::Label("End");
    se->setFont(labelFont);
    extendedProps->add(se,8,114);

    gcn::Label *st=new gcn::Label("Step");
    st->setFont(labelFont);
    extendedProps->add(st,8,154);
    
     
    extendedProps->setBaseColor(gcn::Color(255, 128, 128, 0));

    return b; // editor adds button, sizes and positions it
}

extern "C" gboolean canParent()
{
    return false;    // does the component maintain its own mWidgets list
}
        
        
extern "C" gboolean currentIsThisType()
{
    if (typeid(*currentWidget) == typeid(gceSlider))
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
    gceSlider *c=new gceSlider();
    //((gceBase*)c)->emptyMouseListeners();
    c->addMouseListener(&MListener);

    return c;
}


extern "C" void exportNodeExtended(TiXmlElement *node)
{
    char tmp[256];
    int l=((gcn::Slider*)currentWidget)->getMarkerLength();
    sprintf(tmp,"%i",l);
    node->SetAttribute("markerLength",tmp);

    if (((gcn::Slider*)currentWidget)->getOrientation()==gcn::Slider::VERTICAL)
    {
        node->SetAttribute("vertical","true");
    } else {
        node->SetAttribute("vertical","false");
    }

    float f=((gcn::Slider*)currentWidget)->getScaleEnd();
    sprintf(tmp,"%f",f);
    node->SetAttribute("scaleEnd",tmp);

    f=((gcn::Slider*)currentWidget)->getScaleStart();
    sprintf(tmp,"%f",f);
    node->SetAttribute("scaleStart",tmp);

    f=((gcn::Slider*)currentWidget)->getStepLength();
    sprintf(tmp,"%f",f);
    node->SetAttribute("stepLength",tmp);

}

#include <iostream>
extern "C" void setExtendedFromNode(TiXmlElement *node)
{
    ((gcn::Slider*)currentWidget)->setMarkerLength(atoi(node->Attribute("markerLength")));


    if (strcmp("true",node->Attribute("vertical"))==0)
    {
        ((gcn::Slider*)currentWidget)->setOrientation(gcn::Slider::VERTICAL);
    } else {
        ((gcn::Slider*)currentWidget)->setOrientation(gcn::Slider::HORIZONTAL);
    }
    ((gcn::Slider*)currentWidget)->setScaleStart(atof(node->Attribute("scaleStart")));
    ((gcn::Slider*)currentWidget)->setScaleEnd(atof(node->Attribute("scaleEnd")));
    ((gcn::Slider*)currentWidget)->setStepLength(atof(node->Attribute("stepLength")));
}

const char slName[]="gcn::Slider";
extern "C" const char* componentName()
{
    return &slName[0];
}

