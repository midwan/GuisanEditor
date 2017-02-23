#include <guichan.hpp>
#include <typeinfo>
#include <gmodule.h>

#include "../dummyListModel.hpp"

#include "tinyxml.h"

extern DummyListModel dlm;

extern "C" gcn::Widget *newInstance() // doesnt add to "top"
{
    gcn::ListBox *c=new gcn::ListBox(&dlm);
    return c;
}
extern "C" gboolean canParent()
{
    return false;
}

extern "C" void setExtendedFromNode(TiXmlElement *node)
{

}

const char lbName[]="gcn::ListBox";
extern "C" const char* componentName()
{
    return &lbName[0];
}
