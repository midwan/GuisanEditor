#include <guichan.hpp>
#include <typeinfo>
#include <gmodule.h>
#include "tinyxml.h"

extern "C" gcn::Widget *newInstance() // doesnt add to "top"
{
    gcn::Container *c=new gcn::Container();
    return c;
}

extern "C" gboolean canParent()
{
    return true;
}

extern "C" void setExtendedFromNode(TiXmlElement *node, gcn::Widget *currentWidget)
{

}

const char containerName[]="gcn::Container";
extern "C" const char* componentName()
{
    return &containerName[0];
}
