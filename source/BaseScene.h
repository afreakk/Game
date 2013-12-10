#ifndef BASESCENE_H
#define BASESCENE_H
#include "OISEvents.h"
#include "OISMouse.h"
#include "OISKeyboard.h"
#include "Ogre.h" 
class BaseScene 
{
public:
    BaseScene();
    ~BaseScene();
    std::string getID();
	virtual bool setupScene()=0;
    virtual const std::string& frameRenderingQueued(const Ogre::FrameEvent& evt)=0;
protected:
    std::string         m_sceneID;
	Ogre::SceneManager* m_sceneMgr;
	Ogre::RenderWindow* m_renderWnd;
	Ogre::Viewport*		m_viewport;
	Ogre::Camera*       m_camera;
};
 
#endif 
