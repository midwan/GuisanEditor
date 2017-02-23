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
    gcn::RadioButton *c=new gcn::RadioButton();
    return c;
}

extern "C" void setExtendedFromNode(TiXmlElement *node,gcn::Widget *currentWidget)
{
    ((gcn::RadioButton*)currentWidget)->setCaption(node->Attribute("caption"));
    ((gcn::RadioButton*)currentWidget)->setGroup(node->Attribute("group"));
    if (strcmp("true",node->Attribute("checked"))==0) 
    {
        ((gcn::RadioButton*)currentWidget)->setSelected(true);
    } else {
        ((gcn::RadioButton*)currentWidget)->setSelected(false);
    }
    
}

const char radioName[]="gcn::RadioButton";
extern "C" const char* componentName()
{
    return &radioName[0];
}

