
#ifndef GCE_FILEDIALOG_HPP
#define GCE_FILEDIALOG_HPP

#include <guichan.hpp>
#include <glib.h>
#include "gceStringList.hpp"

typedef void (*fdCallback)(std::string);
        
class gceFileDialog :
    public gcn::ActionListener
{
    private:
        gcn::Window     *fdWin;
        gcn::ListBox    *fileList;
        gcn::ListBox    *dirList;
        gceStringList   *dirs;
        gceStringList   *files;
        gcn::ScrollArea *fArea;
        gcn::ScrollArea *dArea;
        gcn::Button     *fdQuitButton;
        gcn::Button     *fdCancelButton;
        gcn::TextField  *namebox;

        gchar           *mStartPath; 
        
        fdCallback    mCallback;
                
        void fillDir();
                
  public:
        gceFileDialog(fdCallback);
        ~gceFileDialog();
        std::string getFile();
        void action(const gcn::ActionEvent& actionEvent);  

};
 
#endif // end GCE_FILEDIALOG_HPP
