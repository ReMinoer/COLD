/*
-----------------------------------------------------------------------------
Filename:    BaseApplication.h
-----------------------------------------------------------------------------

This source file is part of the
   ___                 __    __ _ _    _ 
  /___\__ _ _ __ ___  / / /\ \ (_) | _(_)
 //  // _` | '__/ _ \ \ \/  \/ / | |/ / |
/ \_// (_| | | |  __/  \  /\  /| |   <| |
\___/ \__, |_|  \___|   \/  \/ |_|_|\_\_|
      |___/                              
      Tutorial Framework
      http://www.ogre3d.org/tikiwiki/
-----------------------------------------------------------------------------
This file has been modified by F. Lamarche for the purpose of the Video game course
-----------------------------------------------------------------------------

*/
#ifndef __BaseApplication_h_
#define __BaseApplication_h_

#include <OGRE/OgreCamera.h>
#include <OGRE/OgreEntity.h>
#include <OGRE/OgreLogManager.h>
#include <OGRE/OgreRoot.h>
#include <OGRE/OgreViewport.h>
#include <OGRE/OgreSceneManager.h>
#include <OGRE/OgreRenderWindow.h>
#include <OGRE/OgreConfigFile.h>

#include <OIS/OISEvents.h>
#include <OIS/OISInputManager.h>
#include <OIS/OISKeyboard.h>
#include <OIS/OISMouse.h>

#include <OGRE/SdkTrays.h>
#include <OGRE/SdkCameraMan.h>


namespace OgreFramework
{
	class BaseApplication : public Ogre::FrameListener, public Ogre::WindowEventListener, public OIS::KeyListener, public OIS::MouseListener, OgreBites::SdkTrayListener
	{
	public:
		BaseApplication(void);
		virtual ~BaseApplication(void);

		virtual void go(void);


	protected:
		virtual void update(Ogre::Real dt) = 0 ;

		virtual bool setup();
		virtual bool configure(void);
		virtual void chooseSceneManager(void);
		virtual void createCamera(void);
		virtual void createFrameListener(void);
		virtual void createScene(void) = 0; // Override me!
		virtual void destroyScene(void);
		virtual void createViewports(void);
		virtual void setupResources(void);
		virtual void createResourceListener(void);
		virtual void loadResources(void);

		// Ogre::FrameListener
		virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);

		// OIS::KeyListener
		virtual bool keyPressed( const OIS::KeyEvent &arg );
		virtual bool keyReleased( const OIS::KeyEvent &arg );
		// OIS::MouseListener
		virtual bool mouseMoved( const OIS::MouseEvent &arg );
		virtual bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
		virtual bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );

		// Ogre::WindowEventListener
		//Adjust mouse clipping area
		virtual void windowResized(Ogre::RenderWindow* rw);
		//Unattach OIS before window shutdown (very important under Linux)
		virtual void windowClosed(Ogre::RenderWindow* rw);

		Ogre::Root *m_rootNode;
		Ogre::Camera* m_camera;
		Ogre::SceneManager* m_sceneManager;
		Ogre::RenderWindow* m_window;
		Ogre::String m_ressourcesConfiguration;
		Ogre::String m_pluginsConfiguration;

		// OgreBites
		OgreBites::SdkTrayManager* m_trayManager;
		//OgreBites::SdkCameraMan* m_cameraManager;       // basic camera controller
		OgreBites::ParamsPanel* m_detailsPanel;     // sample details panel
		bool m_cursorWasVisible;                    // was cursor visible before dialog appeared
		bool m_shutDown;

		//OIS Input devices
		OIS::InputManager* m_inputManager;
		OIS::Mouse*    m_mouse;
		OIS::Keyboard* m_keyboard;
	};
}

#endif // #ifndef __BaseApplication_h_
