#include "LevelManager.h"
LevelManager::LevelManager():m_currentScene(NULL)
{
}

LevelManager::~LevelManager()
{
}


bool LevelManager::init()
{
    m_currentScene = new SceneOne();
    m_currentScene->setupScene();
    Ogre::Root::getSingleton().addFrameListener(this);
    Ogre::Root::getSingleton().renderOneFrame();
    return true;
}

bool LevelManager::frameEnded(const Ogre::FrameEvent& evt)
{
    InputHandler::getSingleton().capture();
    Ogre::WindowEventUtilities::messagePump();
    if(!InputHandler::getSingleton().getQuit())
        Ogre::Root::getSingleton().renderOneFrame();
    else
        return false;
    return true;
}


bool LevelManager::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
    m_currentScene->frameRenderingQueued(evt);
    return true;
}


bool LevelManager::keyPressed(const OIS::KeyEvent &keyEventRef)
{
    return true;
}


bool LevelManager::keyReleased(const OIS::KeyEvent &keyEventRef)
{
    return true;
}


bool LevelManager::mouseMoved(const OIS::MouseEvent &evt)
{
    return true;
}


bool LevelManager::mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
{
    return true;
}


bool LevelManager::mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
{
    return true;
}

