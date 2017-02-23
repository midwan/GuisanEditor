#include <iostream>
#include <guichan.hpp>
#include <gmodule.h>

#include "mouselistener.hpp"

#include "editorGui.hpp"
#include "plugin.hpp"
#include "gcebase.hpp"

GlobalMouseListener MListener;
	
bool parentMode=false;
bool deleteMode=false;

gcn::Widget *oldCurrent;
   
void GlobalMouseListener::mousePressed(gcn::MouseEvent& mouseEvent)
{
    //TODO there is a problem moving scroll areas with a child
        
    timesClicked++;

    oldCurrent=currentWidget;
    currentWidget=mouseEvent.getSource();
    mx=mouseEvent.getX();
    my=mouseEvent.getY();
    int w,h;
    w=currentWidget->getWidth();
    h=currentWidget->getHeight();
    
	GList *nlist;
	nlist=g_list_first(Plugins);
    bool isP=false;
	do 
	{
	    Plugin *plug=(Plugin*)nlist->data;

	    if (plug->mCurrentIsThisType())
	    {
	        plug->mUpdateExtendedProperties();
            if (parentMode) isP=plug->mCanParent();
            break;
	    }
        
	} while ( (nlist=g_list_next(nlist))!=NULL );
    
    if (parentMode)
    {
        if (isP) 
        {
            // TODO boo hiss I didnt want to do a special case here
            // investigate alternitave! (should be handled some how
            // by the plugin...)
            if (dynamic_cast<gcn::ScrollArea*>(currentWidget))
            {
                ((gcn::Container*)oldCurrent->getParent())->remove(oldCurrent);
                gcn::Widget *t=((gcn::ScrollArea*)currentWidget)->getContent();
                ((gcn::ScrollArea*)currentWidget)->setContent(oldCurrent);
                if (t) {
                    top->add(t,16,16);
                }

            } else {
                gcn::Container *c=(gcn::Container*)currentWidget;
                ((gcn::Container*)oldCurrent->getParent())->remove(oldCurrent);
                c->add(oldCurrent,16,16);  // TODO range check parent size and half old position repeatedly??
            }
            parentMode=false;
            parent->setCaption("Parent");
            return; 
        }   
        
    }

    if (deleteMode)
    {
        if (currentWidget!=top) 
        {
            gceBase *c=(gceBase*)currentWidget;
            c->deleteChildren();

            deleteMode=false;
            del->setCaption("DeleteWidget");
            
            currentWidget=NULL;
            return; 
        }   
        
    }

    if(currentWidget!=top)
    {
        if (mouseEvent.getX() < 12)
        {
            if (mouseEvent.getY() < 12)
            {
                isDrag=true;
            }
        }
            
        if (mouseEvent.getX() > w-12)
        {
            if (mouseEvent.getY() > h-12)
            {
                isResize=true;
            }
        }
    }    
    updateBaseProperties();
}

extern int drags;
void GlobalMouseListener::mouseDragged(gcn::MouseEvent& mouseEvent)
{  
    
    gcn::Widget *wid=mouseEvent.getSource();

    int x,y,w,h,b,th;
    w=wid->getWidth();
    h=wid->getHeight();
    x=wid->getX();
    y=wid->getY();
    gcn::Widget *p=wid->getParent();
    b=(int)p->getFrameSize();
    th=0;
    if (typeid(*p) == typeid(gcn::Window)) th=((gcn::Window*)p)->getTitleBarHeight();

    if (isDrag)
    {
        x=x+(mouseEvent.getX()-mx);
		y=y+(mouseEvent.getY()-my);
//		if (x < 0) x=0;
//		if (y < 0) y=0;
//		if (x > p->getWidth()-(w+b*2)-1) x=p->getWidth()-(w+b*2)-1;
//		if (y > p->getHeight()-(h+b*2)-(1+th)) y=p->getHeight()-(h+b*2)-(1+th);
        wid->setPosition(x,y);
        if(p!=top) // errm not sure whats happening here...!
        {
            mx=mouseEvent.getX();
            my=mouseEvent.getY();
        }
        mouseEvent.consume();
    }
    
    if (isResize)
    {
        w=w+(mouseEvent.getX()-mx);
		h=h+(mouseEvent.getY()-my);
//        if (w > p->getWidth()-(x+b*2)-1) w=p->getWidth()-(x+b*2)-1;
//        if (h > p->getHeight()-(y+b*2)-(1+th)) h=p->getHeight()-(y+b*2)-(1+th);
//        if (w<12) w=12;
//        if (h<12) h=12;
		wid->setWidth(w);
		wid->setHeight(h);
	    mx=mouseEvent.getX();
	    my=mouseEvent.getY();			    
        mouseEvent.consume();
    }
}


void GlobalMouseListener::mouseReleased(gcn::MouseEvent& mouseEvent)
{  
    isDrag=false;
    isResize=false;
}


void GlobalMouseListener::mouseClicked(gcn::MouseEvent& mouseEvent)
{  
//        std::cout << "Mouse clicked: " << mouseEvent.getX() << " " << mouseEvent.getY() << std::endl;
}

void GlobalMouseListener::mouseMoved(gcn::MouseEvent& mouseEvent)
{  
//        std::cout << "Mouse moved: " << mouseEvent.getX() << " " << mouseEvent.getY() << std::endl;
}

void GlobalMouseListener::mouseEntered(gcn::MouseEvent& mouseEvent)
{  
//        std::cout << "Mouse entered: " << mouseEvent.getX() << " " << mouseEvent.getY() << std::endl;
}

void GlobalMouseListener::mouseExited(gcn::MouseEvent& mouseEvent)
{  
//        std::cout << "Mouse exited: " << mouseEvent.getX() << " " << mouseEvent.getY() << std::endl;
}

void GlobalMouseListener::mouseWheelMovedDown(gcn::MouseEvent& mouseEvent)
{  
//        std::cout << "Mouse wheel down moved: " << mouseEvent.getX() << " " << mouseEvent.getY() << std::endl;
}

void GlobalMouseListener::mouseWheelMovedUp(gcn::MouseEvent& mouseEvent)
{  
//        std::cout << "Mouse wheel up moved: " << mouseEvent.getX() << " " << mouseEvent.getY() << std::endl;
}

