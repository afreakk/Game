#include "input.h"
#include "OgreStringConverter.h"
#include "simulation.h"

void linuxNoStickyMouse(OIS::ParamList & paramList)
{
#if defined OIS_LINUX_PLATFORM
    paramList.insert(std::make_pair(std::string("x11_mouse_grab"), std::string("false")));
    paramList.insert(std::make_pair(std::string("x11_mouse_hide"), std::string("false")));
    paramList.insert(std::make_pair(std::string("x11_keyboard_grab"), std::string("false")));
    paramList.insert(std::make_pair(std::string("XAutoRepeatOn"), std::string("true")));
#endif
}

template<> InputHandler* Ogre::Singleton<InputHandler>::msSingleton = 0;

InputHandler::InputHandler(unsigned long hWnd, InputFlags flags):m_mouse(NULL),m_keyboard(NULL),m_quit(NULL)
{
	OIS::ParamList pl;
    //linuxNoStickyMouse(pl);
	pl.insert(OIS::ParamList::value_type("WINDOW", Ogre::StringConverter::toString(hWnd)));
	m_hWnd = hWnd;
	m_ois = OIS::InputManager::createInputSystem( pl );
    switch (flags)
    {
        case USE_MOUSE+USE_KEYBOARD:
            m_mouse = static_cast<OIS::Mouse*>(m_ois->createInputObject( OIS::OISMouse, true ));
            m_mouse->setEventCallback(this);
            m_keyboard = static_cast<OIS::Keyboard*>(m_ois->createInputObject( OIS::OISKeyboard, true));
            m_keyboard->setEventCallback(this);
            break;
        case USE_MOUSE:
            m_mouse = static_cast<OIS::Mouse*>(m_ois->createInputObject( OIS::OISMouse, true ));
            m_mouse->setEventCallback(this);
            break;
        case USE_KEYBOARD:
            m_keyboard = static_cast<OIS::Keyboard*>(m_ois->createInputObject( OIS::OISKeyboard, true));
            m_keyboard->setEventCallback(this);
            break;
    }
}


InputHandler::~InputHandler() 
{
    if(m_mouse)
        m_ois->destroyInputObject(m_mouse);
    if(m_keyboard) 
        m_ois->destroyInputObject(m_keyboard);
    m_ois->destroyInputSystem( m_ois );
}

void InputHandler::capture() 
{
    if(m_mouse)
    	m_mouse->capture();
    if(m_keyboard)
    	m_keyboard->capture();
}

void  InputHandler::setWindowExtents(int width, int height)
{
	//Set Mouse Region.. if window resizes, we should alter this to reflect as well
	const OIS::MouseState &ms = m_mouse->getMouseState();
	ms.width = width;
	ms.height = height;
}


bool InputHandler::mouseMoved(const OIS::MouseEvent &evt) 
{
    for(std::map<std::string, BaseController*>::iterator listeners=m_mouseListeners.begin(); listeners !=m_mouseListeners.end(); ++listeners)
        listeners->second->mouseMoved(evt);
    return true;
}

bool InputHandler::mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID btn) 
{
    for(std::map<std::string, BaseController*>::iterator listeners=m_mouseListeners.begin(); listeners !=m_mouseListeners.end(); ++listeners)
        listeners->second->mousePressed(evt,btn);
    return true;

}

bool InputHandler::mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID btn) 
{
    for(std::map<std::string, BaseController*>::iterator listeners=m_mouseListeners.begin(); listeners !=m_mouseListeners.end(); ++listeners)
        listeners->second->mouseReleased(evt,btn);
    return true;
	
}

		
bool InputHandler::keyPressed(const OIS::KeyEvent &evt) 
{
    for(std::map<std::string, BaseController*>::iterator listeners=m_keyListeners.begin(); listeners !=m_keyListeners.end(); ++listeners)
        listeners->second->keyPressed(evt);
	unsigned int ch = evt.text;
    return true;
    
}

bool InputHandler::keyReleased(const OIS::KeyEvent &evt) 
{
    for(std::map<std::string, BaseController*>::iterator listeners=m_keyListeners.begin(); listeners !=m_keyListeners.end(); ++listeners)
        listeners->second->keyReleased(evt);
	if (evt.key == OIS::KC_ESCAPE)
        m_quit = true;
    return true;

}


bool InputHandler::getQuit()
{
    return m_quit;
}



void InputHandler::setQuit(bool val)
{
    m_quit = val;
}


void InputHandler::addMouseListener(BaseController* mouseListener, std::string name)
{
    m_mouseListeners[name] = mouseListener;
}
void InputHandler::addKeyListener(BaseController* keyListener, std::string name)
{
    m_keyListeners[name] = keyListener;
}
void InputHandler::removeMouseListener(std::string name)
{
    m_mouseListeners.erase(name);
}
void InputHandler::removeKeyListener(std::string name)
{
    m_keyListeners.erase(name);
}
