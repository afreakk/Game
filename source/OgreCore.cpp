#include "OgreCore.h"
template<> OgreCore* Ogre::Singleton<OgreCore>::msSingleton = 0;

OgreCore::OgreCore():m_root(NULL), m_window(NULL), m_sceneMgr(NULL), m_camera(NULL),m_viewport(NULL)
{
}
OgreCore::~OgreCore()
{
    delete m_root;
}

bool OgreCore::initRoot()
{
	//Clearing the first two (of three) params will let us specify plugins and resources in code instead of via text file
	m_root = new Ogre::Root("", "");

	m_root->loadPlugin("/usr/lib64/OGRE/RenderSystem_GL");
    Ogre::RenderSystemList::const_iterator r_it;

    r_it = m_root->getAvailableRenderers().begin();
    m_root->setRenderSystem(*r_it);
    m_root->initialise(false);

	m_root->loadPlugin("/usr/lib64/OGRE/Plugin_CgProgramManager");		
	m_root->loadPlugin("/usr/lib64/OGRE/Plugin_OctreeSceneManager");
}

bool OgreCore::initResources()
{
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation(	"resource", "FileSystem", "General");
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation("resource/gui.zip", "Zip", "GUI");
	Ogre::ResourceGroupManager::getSingleton().initialiseResourceGroup("General");
	Ogre::ResourceGroupManager::getSingleton().initialiseResourceGroup("GUI");
}

bool OgreCore::initWindow(const int xResolution, const int yResolution, const Ogre::String renderWindowName)
{
    resolution.x = xResolution;
    resolution.y = yResolution;
	Ogre::NameValuePairList opts;
	opts["fullscreen"] = "false";
	opts["title"] = "www";
	opts["vsync"] = "false";
	m_window = m_root->createRenderWindow(renderWindowName, resolution.x, resolution.y, false, &opts);
}

bool OgreCore::initSceneManager()
{
	m_sceneMgr = m_root->createSceneManager(Ogre::ST_GENERIC);
}

bool OgreCore::initCamera(const Ogre::String cameraName)
{
	m_camera = m_sceneMgr->createCamera(cameraName);
	m_camera->setNearClipDistance(5);
    m_viewport = m_window->addViewport(m_camera);
    m_viewport->setBackgroundColour(Ogre::ColourValue(0.02,0.01,0.1));
	m_camera->setAspectRatio( m_viewport->getWidth() / m_viewport->getHeight() );
}
//gets
Ogre::RenderWindow* OgreCore::getWindow(){
    return m_window;
}
Ogre::Root* OgreCore::getRoot(){
    return m_root;
}
Ogre::SceneManager* OgreCore::getSceneMgr(){
    return m_sceneMgr;
}
Ogre::Camera*       OgreCore::getCamera(){
    return m_camera;
}
Ogre::Viewport*     OgreCore::getViewport(){
    return m_viewport;
}
