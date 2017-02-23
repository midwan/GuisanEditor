#include <guichan.hpp>
#include <typeinfo>
#include <gmodule.h>

#include "guichan/image.hpp"
#include "tinyxml.h"

extern "C" gcn::Widget *newInstance() // doesnt add to "top"
{
    gcn::Image *i=gcn::Image::load("broken.bmp");
    gcn::Icon *c=new gcn::Icon(i);
   return c;
}

extern "C" gboolean canParent()
{
    return false;   // getting this wrong will crash editor on save or delete
}

// this is so we can access the private member mImage!!
class gceIcon : public gcn::Icon {
    public:
    void setIconImage(const char* filename)
    {
        delete mImage;
        mImage=NULL;
        try
        {
            mImage=gcn::Image::load(filename);
        }
        catch (gcn::Exception e)
        {
            mImage=gcn::Image::load("broken.bmp");
        }
        
    }
};

extern "C" void setExtendedFromNode(TiXmlElement *node, gcn::Widget *currentWidget)
{
    const char *str=(const char *)node->Attribute("imageFileName");
    ((gceIcon*)currentWidget)->setIconImage(str);
}

const char containerName[]="gcn::Icon";
extern "C" const char* componentName()
{
    return &containerName[0];
}
