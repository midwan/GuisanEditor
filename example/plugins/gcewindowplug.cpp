#include <guichan.hpp>
#include <typeinfo>
#include <gmodule.h>
#include "tinyxml.h"

extern "C" gboolean canParent()
{
    return true;
}

extern "C" gcn::Widget *newInstance() // doesnt add to "top"
{
    gcn::Window *c=new gcn::Window();
    return c;
}

extern "C" void setExtendedFromNode(TiXmlElement *node, gcn::Widget *currentWidget)
{
    ((gcn::Window*)currentWidget)->setCaption(node->Attribute("caption"));
}

const char windowName[]="gcn::Window";
extern "C" const char* componentName()
{
    return &windowName[0];
}
