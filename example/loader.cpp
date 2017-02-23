#include "plugin.hpp"
#include <iostream>
#include "loader.hpp"
#include "dummyListModel.hpp"

Plugin::~Plugin() 
{
    if (!g_module_close (mModule))
        std::cout << "couldn't close plugin " << std::endl;
}

Plugin::Plugin(const char *PluginName) 
{
    mError=false;
    mModule=g_module_open(PluginName, G_MODULE_BIND_LAZY);
    if (!mModule)
    {
        std::cout << "couldn't open plugin " << PluginName << "  error: " << g_module_error() << std::endl;
        mError=true;
    } 
    else 
    {
        // TODO issue warning for a specific function when bailing
        //!g_module_symbol (mModule, "currentIsThisType", (gpointer *)&mCurrentIsThisType) ||
              
        if (  !g_module_symbol (mModule, "componentName", (gpointer *)&mComponentName) ||
              !g_module_symbol (mModule, "canParent", (gpointer *)&mCanParent) ||
              !g_module_symbol (mModule, "newInstance", (gpointer *)&mNewInstance) ||
              !g_module_symbol (mModule, "setExtendedFromNode", (gpointer *)&mSetExtendedFromNode)
           )
        {
            std::cout << "couldn't find a function " << std::endl;
            
            if (!g_module_close (mModule))
                std::cout << "couldn't close plugin " << std::endl;
            mError=true;
        }
        else
        {
            //mCurrentIsThisType == NULL ||
            if (
                mComponentName == NULL||
                mCanParent == NULL||
                mNewInstance == NULL||
                mSetExtendedFromNode == NULL
               )
            {
                std::cout << "null function pointer " << std::endl;

                if (!g_module_close (mModule))
                    std::cout << "couldn't close plugin " << std::endl;
                mError=true;
            }  //endif function null
        } //endelse function found
    } //endelse cant open module
}
    


GList *Plugins;


void initialisePlugs()
{
    // search for and load plugins 
    GDir *dir=g_dir_open(PLUG_DIR,0,NULL);
    const gchar *file;

    while ( (file=g_dir_read_name(dir))!=NULL )
    {
        if ( g_str_has_suffix(file,".plug") )
        {
            gchar *full=g_strconcat (PLUG_DIR,file,NULL);
            Plugin *plug=new Plugin(full);
            delete full;
            if (plug->mError) 
            {
                std::cout << file << " aborted" << std::endl;
            } else {
                Plugins=g_list_append(Plugins,plug);
                std::cout << plug->mComponentName() << " component loaded. " << std::endl;
            }
        }
    }    
}

void free_all_plugins()
{
    GList *nlist;
    nlist=g_list_first(Plugins);
    do 
    {
        Plugin *plug=(Plugin*)nlist->data;
        delete plug;
    } while ( (nlist=g_list_next(nlist))!=NULL );
    g_list_free(Plugins);
}


int DummyListModel::getNumberOfElements()
{
    return 10;
}

std::string DummyListModel::getElementAt(int i)
{
    return mStrings[i];
}

DummyListModel::DummyListModel()
{
    mStrings[0]=std::string("zero");
    mStrings[1]=std::string("one");
    mStrings[2]=std::string("two");
    mStrings[3]=std::string("three");
    mStrings[4]=std::string("four");
    mStrings[5]=std::string("five");
    mStrings[6]=std::string("six");
    mStrings[7]=std::string("seven");
    mStrings[8]=std::string("eight");
    mStrings[9]=std::string("nine");
}

DummyListModel::~DummyListModel()
{

}

DummyListModel dlm;

gcn::Container *loadGui(const char* filename)
{
//    ((gceBase*)top)->deleteChildren();
    gcn::Container *top;
    TiXmlDocument doc(filename);
    if (doc.LoadFile())
    {
        TiXmlElement* root=doc.FirstChildElement();
        TiXmlElement* topNode=root->FirstChildElement();   // valid save will only have one node in the root the "top" widget
        top=(gcn::Container*)makeFromNode(topNode);
        iterateXml((gcn::Widget*)top,topNode->FirstChildElement()); // the parent widget and first child xml node.
    }
    return top;
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



gcn::Widget* makeFromNode(TiXmlElement* node) 
{
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

    w->setActionEventId("aid");
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
    w->setFrameSize(i);
    
    w->setActionEventId(node->Attribute("actioneventid"));
    w->setId(node->Attribute("widgetid"));
    
//    currentWidget=w;
    plug->mSetExtendedFromNode(node,w);
    return w;
}

void iterateXml(gcn::Widget* p,TiXmlElement *node)
{
    if (node==NULL) return;
//    std::cout << node->Attribute("type") << std::endl;
    TiXmlElement *pnode=node;
    for( pnode; pnode!=NULL; pnode=pnode->NextSiblingElement())
    {
        gcn::Widget* w=makeFromNode(pnode);


        if (dynamic_cast<gcn::ScrollArea*>(p))
        {
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
                    if (plug->mCanParent()) iterateXml((gcn::Widget*)w,pnode->FirstChildElement());
                    break;
                }
            } while ( (nlist=g_list_next(nlist))!=NULL );
        }
    }
}

