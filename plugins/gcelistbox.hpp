
#ifndef GCE_LISTBOX_HPP
#define GCE_LISTBOX_HPP

class gceListBox : public gcn::ListBox
{
	public:
    gceListBox(gcn::ListModel *lm);
	void draw(gcn::Graphics* g);
	
}; 

#endif // end GCE_LISTBOX_HPP
