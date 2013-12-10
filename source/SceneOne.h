#ifndef SCENEONE_H
#define SCENEONE_H
#include "BaseScene.h"
#include "FloorManager.h"
#include "CameraMan.h"
#include "input.h"
class SceneOne : public BaseScene
{
public:
	SceneOne();
	~SceneOne();
	bool setupScene();
    const std::string& frameRenderingQueued(const Ogre::FrameEvent& evt);
    void keyPressed(const OIS::KeyEvent &keyEventRef);
    void keyReleased(const OIS::KeyEvent &keyEventRef);
    void mouseMoved(const OIS::MouseEvent &evt);
    void mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id); 
    void mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id);
private:
//////
    FloorManager* m_fmgr;
    mom::SdkCameraMan* m_cameraMan;
};
 
#endif 
