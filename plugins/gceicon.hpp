
#ifndef GCE_ICON_HPP
#define GCE_ICON_HPP

#include "guichan/image.hpp"

class gceIcon : public gcn::Icon
{
    private:
        char   mFileName[256];
	public:
        gceIcon(gcn::Image* image);

        void draw(gcn::Graphics* g);
        const gcn::Image* getIconImage();
        void setIconImage(const char* filename);
        char* getFileName();
}; 

#endif 
