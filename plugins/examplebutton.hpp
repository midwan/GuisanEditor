
#ifndef EXAMPLEBUTTON_HPP
#define EXAMPLEBUTTON_HPP

#include <guichan.hpp>

class exampleButton : public gcn::Button
{
    public:
        void draw(gcn::Graphics *g);
        static void loadThemeImage(std::string filename);
//    protected:

};

#endif // end EXAMPLEBUTTON_HPP

