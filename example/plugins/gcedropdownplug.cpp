#include <guichan.hpp>
#include <typeinfo>
#include <gmodule.h>
#include "tinyxml.h"

#include "../dummyListModel.hpp"



extern DummyListModel dlm;


extern "C" gcn::Widget *newInstance() // doesnt add to "top"
{
    gcn::DropDown *c=new gcn::DropDown(&dlm);
    return c;
}

extern "C" gboolean canParent()
{
    return false;
}

extern "C" void setExtendedFromNode(TiXmlElement *node, gcn::Widget *currentWidget)
{

}

const char dropdownName[]="gcn::DropDown";
extern "C" const char* componentName()
{
    return &dropdownName[0];
}
