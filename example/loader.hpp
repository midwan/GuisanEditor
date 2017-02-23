#include <guichan.hpp>
#include "../tinyxml/tinyxml.h"

void initialisePlugs();
void free_all_plugins();
gcn::Container* loadGui(const char* filename);
gcn::Color strToColour(const char* s);
gcn::Widget* makeFromNode(TiXmlElement* node);
void iterateXml(gcn::Widget* p,TiXmlElement *node);

