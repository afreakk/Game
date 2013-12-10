#include "input.h"
 
#include "Ogre.h"
#include "OgreWindowEventUtilities.h"
#include "OgreCore.h"
#include "LevelManager.h"

#if defined(WIN32)
#include "windows.h"

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
#else
int main (int argc, char *argv[]) {
#endif

    OgreCore* ogreCore = NULL;
    LevelManager* lvlMgr= NULL;
    try
    {
        ogreCore = new OgreCore();
        ogreCore->initRoot();
        ogreCore->initResources();
        ogreCore->initWindow(1280,720,"MainWindow");
        ogreCore->initSceneManager();
        ogreCore->initCamera("MainCamera");
    }
    catch(Ogre::Exception& e)
    {
        std::cout << e.what() <<std::endl;
    }

	unsigned long hWnd;
	ogreCore->getWindow()->getCustomAttribute("WINDOW", &hWnd);
	InputHandler *handler = new InputHandler(hWnd,  USE_KEYBOARD|USE_MOUSE);

    lvlMgr = new LevelManager();
    lvlMgr->init();

    delete lvlMgr;
	delete handler;
    delete ogreCore;

	return 0;
}
