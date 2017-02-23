#ifndef GCE_PLUGIN_HPP
#define GCE_PLUGIN_HPP

#define PLUG_DIR "./plugins/"

#include <guichan.hpp>
#include <gmodule.h>
#include "../tinyxml/tinyxml.h"

// plugin prototypes
typedef gcn::Widget* (*newInstance)();
typedef gboolean (*canParent)();
typedef gboolean (*currentIsThisType)();
typedef void (*setExtendedFromNode)(TiXmlElement *node, gcn::Widget *currentWidget);
typedef char* (*componentName)();

class Plugin {
    GModule *mModule;

    public:

    currentIsThisType mCurrentIsThisType;
    canParent mCanParent;
    componentName mComponentName;
    newInstance mNewInstance;
    setExtendedFromNode mSetExtendedFromNode;
    gboolean mError;

    ~Plugin();
    Plugin(const char *PluginName);
};

extern GList *Plugins;

#endif

