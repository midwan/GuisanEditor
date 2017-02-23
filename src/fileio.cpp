#include <gmodule.h>
#include <guichan.hpp>
#include "editorGui.hpp"
#include "gcebase.hpp"
#include "plugin.hpp"
#include "tinyxml.h"


void saveGui(std::string filename)
{

    TiXmlDocument doc;  

    TiXmlDeclaration* decl = new TiXmlDeclaration( "1.0", "ascii", "" );
    doc.LinkEndChild( decl ); 
 
    TiXmlElement * root = new TiXmlElement("GUI");
    doc.LinkEndChild( root );

    gceBase *t=(gceBase*)top;
    t->iterate(root);
    currentWidget=NULL;

    doc.SaveFile(filename.c_str());
}

gcn::Color strToColour(const char* s)
{
    gcn::Color c;
    char d[]="\0\0\0";
    // example c3d9ffff
    d[0]=s[0];
    d[1]=s[1];
    c.r=strtol(d,NULL,16);

    d[0]=s[2];
    d[1]=s[3];
    c.g=strtol(d,NULL,16);

    d[0]=s[4];
    d[1]=s[5];
    c.b=strtol(d,NULL,16);

    d[0]=s[6];
    d[1]=s[7];
    c.a=strtol(d,NULL,16);

    return c;
}


gcn::Widget* makeFromNode(TiXmlElement* node) {
    GList *nlist;
    Plugin *plug;
    gcn::Widget* w;
    nlist=g_list_first(Plugins);
    do
    {
        plug=(Plugin*)nlist->data;
        if (strcmp(plug->mComponentName(),node->Attribute("type"))==0)
        {
            w=plug->mNewInstance();
            break;
        }
    } while ( (nlist=g_list_next(nlist))!=NULL );
    int i;

//    std::cout << node->Attribute("widgetid") << std::endl;    
        // set base property widgets
    w->setBaseColor(strToColour(node->Attribute("basecolour")));
    w->setBackgroundColor(strToColour(node->Attribute("backgroundcolour")));
    w->setForegroundColor(strToColour(node->Attribute("foregroundcolour")));
    w->setSelectionColor(strToColour(node->Attribute("selectioncolour")));
    
    node->QueryIntAttribute("x",&i);
    w->setX(i);
    node->QueryIntAttribute("y",&i);
    w->setY(i);
    node->QueryIntAttribute("width",&i);
    w->setWidth(i);
    node->QueryIntAttribute("height",&i);
    w->setHeight(i);
    node->QueryIntAttribute("bordersize",&i);
//    w->setBorderSize(i);
    w->setFrameSize(i);

    w->setActionEventId(node->Attribute("actioneventid"));
    w->setId(node->Attribute("widgetid"));
    
    currentWidget=w;
    plug->mSetExtendedFromNode(node);
    return w;
}

void iterateXml(gcn::Widget* p,TiXmlElement *node)
{

    if (node==NULL) return;

    TiXmlElement *pnode=node;
    for( pnode; pnode!=NULL; pnode=pnode->NextSiblingElement())
    {
        gcn::Widget* w=makeFromNode(pnode);

        if (dynamic_cast<gcn::ScrollArea*>(p))
        {
//            std::cout << "setting as contents of scroll area" << std::endl;
            ((gcn::ScrollArea*)p)->setContent(w);
        } else {
            ((gcn::Container*)p)->add(w);
        }

        // check if perentable if it is do iterateXml(w,pnode)

        GList *nlist;
        Plugin *plug;
        nlist=g_list_first(Plugins);
        
        if (pnode->FirstChildElement()!=NULL)
        {
            do
            {
                
                plug=(Plugin*)nlist->data;
                if (strcmp(plug->mComponentName(),pnode->Attribute("type"))==0)
                {
                    if (plug->mCanParent()) iterateXml((gcn::Container*)w,pnode->FirstChildElement());
                    break;
                }
            } while ( (nlist=g_list_next(nlist))!=NULL );
        }
    }
}

void loadGui(std::string filename)
{
    ((gceBase*)top)->deleteChildren();
    //TiXmlDocument doc("output.xml");
	TiXmlDocument doc(filename.c_str());


    if (doc.LoadFile())
    {
        TiXmlElement* root=doc.FirstChildElement();
        TiXmlElement* topNode=root->FirstChildElement();   // valid save will only have one node in the root the "top" widget
        iterateXml(top,topNode->FirstChildElement()); // the parent widget and first child xml node.
    }
    currentWidget=NULL;
}

