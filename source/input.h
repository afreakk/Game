#pragma once

///
//
enum InputFlags
{
    USE_MOUSE = 1,
    USE_KEYBOARD =2,
};

inline InputFlags operator|(InputFlags a, InputFlags b)
{return static_cast<InputFlags>(static_cast<int>(a) | static_cast<int>(b));}

//////
//

#include "OISEvents.h"
#include "OISInputManager.h"
#include "OISMouse.h"
#include "OISKeyboard.h"
#include "BaseController.h"
#include <OgreSingleton.h>
#include <map>
class InputHandler : public OIS::MouseListener, public OIS::KeyListener, public Ogre::Singleton<InputHandler>
{
private:
	OIS::InputManager *m_ois;
	OIS::Mouse      *m_mouse;
	OIS::Keyboard*m_keyboard;
	unsigned long     m_hWnd;
    bool              m_quit;
    std::map<std::string, BaseController*>    m_mouseListeners;
    std::map<std::string, BaseController*>      m_keyListeners;

public:
    bool getQuit();
    void setQuit(bool val);

    void addMouseListener(BaseController* mouseListener, std::string name);
    void addKeyListener(BaseController* keyListener, std::string name);
    void removeMouseListener(std::string name);
    void removeKeyListener(std::string name);

	InputHandler(unsigned long hWnd, InputFlags flags); 
	~InputHandler();

	void setWindowExtents(int width, int height) ;
	void capture();
	
	bool mouseMoved(const OIS::MouseEvent &evt);
	bool mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID);
	bool mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID);
	
	bool keyPressed(const OIS::KeyEvent &evt);
	bool keyReleased(const OIS::KeyEvent &evt);
	
};

