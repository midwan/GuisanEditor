
#include <guichan.hpp>

#include "gceicon.hpp"
#include "editorGui.hpp"

#include "guichan/image.hpp"

void gceIcon::draw(gcn::Graphics* g)
{
    Icon::draw(g);


//    g->drawImage(mImage,0,0,0,0,w,h);
    
    if (currentWidget==this)
    {
        g->setColor(gcn::Color(255,0,0,128));
        g->fillRectangle(gcn::Rectangle(0,0,12,12));
        int w=getWidth();
        int h=getHeight();
        g->fillRectangle(gcn::Rectangle(w-12,h-12,w,h));
    }
}


// gosh! some actual implementation!!!
gceIcon::gceIcon(gcn::Image* image) : gcn::Icon(image)
{
    mFileName[0]=0;
}


const gcn::Image* gceIcon::getIconImage()
{
    return mImage;
}

void gceIcon::setIconImage(const char* filename)
{
    delete mImage;
    mImage=NULL;
    try
    {
        mImage=gcn::Image::load(filename);
        strcpy(&mFileName[0], filename);
    }
    catch (gcn::Exception e)
    {
        mFileName[0]=0;
        mImage=gcn::Image::load("images/broken.bmp");
    }
    
}


char* gceIcon::getFileName()
{
    return &mFileName[0];
}

