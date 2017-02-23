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
    gcn::CheckBox *c=new gcn::CheckBox();
    return c;
}

extern "C" void setExtendedFromNode(TiXmlElement *node, gcn::Widget *currentWidget)
{
    ((gcn::CheckBox*)currentWidget)->setCaption(node->Attribute("caption"));
    if (strcmp("true",node->Attribute("checked"))==0) 
    {
        ((gcn::CheckBox*)currentWidget)->setSelected(true);
    } else {
        ((gcn::CheckBox*)currentWidget)->setSelected(false);
    }
    
}

const char checkName[]="gcn::CheckBox";
extern "C" const char* componentName()
{
    return &checkName[0];
}

