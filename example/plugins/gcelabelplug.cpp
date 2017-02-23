#include <guichan.hpp>
#include <typeinfo>
#include <gmodule.h>

#include "tinyxml.h"

extern "C" gboolean canParent()
{
    return false;
}

extern "C" gcn::Widget *newInstance() // doesnt add to "top"
{
    gcn::Label *c=new gcn::Label();
    return c;
}

extern "C" void setExtendedFromNode(TiXmlElement *node, gcn::Widget *currentWidget)
{
    ((gcn::Label*)currentWidget)->setCaption(node->Attribute("caption"));

    if (strcmp("LEFT",node->Attribute("alignment"))==0) ((gcn::Label*)currentWidget)->setAlignment(gcn::Graphics::LEFT);
    if (strcmp("CENTRE",node->Attribute("alignment"))==0) ((gcn::Label*)currentWidget)->setAlignment(gcn::Graphics::CENTER);
    if (strcmp("RIGHT",node->Attribute("alignment"))==0) ((gcn::Label*)currentWidget)->setAlignment(gcn::Graphics::RIGHT);
    
}

const char labelName[]="gcn::Label";
extern "C" const char* componentName()
{
    return &labelName[0];
}

