/*
-----------------------------------------------------------------------------
Filename:    BaseApplication.cpp
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
*/
#include <stdafx.h>


#include <OgreFramework/BaseApplication.h>

namespace OgreFramework
{
	//-------------------------------------------------------------------------------------
	BaseApplication::BaseApplication(void)
		: m_rootNode(0),
		m_camera(0),
		m_sceneManager(0),
		m_window(0),
		m_ressourcesConfiguration(Ogre::StringUtil::BLANK),
		m_pluginsConfiguration(Ogre::StringUtil::BLANK),
		m_trayManager(0),
		//m_cameraManager(0),
		m_detailsPanel(0),
		m_cursorWasVisible(false),
		m_shutDown(false),
		m_inputManager(0),
		m_mouse(0),
		m_keyboard(0)
	{
	}

	//-------------------------------------------------------------------------------------
	BaseApplication::~BaseApplication(void)
	{
		if (m_trayManager) delete m_trayManager;
		//if (m_cameraManager) delete m_cameraManager;

		//Remove ourself as a Window listener
		Ogre::WindowEventUtilities::removeWindowEventListener(m_window, this);
		windowClosed(m_window);
		delete m_rootNode;
	}

	//-------------------------------------------------------------------------------------
	bool BaseApplication::configure(void)
	{
		// Show the configuration dialog and initialise the system
		// You can skip this and use root.restoreConfig() to load configuration
		// settings if you were sure there are valid ones saved in ogre.cfg
		if(m_rootNode->showConfigDialog())
		{
			// If returned true, user clicked OK so initialise
			// Here we choose to let the system create a default rendering window by passing 'true'
			m_window = m_rootNode->initialise(true, "TutorialApplication Render Window");

			return true;
		}
		else
		{
			return false;
		}
	}
	//-------------------------------------------------------------------------------------
	void BaseApplication::chooseSceneManager(void)
	{
		// Get the SceneManager, in this case a generic one
		//m_sceneManager = m_rootNode->createSceneManager(Ogre::ST_GENERIC);
		m_sceneManager = m_rootNode->createSceneManager("OctreeSceneManager") ;
	}
	//-------------------------------------------------------------------------------------
	void BaseApplication::createCamera(void)
	{
		// Create the camera
		m_camera = m_sceneManager->createCamera("PlayerCam");

		// Position it at 500 in Z direction
		m_camera->setPosition(Ogre::Vector3(0,0,80));
		// Look back along -Z
		m_camera->lookAt(Ogre::Vector3(0,0,-300));
		m_camera->setNearClipDistance(5);

		//m_cameraManager = new OgreBites::SdkCameraMan(m_camera);   // create a default camera controller
	}
	//-------------------------------------------------------------------------------------
	void BaseApplication::createFrameListener(void)
	{
		Ogre::LogManager::getSingletonPtr()->logMessage("*** Initializing OIS ***");
		OIS::ParamList pl;
		size_t windowHnd = 0;
		std::ostringstream windowHndStr;

		m_window->getCustomAttribute("WINDOW", &windowHnd);
		windowHndStr << windowHnd;
		pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

		m_inputManager = OIS::InputManager::createInputSystem( pl );

		m_keyboard = static_cast<OIS::Keyboard*>(m_inputManager->createInputObject( OIS::OISKeyboard, true ));
		m_mouse = static_cast<OIS::Mouse*>(m_inputManager->createInputObject( OIS::OISMouse, true ));

		m_mouse->setEventCallback(this);
		m_keyboard->setEventCallback(this);

		//Set initial mouse clipping size
		windowResized(m_window);

		//Register as a Window listener
		Ogre::WindowEventUtilities::addWindowEventListener(m_window, this);

		m_trayManager = new OgreBites::SdkTrayManager("InterfaceName", m_window, m_mouse, this);
		m_trayManager->showFrameStats(OgreBites::TL_BOTTOMLEFT);
		m_trayManager->showLogo(OgreBites::TL_BOTTOMRIGHT);
		//m_trayManager->hideCursor();

		// create a params panel for displaying sample details
		Ogre::StringVector items;
		items.push_back("cam.pX");
		items.push_back("cam.pY");
		items.push_back("cam.pZ");
		items.push_back("");
		items.push_back("cam.oW");
		items.push_back("cam.oX");
		items.push_back("cam.oY");
		items.push_back("cam.oZ");
		items.push_back("");
		items.push_back("Filtering");
		items.push_back("Poly Mode");

		m_detailsPanel = m_trayManager->createParamsPanel(OgreBites::TL_NONE, "DetailsPanel", 200, items);
		m_detailsPanel->setParamValue(9, "Bilinear");
		m_detailsPanel->setParamValue(10, "Solid");
		m_detailsPanel->hide();

		m_rootNode->addFrameListener(this);
	}
	//-------------------------------------------------------------------------------------
	void BaseApplication::destroyScene(void)
	{
	}
	//-------------------------------------------------------------------------------------
	void BaseApplication::createViewports(void)
	{
		// Create one viewport, entire window
		Ogre::Viewport* vp = m_window->addViewport(m_camera);
		vp->setBackgroundColour(Ogre::ColourValue(0,0,0));

		// Alter the camera aspect ratio to match the viewport
		m_camera->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
	}
	//-------------------------------------------------------------------------------------
	void BaseApplication::setupResources(void)
	{
		// Load resource paths from config file
		Ogre::ConfigFile cf;
		cf.load(m_ressourcesConfiguration);

		// Go through all sections & settings in the file
		Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();

		Ogre::String secName, typeName, archName;
		while (seci.hasMoreElements())
		{
			secName = seci.peekNextKey();
			Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
			Ogre::ConfigFile::SettingsMultiMap::iterator i;
			for (i = settings->begin(); i != settings->end(); ++i)
			{
				typeName = i->first;
				archName = i->second;
				Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
					archName, typeName, secName);
			}
		}
	}
	//-------------------------------------------------------------------------------------
	void BaseApplication::createResourceListener(void)
	{

	}
	//-------------------------------------------------------------------------------------
	void BaseApplication::loadResources(void)
	{
		Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
	}
	//-------------------------------------------------------------------------------------
	void BaseApplication::go(void)
	{
#ifdef _DEBUG
		m_ressourcesConfiguration = "../data/resources_d.cfg";
		m_pluginsConfiguration = "../data/plugins_d.cfg";
#else
		m_ressourcesConfiguration = "../data/resources.cfg";
		m_pluginsConfiguration = "../data/plugins.cfg";
#endif

		if (!setup())
			return;

		m_rootNode->startRendering();

		// clean up
		destroyScene();
	}
	//-------------------------------------------------------------------------------------
	bool BaseApplication::setup(void)
	{
		m_rootNode = new Ogre::Root(m_pluginsConfiguration);

		setupResources();

		bool carryOn = configure();
		if (!carryOn) return false;

		chooseSceneManager();
		createCamera();
		createViewports();

		// Set default mipmap level (NB some APIs ignore this)
		Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);

		// Create any resource listeners (for loading screens)
		createResourceListener();
		// Load resources
		loadResources();

		createFrameListener();

		// Create the scene
		createScene();

		return true;
	};
	//-------------------------------------------------------------------------------------
	bool BaseApplication::frameRenderingQueued(const Ogre::FrameEvent& evt)
	{
		if(m_window->isClosed())
			return false;

		if(m_shutDown)
			return false;

		//Need to capture/update each device
		m_keyboard->capture();
		m_mouse->capture();

		m_trayManager->frameRenderingQueued(evt);

		if (!m_trayManager->isDialogVisible())
		{
			//m_cameraManager->frameRenderingQueued(evt);   // if dialog isn't up, then update the camera
			if (m_detailsPanel->isVisible())   // if details panel is visible, then update its contents
			{
				m_detailsPanel->setParamValue(0, Ogre::StringConverter::toString(m_camera->getDerivedPosition().x));
				m_detailsPanel->setParamValue(1, Ogre::StringConverter::toString(m_camera->getDerivedPosition().y));
				m_detailsPanel->setParamValue(2, Ogre::StringConverter::toString(m_camera->getDerivedPosition().z));
				m_detailsPanel->setParamValue(4, Ogre::StringConverter::toString(m_camera->getDerivedOrientation().w));
				m_detailsPanel->setParamValue(5, Ogre::StringConverter::toString(m_camera->getDerivedOrientation().x));
				m_detailsPanel->setParamValue(6, Ogre::StringConverter::toString(m_camera->getDerivedOrientation().y));
				m_detailsPanel->setParamValue(7, Ogre::StringConverter::toString(m_camera->getDerivedOrientation().z));
			}
		}

		update(evt.timeSinceLastFrame) ;

		return true;
	}
	//-------------------------------------------------------------------------------------
	bool BaseApplication::keyPressed( const OIS::KeyEvent &arg )
	{
		if (m_trayManager->isDialogVisible()) return true;   // don't process any more keys if dialog is up

		if (arg.key == OIS::KC_F)   // toggle visibility of advanced frame stats
		{
			m_trayManager->toggleAdvancedFrameStats();
		}
		else if (arg.key == OIS::KC_G)   // toggle visibility of even rarer debugging details
		{
			if (m_detailsPanel->getTrayLocation() == OgreBites::TL_NONE)
			{
				m_trayManager->moveWidgetToTray(m_detailsPanel, OgreBites::TL_TOPRIGHT, 0);
				m_detailsPanel->show();
			}
			else
			{
				m_trayManager->removeWidgetFromTray(m_detailsPanel);
				m_detailsPanel->hide();
			}
		}
		else if (arg.key == OIS::KC_T)   // cycle polygon rendering mode
		{
			Ogre::String newVal;
			Ogre::TextureFilterOptions tfo;
			unsigned int aniso;

			switch (m_detailsPanel->getParamValue(9).asUTF8()[0])
			{
			case 'B':
				newVal = "Trilinear";
				tfo = Ogre::TFO_TRILINEAR;
				aniso = 1;
				break;
			case 'T':
				newVal = "Anisotropic";
				tfo = Ogre::TFO_ANISOTROPIC;
				aniso = 8;
				break;
			case 'A':
				newVal = "None";
				tfo = Ogre::TFO_NONE;
				aniso = 1;
				break;
			default:
				newVal = "Bilinear";
				tfo = Ogre::TFO_BILINEAR;
				aniso = 1;
			}

			Ogre::MaterialManager::getSingleton().setDefaultTextureFiltering(tfo);
			Ogre::MaterialManager::getSingleton().setDefaultAnisotropy(aniso);
			m_detailsPanel->setParamValue(9, newVal);
		}
		else if (arg.key == OIS::KC_R)   // cycle polygon rendering mode
		{
			Ogre::String newVal;
			Ogre::PolygonMode pm;

			switch (m_camera->getPolygonMode())
			{
			case Ogre::PM_SOLID:
				newVal = "Wireframe";
				pm = Ogre::PM_WIREFRAME;
				break;
			case Ogre::PM_WIREFRAME:
				newVal = "Points";
				pm = Ogre::PM_POINTS;
				break;
			default:
				newVal = "Solid";
				pm = Ogre::PM_SOLID;
			}

			m_camera->setPolygonMode(pm);
			m_detailsPanel->setParamValue(10, newVal);
		}
		else if(arg.key == OIS::KC_F5)   // refresh all textures
		{
			Ogre::TextureManager::getSingleton().reloadAll();
		}
		else if (arg.key == OIS::KC_SYSRQ)   // take a screenshot
		{
			m_window->writeContentsToTimestampedFile("screenshot", ".jpg");
		}
		else if (arg.key == OIS::KC_ESCAPE)
		{
			m_shutDown = true;
		}

		//m_cameraManager->injectKeyDown(arg);
		return true;
	}

	bool BaseApplication::keyReleased( const OIS::KeyEvent &arg )
	{
		//m_cameraManager->injectKeyUp(arg);
		return true;
	}

	bool BaseApplication::mouseMoved( const OIS::MouseEvent &arg )
	{
		if (m_trayManager->injectMouseMove(arg)) return true;
		//m_cameraManager->injectMouseMove(arg);
		return true;
	}

	bool BaseApplication::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
	{
		if (m_trayManager->injectMouseDown(arg, id)) return true;
		//m_cameraManager->injectMouseDown(arg, id);
		return true;
	}

	bool BaseApplication::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
	{
		if (m_trayManager->injectMouseUp(arg, id)) return true;
		//m_cameraManager->injectMouseUp(arg, id);
		return true;
	}

	//Adjust mouse clipping area
	void BaseApplication::windowResized(Ogre::RenderWindow* rw)
	{
		unsigned int width, height, depth;
		int left, top;
		rw->getMetrics(width, height, depth, left, top);

		const OIS::MouseState &ms = m_mouse->getMouseState();
		ms.width = width;
		ms.height = height;
	}

	//Unattach OIS before window shutdown (very important under Linux)
	void BaseApplication::windowClosed(Ogre::RenderWindow* rw)
	{
		//Only close for window that created OIS (the main window in these demos)
		if( rw == m_window )
		{
			if( m_inputManager )
			{
				m_inputManager->destroyInputObject( m_mouse );
				m_inputManager->destroyInputObject( m_keyboard );

				OIS::InputManager::destroyInputSystem(m_inputManager);
				m_inputManager = 0;
			}
		}
	}
}
