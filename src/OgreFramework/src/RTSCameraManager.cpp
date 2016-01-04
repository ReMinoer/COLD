#include <stdafx.h>

#include <OgreFramework/RTSCameraManager.h>

namespace OgreFramework
{


	RTSCameraManager::RTSCameraManager( Ogre::SceneManager * sceneManager,  Ogre::Camera* camera, KeyboardState * keyboardState ) : m_keyboardState(keyboardState)
	{
		m_cameraControlSystem = new CCS::CameraControlSystem(sceneManager, "Camera control system", camera) ;
		m_cameraMode = new CCS::RTSCameraMode(m_cameraControlSystem, Ogre::Vector3(0.0, 0.0, 5.0), Ogre::Vector3::UNIT_Y, Ogre::Vector3::NEGATIVE_UNIT_X, Ogre::Radian(Ogre::Degree(0)), -100, 50000) ;
		m_cameraControlSystem->setCurrentCameraMode(m_cameraMode) ;
		setDefaultKeyConfig() ;
		m_cameraMode->setMoveFactor(50) ;
	}

	RTSCameraManager::~RTSCameraManager()
	{
		delete m_cameraControlSystem ;
		delete m_cameraMode ;
	}

	void RTSCameraManager::setDefaultKeyConfig()
	{
		m_configuration[key_up] = OIS::KC_UP ;
		m_configuration[key_down] = OIS::KC_DOWN ;
		m_configuration[key_left] = OIS::KC_LEFT ;
		m_configuration[key_right] = OIS::KC_RIGHT ;
		m_configuration[key_zoomIn] = OIS::KC_PGUP ;
		m_configuration[key_zoomOut] = OIS::KC_PGDOWN ;
	}

	void RTSCameraManager::setControlKey( ControlKey controlKey, OIS::KeyCode key )
	{
		m_configuration[controlKey] = key ;
	}

	void RTSCameraManager::update( Ogre::Real dt )
	{
		// Updates camera mode accordingly to keyboard state
		if(m_keyboardState->isDown(OIS::KC_UP)) m_cameraMode->goUp(dt) ;
		if(m_keyboardState->isDown(OIS::KC_DOWN)) m_cameraMode->goDown(dt) ;
		if(m_keyboardState->isDown(OIS::KC_LEFT)) m_cameraMode->goLeft(dt) ;
		if(m_keyboardState->isDown(OIS::KC_RIGHT)) m_cameraMode->goRight(dt) ;
		if(m_keyboardState->isDown(OIS::KC_PGUP)) m_cameraMode->zoomIn(dt) ;
		if(m_keyboardState->isDown(OIS::KC_PGDOWN)) m_cameraMode->zoomOut(dt) ;
		// Updates camera control system 
		m_cameraControlSystem->update(dt) ;
	}
}