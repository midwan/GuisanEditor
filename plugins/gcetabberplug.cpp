#include <guichan.hpp>
#include <typeinfo>
#include <gmodule.h>

#include "gcetabber.hpp"
#include "editorGui.hpp"
#include "mouselistener.hpp"

#include "gcebase.hpp"

static gcn::Container *tabExtendedProps;
//static gcn::TextField *tabCaptionEdit;

static void doExtended()
{
//    tabCaptionEdit->setText(((gceTabber*)currentWidget)->getCaption());
}

class tbActionListener : public gcn::ActionListener
{
    void action(const gcn::ActionEvent& actionEvent);
};

static tbActionListener *tbListener;

void tbActionListener::action(const gcn::ActionEvent& actionEvent)
{
    if (actionEvent.getId() == "newTabber")
    {
        gceTabber *tb=new gceTabber();
//        tb->setCaption("New Tabber");
        tb->setPosition(16,16);
        tb->setSize(110,110);
//        ((gceBase*)tb)->emptyMouseListeners();
//        tb->addMouseListener(&MListener);   // all components must add editors global mouse listener
        
        gcn::Container* c1=new gcn::Container();
        gcn::Container* c2=new gcn::Container();
        c1->setSize(60,60);
        c2->setSize(60,60);
    
        c1->addMouseListener(&MListener);    

        gcn::Tab *t1=new gcn::Tab;
        t1->setCaption("Tab 1");
        t1->setSize(40,20);
        tb->addTab(t1,c1);
//        t1->addMouseListener(&MListener);

        gcn::Tab *t2=new gcn::Tab;

        t2->setCaption("Tab 2");
        t2->setSize(40,20);
        tb->addTab(t2,c2);
//        t2->addMouseListener(&MListener);
        

        
        top->add(tb);
        currentWidget=tb;
        doExtended();
        updateBaseProperties();
    }
    
//    if (actionEvent.getId() == "captionEdit") ((gceTabber*)currentWidget)->setCaption(tabCaptionEdit->getText());

}


extern "C" gcn::Button *initComponent()
{
    tabExtendedProps = new gcn::Container();
    tabExtendedProps->setSize(SHEET_WIDTH,SHEET_HEIGHT);
        
    tbListener=new tbActionListener();
    gcn::Button *b=new gcn::Button("Tabber"); 
    b->adjustSize();
    b->setHeight(b->getHeight()-6);

    b->setActionEventId("newTabber");
    b->addActionListener(tbListener);
    
//    tabCaptionEdit=new gcn::TextField();
//    tabCaptionEdit->setSize(84,18);    
//    tabCaptionEdit->setActionEventId("captionEdit");
//    tabCaptionEdit->addActionListener(tbListener);

    
    
    gcn::Label *tl=new gcn::Label("Caption");
    tl->setFont(labelFont);
    tabExtendedProps->add(tl,8,0);

//    tabExtendedProps->add(captionEdit,8,14); 
    tabExtendedProps->setBaseColor(gcn::Color(255, 128, 128, 0));
    
    return b;
}

extern "C" gboolean canParent()
{
    return true;
}
        
extern "C" gboolean currentIsThisType()
{
    if (typeid(*currentWidget) == typeid(gceTabber))
    {
        return true;
    } else {
        return false;
    }
}


extern "C" gcn::Widget *newInstance() // doesnt add to "top" 
{
    gceTabber *c=new gceTabber();
    ((gceBase*)c)->emptyMouseListeners();
    c->addMouseListener(&MListener);

    return c;
}

extern "C" void updateExtendedProperties()
{
    if (oldExtendedProps!=tabExtendedProps)
    {
        if (oldExtendedProps!=NULL) extended->remove(oldExtendedProps);
        extended->add(tabExtendedProps,0,0);
    }  // every pluing must do this
    
    doExtended();
        
    oldExtendedProps=tabExtendedProps;  // every plugin must do this
}

extern "C" void exportNodeExtended(TiXmlElement *node)
{
//       node->SetAttribute("caption",((gcn::Tabber*)currentWidget)->getCaption().c_str());
}

extern "C" void setExtendedFromNode(TiXmlElement *node)
{
//    ((gcn::Tabber*)currentWidget)->setCaption(node->Attribute("caption"));
}

const char windowName[]="gcn::Tabber";
extern "C" const char* componentName()
{
    return &windowName[0];
}
