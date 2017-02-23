#ifndef GCE_PLUGIN_HPP
#define GCE_PLUGIN_HPP

#define PLUG_DIR "./plugins/"

#include "tinyxml.h"

// plugin prototypes
typedef gcn::Button* (*initComponent)();
typedef gboolean (*currentIsThisType)();
typedef gboolean (*canParent)();
typedef void (*updateExtendedProperties)();
typedef char* (*componentName)();
typedef void (*exportNodeExtended)(TiXmlElement *node);
typedef gcn::Widget* (*newInstance)();
typedef void (*setExtendedFromNode)(TiXmlElement *node);

class Plugin {
    GModule *mModule;

    public:

    initComponent mInitComponent;
    currentIsThisType mCurrentIsThisType;
    canParent mCanParent;
    updateExtendedProperties mUpdateExtendedProperties;
    componentName mComponentName;
    exportNodeExtended mExportNodeExtended;
    newInstance mNewInstance;
    setExtendedFromNode mSetExtendedFromNode;
    gboolean mError;

    ~Plugin();
    Plugin(const char *PluginName);
};

extern GList *Plugins;

#endif

