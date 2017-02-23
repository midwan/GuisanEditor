
#ifndef GCE_COLOURSELECT_HPP
#define GCE_COLOURSELECT_HPP

#include <guichan.hpp>



class gceColourSelector :
    public gcn::Button, 
    public gcn::ActionListener
{
    private:
        gcn::Color      mCol;
        gcn::Color      mColTemp;
        gcn::Slider*    mRed;
        gcn::Slider*    mGreen;
        gcn::Slider*    mBlue;
        gcn::Slider*    mAlpha;
        gcn::Button*    mOkButt;
        gcn::Container* mCsPane;

	public:
        std::string     mActionId;
        gceColourSelector();
        gcn::Color getSelectedColour();
        void setSelectedColour(gcn::Color c);
        void action(const gcn::ActionEvent& actionEvent);	
};
 
#endif // end GCE_COLOURSELECT_HPP
