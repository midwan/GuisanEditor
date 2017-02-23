#include <guichan.hpp>
#include <typeinfo>
#include <gmodule.h>
#include "tinyxml.h"

extern "C" gcn::Widget *newInstance() // doesnt add to "top"
{
    gcn::TextBox *c=new gcn::TextBox();
    return c;
}
extern "C" gboolean canParent()
{
    return false;
}

extern "C" void setExtendedFromNode(TiXmlElement *node)
{

}

const char tbName[]="gcn::TextBox";
extern "C" const char* componentName()
{
    return &tbName[0];
}
