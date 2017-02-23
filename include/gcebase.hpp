

// TODO work out why I can't use this as base of gceWidgets....
#include "tinyxml.h"

class gceBase : public gcn::BasicContainer
{
    public:
        void iterate(TiXmlElement *parent);
        void emptyMouseListeners();
        void exportNodeExtended(TiXmlElement *node);
        void deleteChildren();
};
