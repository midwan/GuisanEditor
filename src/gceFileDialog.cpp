#include <iostream>
#include <guichan.hpp>
#include "gceFileDialog.hpp"
#include "editorGui.hpp"
#include "gcebase.hpp"

#include <glib.h>
#include <glib/gstdio.h>

gceFileDialog::gceFileDialog(fdCallback cbFunction)
{
    mCallback=cbFunction;
    mStartPath=g_get_current_dir ();

    fdWin=new gcn::Window();
    fdWin->setPosition(top->getWidth()/2-200,top->getHeight()/2-180);
    fdWin->setSize(400,360);
    fdQuitButton=new gcn::Button("OK");
    fdWin->add(fdQuitButton,10,10);
    fdQuitButton->setActionEventId("ok");
    fdQuitButton->addActionListener(this);
    
    fdCancelButton=new gcn::Button("Cancel");
    fdWin->add(fdCancelButton,100,10);
    fdCancelButton->setActionEventId("cancel");
    fdCancelButton->addActionListener(this);
    
    fArea=new gcn::ScrollArea();
    fArea->setPosition(210,48);
    fArea->setSize(175,252);
    fdWin->add(fArea);

    dArea=new gcn::ScrollArea();
    dArea->setPosition(10,48);
    dArea->setSize(175,252);
    fdWin->add(dArea);
        
    dirs=new gceStringList();
    files=new gceStringList();
    
    fileList=new gcn::ListBox(files);
    fileList->setActionEventId("fileclicked");
    fileList->addActionListener(this);
    
    dirList=new gcn::ListBox(dirs);
    dirList->setActionEventId("dirclicked");
    dirList->addActionListener(this);
        
    namebox=new gcn::TextField();
    namebox->setPosition(10,310);
    namebox->setSize(160,20);
    fdWin->add(namebox);

    top->add(fdWin);
    fillDir();   
     
    fArea->setContent(fileList);
    dArea->setContent(dirList);   
}

gceFileDialog::~gceFileDialog() 
{

}

void gceFileDialog::action(const gcn::ActionEvent& actionEvent)
{
    std::cout << "fd action listener: " << actionEvent.getId() << std::endl;
    
    if (actionEvent.getId() == "ok" || actionEvent.getId()=="cancel") 
    {
        if (actionEvent.getId() == "ok") {
          mCallback(namebox->getText());
        }
        g_chdir(mStartPath);
        delete mStartPath; 

        widgetsToDelete.push_back(fileList);
        widgetsToDelete.push_back(dirList);
        widgetsToDelete.push_back(fArea);
        widgetsToDelete.push_back(dArea);
        widgetsToDelete.push_back(fdQuitButton);
        widgetsToDelete.push_back(fdCancelButton);
        widgetsToDelete.push_back(namebox);
        widgetsToDelete.push_back((gceBase*)dirs);
        widgetsToDelete.push_back((gceBase*)files);        
        widgetsToDelete.push_back(fdWin); 

        widgetsToDelete.push_back((gceBase*)this);  
    }
    
    if (actionEvent.getId() == "fileclicked") 
    {
      int i=fileList->getSelected();
      namebox->setText(files->getElementAt(i).c_str());
    }


    if (actionEvent.getId() == "dirclicked") 
    {
      int i=dirList->getSelected();        
      g_chdir (dirs->getElementAt(i).c_str());
      dirs->clearList();
      files->clearList();

      fillDir();
    }        

}


static gint sortFileList(const std::string *a, const std::string *b) {

	return a->compare(b->c_str());
	
}


void gceFileDialog::fillDir() 
{
        
  dirs->addString("..");
  GDir* d=g_dir_open (".",0,NULL);
  if (d) {
    const gchar* fname;

    char fwidest[1024];
    char dwidest[1024];
    unsigned int dw=0;
    unsigned int fw=0;

    while((fname=g_dir_read_name(d))) {
      if (g_file_test (fname,G_FILE_TEST_IS_DIR) ) {
        dirs->addString(fname);
        if (strlen(fname)>dw) {
          dw=strlen(fname);
          sprintf(dwidest,"%s",fname);
        }
      } else {
        files->addString(fname);
        if (strlen(fname)>fw) {
          fw=strlen(fname);
          sprintf(fwidest,"%s",fname);
        }
      }
    }

    fileList->setSize(fileList->getFont()->getWidth(fwidest)+4,files->getNumberOfElements()*fileList->getFont()->getHeight()); 
    dirList->setSize(dirList->getFont()->getWidth(dwidest)+4,dirs->getNumberOfElements()*dirList->getFont()->getHeight()); 



    g_dir_close (d);
  }
    
  files->mList = g_list_sort ( files->mList, (GCompareFunc)sortFileList );
  dirs->mList = g_list_sort ( dirs->mList, (GCompareFunc)sortFileList );

}

