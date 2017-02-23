#include <guichan.hpp>
#include <typeinfo>
#include <gmodule.h>
#include "tinyxml.h"

// TODO add scroll bar policy settings etc in extended properties sheet
// see editor plugin
extern "C" gcn::Widget *newInstance() // doesnt add to "top"
{
    gcn::ScrollArea *c=new gcn::ScrollArea();
    return c;
}

extern "C" gboolean canParent()
{
    return true;    // a special case in the loader....
}

extern "C" void setExtendedFromNode(TiXmlElement *node)
{

}

const char scrollName[]="gcn::ScrollArea";
extern "C" const char* componentName()
{
    return &scrollName[0];
}
