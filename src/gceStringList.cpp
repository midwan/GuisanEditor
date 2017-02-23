
#include <iostream>
#include <guichan.hpp>
#include <glib.h>
#include "gceStringList.hpp"

  // TODO consider using g_string instead of std::string

gceStringList::gceStringList() 
{
    mList=NULL;
}

gceStringList::~gceStringList()
{
    clearList();
}


int gceStringList::getNumberOfElements() {
    return g_list_length(mList);
}

std::string gceStringList::getElementAt(int i)
{

//if (i>=(int)g_list_length(mList)) return std::string("---");
    return std::string( ((std::string*)g_list_nth_data(mList,i))->c_str() );
}

void gceStringList::addString(std::string s)
{

    std::string *ns=new std::string(s); // make a new copy for the list
    mList=g_list_append(mList,ns);
}

void gceStringList::insertString(std::string s, int pos)
{
// TODO!!
}

void gceStringList::removeString(int pos)
{
// TODO!!
}

void gceStringList::clearList() {
    GList *nlist;
	nlist=g_list_first(mList);
	do 
	{
	    std::string *s=(std::string*)nlist->data; 
        delete s;
	} while ( (nlist=g_list_next(nlist))!=NULL );
	g_list_free(mList);
    mList=NULL;
}
