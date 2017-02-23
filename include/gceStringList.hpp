
#ifndef GCE_LIST_HPP
#define GCE_LIST_HPP

class gceStringList : public gcn::ListModel 
{
    public:
    gceStringList();
    ~gceStringList();
    int getNumberOfElements();
    std::string getElementAt(int i);
    void addString(std::string s);
    void insertString(std::string s, int pos);
    void removeString(int pos);	
    void clearList();

    GList *mList;
}; 

#endif // end GCE_LIST_HPP
