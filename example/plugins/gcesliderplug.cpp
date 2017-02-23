#include <guichan.hpp>
#include <typeinfo>
#include <gmodule.h>
#include "tinyxml.h"

extern "C" gboolean canParent()
{
    return false;    // does the component maintain its own mWidgets list
}

extern "C" gcn::Widget *newInstance() // doesnt add to "top"
{
    gcn::Slider *c=new gcn::Slider();
    return c;
}

extern "C" void setExtendedFromNode(TiXmlElement *node, gcn::Widget *currentWidget)
{
    ((gcn::Slider*)currentWidget)->setMarkerLength(atoi(node->Attribute("markerLength")));
    if (strcmp("true",node->Attribute("vertical"))==0)
    {
        ((gcn::Slider*)currentWidget)->setOrientation(gcn::Slider::VERTICAL);
    } else {
        ((gcn::Slider*)currentWidget)->setOrientation(gcn::Slider::HORIZONTAL);
    }
    ((gcn::Slider*)currentWidget)->setScaleStart(atof(node->Attribute("scaleStart")));
    ((gcn::Slider*)currentWidget)->setScaleEnd(atof(node->Attribute("scaleEnd")));
    ((gcn::Slider*)currentWidget)->setStepLength(atof(node->Attribute("stepLength")));
}

const char slName[]="gcn::Slider";
extern "C" const char* componentName()
{
    return &slName[0];
}

