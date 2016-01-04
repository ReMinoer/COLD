#ifndef _OgreFramework_H
#define _OgreFramework_H

#include <Config/Real.h>
#include <Math/Vector3.h>
#include <OGRE/OgreCamera.h>
#include <OGRE/OgreSceneManager.h>
#include <CCSBasicCameraModes.h>
#include <OgreFramework/KeyboardState.h>

namespace OgreFramework
{
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \class	RTSCameraManager
	///
	/// \brief	Camera manager for RTS camera style.
	///
	/// \author	Fabrice Lamarche, University of Rennes 1
	/// \date	03/12/2011
	////////////////////////////////////////////////////////////////////////////////////////////////////
	class RTSCameraManager 
	{
	protected:
		///< State of the keyboard
		KeyboardState * m_keyboardState ;
		///< The camera control system
		CCS::CameraControlSystem * m_cameraControlSystem ;
		///< The camera mode (RTS mode)
		CCS::RTSCameraMode * m_cameraMode ;

	public:
		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \enum	ControlKey
		///
		/// \brief	Values that represent keys controlling camera movements.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		typedef enum {key_up, key_down, key_left, key_right, key_zoomIn, key_zoomOut} ControlKey ;

	protected:
		///< The current control key configuration
		OIS::KeyCode m_configuration[key_zoomOut+1] ;


	public:

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	RTSCameraManager::RTSCameraManager(Ogre::SceneManager * sceneManager,
		/// 	Ogre::Camera* camera, KeyboardState * keyboardState);
		///
		/// \brief	Constructor.
		///
		/// \author	Fabrice Lamarche, University of Rennes 1
		/// \date	03/12/2011
		///
		/// \param sceneManager 	The ogre scene manager for the scene.
		/// \param camera		 	The controlled camera.
		/// \param keyboardState	The keyboard state.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		RTSCameraManager(Ogre::SceneManager * sceneManager, Ogre::Camera* camera, KeyboardState * keyboardState);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	RTSCameraManager::~RTSCameraManager();
		///
		/// \brief	Destructor.
		///
		/// \author	Fabrice Lamarche, University of Rennes 1
		/// \date	17/12/2011
		////////////////////////////////////////////////////////////////////////////////////////////////////
		~RTSCameraManager();

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	void RTSCameraManager::setDefaultKeyConfig();
		///
		/// \brief	Sets the default key configuration.
		///
		/// \author	Fabrice Lamarche, University of Rennes 1
		/// \date	17/12/2011
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void setDefaultKeyConfig();

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	void RTSCameraManager::setControlKey(ControlKey controlKey, OIS::KeyCode key);
		///
		/// \brief	Sets a control key.
		///
		/// \author	Fabrice Lamarche, University of Rennes 1
		/// \date	17/12/2011
		///
		/// \param	controlKey	The control key.
		/// \param	key		  	The key.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void setControlKey(ControlKey controlKey, OIS::KeyCode key);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	void RTSCameraManager::update(Ogre::Real dt);
		///
		/// \brief	Updates the camera with the given dt.
		///
		/// \author	Fabrice Lamarche, University of Rennes 1
		/// \date	17/12/2011
		///
		/// \param	dt	The dt.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void update(Ogre::Real dt);
	};
}

#endif