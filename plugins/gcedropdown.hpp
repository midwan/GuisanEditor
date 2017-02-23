
#ifndef GCE_DROPDOWN_HPP
#define GCE_DROPDOWN_HPP

class gceDropDown : public gcn::DropDown 
{
	public:
    gceDropDown(gcn::ListModel *lm = NULL,gcn::ScrollArea *sa = NULL,gcn::ListBox *lb = NULL);
	void draw(gcn::Graphics* g);
	
}; 

#endif // end GCE_DROPDOWN_HPP
