#include <guichan.hpp>
#include <gmodule.h>
#include "editorGui.hpp"
#include <iostream>
#include "plugin.hpp"
#include "gcebase.hpp"

#include "tinyxml.h"

// save iteration, stripping of all normal mouse listeners
// and deletion of self / all children

char s[256];
char* colourStr(gcn::Color c)
{
    sprintf(s,"%02x%02x%02x%02x",c.r,c.g,c.b,c.a);
    return s;
}


void gceBase::iterate(TiXmlElement *parent)
{
    static GList *nlist;
    static Plugin *plug;

    currentWidget=this;

    TiXmlElement * node = new TiXmlElement("widget");

    nlist=g_list_first(Plugins);
    do
    {
        plug=(Plugin*)nlist->data;
        if (plug->mCurrentIsThisType())
        {
            if (plug->mCurrentIsThisType()) break;
        }
    } while ( (nlist=g_list_next(nlist))!=NULL );
    node->SetAttribute("type",plug->mComponentName());
    parent->LinkEndChild(node);
        // set base property widgets
    node->SetAttribute("x",currentWidget->getX());
    node->SetAttribute("y",currentWidget->getY());
    node->SetAttribute("width",currentWidget->getWidth());
    node->SetAttribute("height",currentWidget->getHeight());
    
    node->SetAttribute("bordersize",currentWidget->getFrameSize());
    node->SetAttribute("basecolour",colourStr(currentWidget->getBaseColor()));
    node->SetAttribute("backgroundcolour",colourStr(currentWidget->getBackgroundColor()));
    node->SetAttribute("foregroundcolour",colourStr(currentWidget->getForegroundColor()));
    node->SetAttribute("selectioncolour",colourStr(currentWidget->getSelectionColor()));
    node->SetAttribute("actioneventid",currentWidget->getActionEventId().c_str());
    node->SetAttribute("widgetid",currentWidget->getId().c_str());
    
    
    plug->mExportNodeExtended(node);

    if (plug->mCanParent())
    {
        WidgetListIterator iter;
        for (iter = mWidgets.begin(); iter != mWidgets.end(); iter++)
        {
            currentWidget=(*iter);
            if (currentWidget!=this)
            {
                nlist=g_list_first(Plugins);
                do
                {
                    plug=(Plugin*)nlist->data;
                    if (plug->mCurrentIsThisType())
                    {
                        ((gceBase*)currentWidget)->iterate(node);
                    }
                } while ( (nlist=g_list_next(nlist))!=NULL );
            }
        }
    }

}
    
void gceBase::emptyMouseListeners()
{
    mMouseListeners.clear();
}

void gceBase::deleteChildren()
{
    static GList *nlist;
    static Plugin *plug;

    currentWidget=this;
    
    nlist=g_list_first(Plugins);
    do
    {
        plug=(Plugin*)nlist->data;
        if (plug->mCurrentIsThisType()) break;
    } while ( (nlist=g_list_next(nlist))!=NULL );

    if (plug->mCanParent())
    {
        WidgetListIterator iter;
        for (iter = mWidgets.begin(); iter != mWidgets.end(); iter++)
        {
            currentWidget=(*iter);
            nlist=g_list_first(Plugins);
            do
            {
                plug=(Plugin*)nlist->data;
                if (plug->mCurrentIsThisType())
                {
                    ((gceBase*)currentWidget)->deleteChildren();
                }
            } while ( (nlist=g_list_next(nlist))!=NULL );
        }
    }
    if ((gcn::Container*)this!=top) widgetsToDelete.push_back(this);
}
