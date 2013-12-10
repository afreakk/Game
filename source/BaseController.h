
#ifndef BASECONTROLLER_H
#define BASECONTROLLER_H
#include "OISEvents.h"
#include "OISMouse.h"
#include "OISKeyboard.h"
class BaseController 
{
public:
    virtual void keyPressed(const OIS::KeyEvent &keyEventRef){};
    virtual void keyReleased(const OIS::KeyEvent &keyEventRef){};
    virtual void mouseMoved(const OIS::MouseEvent &evt){};
    virtual void mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id){}; 
    virtual void mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id){};
};
 
#endif 
