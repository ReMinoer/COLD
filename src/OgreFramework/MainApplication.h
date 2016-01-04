
#ifndef _MainApplication_H
#define _MainApplication_H

#include <OgreFramework/BaseApplication.h>
#include <System/Controller.h>
#include <Triggers/SweepAndPrune.h>
#include <OgreFramework/Picking.h>
#include <CCSBasicCameraModes.h>
#include <OgreFramework/KeyboardState.h>
#include <OgreFramework/RTSCameraManager.h>
#include <OgreFramework/EntityAdapter.h>
#include <GameElements/NullAgent.h>

namespace OgreFramework
{
	///////////////////////////////////////////////////////////////////////////////////
	/// \brief The main application.
	/// 	   
	/// \remarks \li createScene method should be used to setup your scene
	/// 		 \li update method should be used to update your animation engine
	/// 
	/// \author F. Lamarche, University of Rennes 1.
	///////////////////////////////////////////////////////////////////////////////////
	class MainApplication : public BaseApplication
	{
	public:
		MainApplication();
		virtual ~MainApplication();

	protected:
		///////////////////////////////////////////////////////////////////////////////////
		/// \brief Returns the scene manager
		/// 
		/// \return 
		/// 
		/// \author F. Lamarche, University of Rennes 1.
		///////////////////////////////////////////////////////////////////////////////////
		Ogre::SceneManager * getSceneManager()
		{
			return m_sceneManager ;
		}

		///////////////////////////////////////////////////////////////////////////////////
		/// \brief Return the root node
		/// 
		/// \return 
		/// 
		/// \author F. Lamarche, University of Rennes 1.
		///////////////////////////////////////////////////////////////////////////////////
		Ogre::SceneNode * getRootSceneNode()
		{
			return m_sceneManager->getRootSceneNode() ;
		}

		///////////////////////////////////////////////////////////////////////////////////
		/// \brief Called when the scene needs to be created. 
		/// 
		/// \author F. Lamarche, University of Rennes 1.
		///////////////////////////////////////////////////////////////////////////////////
		virtual void createScene(void);

		///////////////////////////////////////////////////////////////////////////////////
		/// \brief Called when the scene is updated.
		/// 
		/// \param dt Time elapsed since last call
		/// 
		/// \author F. Lamarche, University of Rennes 1.
		///////////////////////////////////////////////////////////////////////////////////
		virtual void update(Ogre::Real dt) ;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	virtual bool MainApplication::mousePressed( const OIS::MouseEvent &arg,
		/// 	OIS::MouseButtonID id );
		///
		/// \brief	Mouse pressed.
		///
		/// \author	Fabrice Lamarche, University of Rennes 1
		/// \date	26/11/2011
		///
		/// \param	arg	The mouse Event.
		/// \param	id 	The identifier.
		///
		/// \return	true if it succeeds, false if it fails.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	void MainApplication::itemSelected(OgreBites::SelectMenu* menu)
		///
		/// \brief	Callback method called when a menu item is selected by the user.
		/// 		
		///
		/// \author	Fabrice Lamarche, University of Rennes 1
		/// \date	27/11/2011
		///
		/// \param menu	The menu in which the selection happened.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void itemSelected(OgreBites::SelectMenu* menu);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	virtual bool MainApplication::keyPressed( const OIS::KeyEvent &arg );
		///
		/// \brief	Callback method called when a key is pressed.
		///
		/// \author	Fabrice Lamarche, University of Rennes 1
		/// \date	03/12/2011
		///
		/// \param	arg	The argument.
		///
		/// \return	true if it succeeds, false if it fails.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual bool keyPressed( const OIS::KeyEvent &arg );

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	virtual bool MainApplication::keyReleased(const OIS::KeyEvent &arg );
		///
		/// \brief	Callback method called when a key is released.
		///
		/// \author	Fabrice Lamarche, University of Rennes 1
		/// \date	03/12/2011
		///
		/// \param	arg	The argument.
		///
		/// \return	true if it succeeds, false if it fails.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual bool keyReleased(const OIS::KeyEvent &arg );

		
		///< The picking controller
		OgreFramework::Picking * m_picking ;
		///< State of the keyboard
		KeyboardState & m_keyboardState ;
		///< The camera manager
		RTSCameraManager * m_cameraManager ;

		//Ogre::SceneNode * m_shipShape ;
		//GameElements::NullAgent::Pointer m_entityAdapter ;
	};
}

#endif 
