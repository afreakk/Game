#include "SceneOne.h"
SceneOne::SceneOne():m_fmgr(NULL),m_cameraMan(NULL)
{
    m_sceneID= "SceneOne";
}
 
SceneOne::~SceneOne()
{

}

bool SceneOne::setupScene()
{
	m_sceneMgr->createLight("Light")->setPosition(75,75,75);
    m_fmgr = new FloorManager(m_sceneMgr,40,40,100.0f);
    m_fmgr->init(1000.0);
    m_cameraMan = new mom::SdkCameraMan(m_camera);
    InputHandler::getSingleton().addMouseListener(m_cameraMan, "CameraMan");
    InputHandler::getSingleton().addKeyListener(m_cameraMan, "CameraMan");
    return true;
}
 
const std::string& SceneOne::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
    m_cameraMan->frameRenderingQueued(evt);
    return m_sceneID;
}
