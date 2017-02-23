#include <guichan.hpp>
#include "dummyListModel.hpp"

int DummyListModel::getNumberOfElements()
{
    return 20;
}

std::string DummyListModel::getElementAt(int i)
{
//    if (i>9) return std::string("---");
    return mStrings[i];
}

DummyListModel::DummyListModel()
{
    mStrings[0]=std::string("zero");
    mStrings[1]=std::string("one");
    mStrings[2]=std::string("two");
    mStrings[3]=std::string("three");
    mStrings[4]=std::string("four");
    mStrings[5]=std::string("five");
    mStrings[6]=std::string("six");
    mStrings[7]=std::string("seven");
    mStrings[8]=std::string("eight");
    mStrings[9]=std::string("nine");
    mStrings[10]=std::string("zero");
    mStrings[11]=std::string("one");
    mStrings[12]=std::string("two");
    mStrings[13]=std::string("three");
    mStrings[14]=std::string("four");
    mStrings[15]=std::string("five");
    mStrings[16]=std::string("six");
    mStrings[17]=std::string("seven");
    mStrings[18]=std::string("eight");
    mStrings[19]=std::string("nine");
    /*    
    mStrings[20]=std::string("zero");
    mStrings[21]=std::string("one");
    mStrings[22]=std::string("two");
    mStrings[23]=std::string("three");
    mStrings[24]=std::string("four");
    mStrings[25]=std::string("five");
    mStrings[26]=std::string("six");
    mStrings[27]=std::string("seven");
    mStrings[28]=std::string("eight");
    mStrings[29]=std::string("nine");
    mStrings[30]=std::string("zero");
    mStrings[31]=std::string("one");
    mStrings[32]=std::string("two");
    mStrings[33]=std::string("three");
    mStrings[34]=std::string("four");
    mStrings[35]=std::string("five");
    mStrings[36]=std::string("six");
    mStrings[37]=std::string("seven");
    mStrings[38]=std::string("eight");
    mStrings[39]=std::string("nine");
    */ 
}

DummyListModel::~DummyListModel()
{

}

