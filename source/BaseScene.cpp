#include "BaseScene.h"
#include "OgreCore.h"
BaseScene::BaseScene():m_sceneID("NONE")
{
    OgreCore& core = OgreCore::getSingleton();
    m_sceneMgr = core.getSceneMgr();
    m_renderWnd = core.getWindow();
    m_viewport = core.getViewport();
    m_camera = core.getCamera();
}
BaseScene::~BaseScene()
{

}

std::string BaseScene::getID()
{
    return m_sceneID; 
}

