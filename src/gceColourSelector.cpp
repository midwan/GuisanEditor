#include <iostream>
#include <guichan.hpp>
#include "gceColourSelector.hpp"
#include "editorGui.hpp"
#include <vector>

gceColourSelector::gceColourSelector()
{
    // TODO I *really* shouldnt be playing fast and loose with
    // the eventID......
    addActionListener(this);
    setActionEventId("openColourSelector");
    setCaption("  ");
    adjustSize();
    mColTemp=mCol;
}


void gceColourSelector::action(const gcn::ActionEvent& actionEvent)
{
//    std::cout << "cs action listener: " << actionEvent.getId() << std::endl;
    
    if (actionEvent.getId() == "openColourSelector") 
    {
        if (currentWidget!=NULL)
        {
            //TODO add range checking and repositioning for main container
            mCsPane=new gcn::Container();
            mCsPane->setSize(148,96);
            mCsPane->setFrameSize(2);
            int x,y;
            getAbsolutePosition(x,y);
            top->add(mCsPane,0,0);
            mCsPane->setPosition(x+(getWidth()/2)-76,y+(getHeight()/2)-50);
            mOkButt=new gcn::Button("OK");
            mOkButt->adjustSize();
            mOkButt->addActionListener(this);
            mOkButt->setActionEventId("ColourSelected");
            mCsPane->add(mOkButt,8,8);
            
            mRed=new gcn::Slider(255);
            mRed->setSize(130, 10);
            mRed->setActionEventId("Red");
            mRed->addActionListener(this);
            mRed->setValue(mCol.r);
            mCsPane->add(mRed,8,36);
            
            mGreen=new gcn::Slider(255);
            mGreen->setSize(130, 10);
            mGreen->setActionEventId("Green");
            mGreen->addActionListener(this);
            mGreen->setValue(mCol.g);
            mCsPane->add(mGreen,8,48);
            
            mBlue=new gcn::Slider(255);
            mBlue->setSize(130, 10);
            mBlue->setActionEventId("Blue");
            mBlue->addActionListener(this);
            mBlue->setValue(mCol.b);
            mCsPane->add(mBlue,8,60);            
             
            mAlpha=new gcn::Slider(255);
            mAlpha->setSize(130, 10);
            mAlpha->setActionEventId("Alpha");
            mAlpha->addActionListener(this);
            mAlpha->setValue(mCol.a);
            mCsPane->add(mAlpha,8,72);
            
        }
        
    }

    if (actionEvent.getId() == "Red") 
    {
        mColTemp.r=(int)mRed->getValue();
        mCsPane->setBaseColor(mColTemp);
    }
    
    if (actionEvent.getId() == "Green") 
    {
        mColTemp.g=(int)mGreen->getValue();
        mCsPane->setBaseColor(mColTemp);
    }
    
    if (actionEvent.getId() == "Blue") 
    {
        mColTemp.b=(int)mBlue->getValue();
        mCsPane->setBaseColor(mColTemp);
    }
    
    if (actionEvent.getId() == "Alpha") 
    {
        mColTemp.a=(int)mAlpha->getValue();
        mCsPane->setBaseColor(mColTemp);
    }
    
    if (actionEvent.getId() == "ColourSelected") 
    
    {
        mCol=mColTemp;
        setBaseColor(mCol);
        setActionEventId(mActionId);  // this is the users close event id... (kludge!)
        distributeActionEvent();
        setActionEventId("openColourSelector");
                
        widgetsToDelete.push_back(mCsPane);
        widgetsToDelete.push_back(mOkButt);
        widgetsToDelete.push_back(mAlpha);
        widgetsToDelete.push_back(mRed);
        widgetsToDelete.push_back(mGreen);
        widgetsToDelete.push_back(mBlue);
    }
    

}

gcn::Color gceColourSelector::getSelectedColour()
{
    return mCol;
}


void gceColourSelector::setSelectedColour(gcn::Color c)
{
    mCol=c;
    mColTemp=c;
    setBaseColor(mCol);
}
