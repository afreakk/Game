#pragma once
#include "SceneOne.h"
#include "OISEvents.h"
#include "OISMouse.h"
#include "OISKeyboard.h"
#include "OgreFrameListener.h"
#include "input.h"
class LevelManager: public OIS::KeyListener, public OIS::MouseListener, public Ogre::FrameListener
{
    public:
        LevelManager();
        ~LevelManager();
        bool init();

        //OGREEvents
        bool frameEnded(const Ogre::FrameEvent& evt);
        bool frameRenderingQueued(const Ogre::FrameEvent& evt);

        //OISEvents
        bool keyPressed(const OIS::KeyEvent &keyEventRef);
        bool keyReleased(const OIS::KeyEvent &keyEventRef);
        bool mouseMoved(const OIS::MouseEvent &evt);
        bool mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id); 
        bool mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id);

    private:
        BaseScene* m_currentScene;

};
