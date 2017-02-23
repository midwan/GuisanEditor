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
    gcn::TextField *c=new gcn::TextField();
    return c;
}

extern "C" void setExtendedFromNode(TiXmlElement *node, gcn::Widget *currentWidget)
{
    ((gcn::TextField*)currentWidget)->setText(node->Attribute("text"));    
}

const char textfieldName[]="gcn::TextField";
extern "C" const char* componentName()
{
    return &textfieldName[0];
}
