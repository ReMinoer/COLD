#ifndef _OgreFramework_Picking_H
#define _OgreFramework_Picking_H

#include <OGRE/OgreCamera.h>
#include <OGRE/OgreSceneQuery.h>
#include <OGRE/OgreSceneManager.h>
#include <OIS/OIS.h>
#include <OgreFramework/PickableObject.h>

namespace OgreFramework
{
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \class	Picking
	///
	/// \brief	Class handling picking in a 3D scene. This picking is computed with the bounding boxes of the
	/// 		objects.
	///
	/// \author	Fabrice Lamarche, University of Rennes 1
	/// \date	26/11/2011
	////////////////////////////////////////////////////////////////////////////////////////////////////
	class Picking
	{
	protected:
		///< Manager for scene
		Ogre::SceneManager * m_sceneManager ;
		///< The camera
		Ogre::Camera * m_camera ;
		///< The button activating the picking
		OIS::MouseButtonID m_button ;
		/////< The ray scene query object
		//Ogre::DefaultRaySceneQuery m_raySceneQuery ;
		///< true if this object is active
		bool m_isActive ;	
		///< The last selected object, NULL if last picking did not pick a object
		Ogre::MovableObject * m_lastSelected ;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	void Picking::notifySelected(Ogre::MovableObject * object);
		///
		/// \brief	Notifies selection.
		///
		/// \author	Fabrice Lamarche, University of Rennes 1
		/// \date	26/11/2011
		///
		/// \param object	If non-null, the selected object.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void notifySelected(Ogre::MovableObject * object);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	void Picking::notifyUnselected(Ogre::MovableObject * object);
		///
		/// \brief	Notifies unselection.
		///
		/// \author	Fabrice Lamarche, University of Rennes 1
		/// \date	26/11/2011
		///
		/// \param object	If non-null, the unselected object.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void notifyUnselected(Ogre::MovableObject * object);

	public:

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Picking::Picking(Ogre::SceneManager * sceneManager, Ogre::Camera * camera)
		///
		/// \brief	Constructor.
		///
		/// \author	Fabrice Lamarche, University of Rennes 1
		/// \date	26/11/2011
		///
		/// \param sceneManager	manager of the scene, must not be NULL.
		/// \param camera		camera, must not be NULL.
		/// \param buttonId		the button activating the picking
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Picking(Ogre::SceneManager * sceneManager, Ogre::Camera * camera, OIS::MouseButtonID buttonId);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	void Picking::update(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
		///
		/// \brief	Updates the picking.
		///
		/// \author	Fabrice Lamarche, University of Rennes 1
		/// \date	26/11/2011
		///
		/// \param	arg	The mouse envent.
		/// \param	id 	The identifier of the pressed button.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual void update(const OIS::MouseEvent &arg, OIS::MouseButtonID id) = 0 ;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	void Picking::setActive(bool isActive)
		///
		/// \brief	Sets the activity state of this picking instance.
		///
		/// \author	Fabrice Lamarche, University of Rennes 1
		/// \date	26/11/2011
		///
		/// \param	isActive	true if this object is active, false otherwise.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void setActive(bool isActive);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	MovableObject * Picking::getLastSelected() const
		///
		/// \brief	Gets the last selected object. Returns NULL if last picking did not hit an object in the 
		/// 		scene.
		///
		/// \author	Fabrice Lamarche, University of Rennes 1
		/// \date	26/11/2011
		///
		/// \return	null if no object selected, else the last selected object.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Ogre::MovableObject * getLastSelected() const;
	};
}

#endif