#include <guichan.hpp>
#include <typeinfo>
#include <gmodule.h>
#include "tinyxml.h"

#include "examplebutton.hpp"

gcn::Image  *mImage;


extern "C" gboolean canParent()
{
    return false;
}
extern "C" gcn::Widget *newInstance() // doesnt add to "top" 
{
    if (mImage==NULL) {
        exampleButton::loadThemeImage(std::string("buttonskin.png"));
    }
    
    exampleButton *c=new exampleButton();
    return c;
}

extern "C" void setExtendedFromNode(TiXmlElement *node, gcn::Widget *currentWidget)
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

