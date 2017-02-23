
#include <guichan.hpp>
#include "examplebutton.hpp"

extern "C" gcn::Image  *mImage;
static gcn::Color  mCC;
static gcn::Color  mCCD;


void exampleButton::loadThemeImage(std::string filename)
{

    mImage=gcn::Image::load(filename);
    mCC=mImage->getPixel(8,8);
    mCCD=mImage->getPixel(25,8);
    // TODO need a delete on app close type routine
    // cant do in distructor as these are used globaly by all instances
}


void exampleButton::draw(gcn::Graphics* g)
{


    gcn::Color centreColour;
    int srcX=0;

    if (isPressed())
    {
        srcX=17;
        centreColour=mCCD;
    }
    else
    {
        centreColour=mCC;
    }

    g->setColor(centreColour);
    g->fillRectangle(gcn::Rectangle(8, 8, getWidth()-16, getHeight() - 16));
    g->drawImage(mImage,0+srcX,0,0,0,8,8);
    g->drawImage(mImage,9+srcX,0,getWidth()-8,0,8,8);
    g->drawImage(mImage,0+srcX,9,0,getHeight()-8,8,8);
    g->drawImage(mImage,9+srcX,9,getWidth()-8,getHeight()-8,8,8);

    for (int i=0;i<(getWidth()-16);i++)
    {
        g->drawImage(mImage,8+srcX,0,8+i,0,1,8);
        g->drawImage(mImage,8+srcX,9,8+i,getHeight()-8,1,8);
    }
    for (int i=0;i<(getHeight()-16);i++)
    {
        g->drawImage(mImage,0+srcX,8,0,8+i,8,1);
        g->drawImage(mImage,9+srcX,8,getWidth()-8,8+i,8,1);
    }

    g->setColor(getForegroundColor());

    int textX;
    int textY = getHeight() / 2 - getFont()->getHeight() / 2;

    switch (getAlignment())
    {
        case gcn::Graphics::LEFT:
            textX = mSpacing;
            break;
        case gcn::Graphics::CENTER:
            textX = getWidth() / 2;
            break;
        case gcn::Graphics::RIGHT:
            textX = getWidth() - mSpacing;
            break;
        default:
            throw GCN_EXCEPTION("Unknown alignment.");
    }

    g->setFont(getFont());

    if (isPressed())
    {
        g->drawText(getCaption(), textX + 1, textY + 1, getAlignment());
    }
    else
    {
        g->drawText(getCaption(), textX, textY, getAlignment());

        if (isFocused())
        {
            g->drawRectangle(gcn::Rectangle(6, 6, getWidth() - 12,
                                                getHeight() - 12));
        }
    }

}




