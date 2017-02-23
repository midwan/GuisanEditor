#include <iostream>

#include <guichan.hpp>
#include "actionlistener.hpp"
#include "editorGui.hpp"
#include "gceFileDialog.hpp"

#include <gmodule.h>
#include "plugin.hpp"

void saveGui(std::string filename);
void loadGui(std::string filename);

extern bool parentMode;
extern bool deleteMode;
gceActionListener guiListener;

void gceActionListener::action(const gcn::ActionEvent& actionEvent)
{
//    std::cout << "gui listener : " << actionEvent.getId() << std::endl;
    if (actionEvent.getId() == "sheetSelector")
    {
        int i=sheetSelector->getSelected();
        gcn::Container* sel;
        switch(i)
        {
            case 0:
                sel=global;
                break;
            case 1:
                sel=components;
                break;
            case 2:
                sel=standard;
                break;
            case 3:
                sel=extended;
                if (currentWidget)
                {
                    GList *nlist;
                    nlist=g_list_first(Plugins);
                    bool isP=false;
                    do 
                    {
                        Plugin *plug=(Plugin*)nlist->data;
    
                        if (plug->mCurrentIsThisType())
                        {
                            plug->mUpdateExtendedProperties();
                            break;
                        }
            
                    } while ( (nlist=g_list_next(nlist))!=NULL );
                }
                break;
        }
        mainWindow->remove(lastSelected);
        mainWindow->add(sel, 0, 32);
        lastSelected=sel;

    }
    
    if (actionEvent.getId() == "borderSize" && currentWidget!=NULL)
    {
        char s[256];
        int i=(int)borderSize->getValue();
        sprintf(s,"Border Size : %i",i);
        borderSizeLabel->setCaption(s);
        currentWidget->setFrameSize(i);
    }
    
    if (actionEvent.getId() == "baseColour" && currentWidget!=NULL)
            currentWidget->setBaseColor(baseColour->getSelectedColour());
    
    if (actionEvent.getId() == "backgroundColour" && currentWidget!=NULL)
            currentWidget->setBackgroundColor(backgroundColour->getSelectedColour());

    if (actionEvent.getId() == "foregroundColour" && currentWidget!=NULL)
            currentWidget->setForegroundColor(foregroundColour->getSelectedColour());

    if (actionEvent.getId() == "selectionColour" && currentWidget!=NULL)
            currentWidget->setSelectionColor(selectionColour->getSelectedColour());

    if (actionEvent.getId() == "actionEventId" && currentWidget!=NULL)
        currentWidget->setActionEventId(actionEventId->getText());
    
    if (actionEvent.getId() == "widgetId" && currentWidget!=NULL)
        currentWidget->setId(widgetId->getText());
    
    if (actionEvent.getId() == "toBack" && currentWidget!=NULL)
            currentWidget->requestMoveToBottom();
    
    if (actionEvent.getId() == "toFront" && currentWidget!=NULL)
            currentWidget->requestMoveToTop();
    
    
    if (actionEvent.getId() == "parent") 
    {
        if (parentMode==true)
        {
            parentMode=false;
            parent->setCaption("Parent");
            return;
        }

        parentMode=true;
        parent->setCaption("CLICK!");
    }

    
    if (actionEvent.getId() == "delete") 
    {
        if (deleteMode==true)
        {
            deleteMode=false;
            del->setCaption("Delete Widget");
            return;
        }

        deleteMode=true;
        del->setCaption("CLICK!");
    }

    if (actionEvent.getId() == "parentTop") 
    {
        parentMode=false;
        ((gcn::Container*)currentWidget->getParent())->remove(currentWidget);
        top->add(currentWidget,16,16);
    }

    
    if (actionEvent.getId() == "save") gceFileDialog *fd=new gceFileDialog(saveGui);
    
    if (actionEvent.getId() == "load") gceFileDialog *fd=new gceFileDialog(loadGui);
    
}

