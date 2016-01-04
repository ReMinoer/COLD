#ifndef _OgreFramework_PickingSelectionBuffer_H
#define _OgreFramework_PickingSelectionBuffer_H

#include <Ogre/SelectionBuffer.h>
#include <Ogre/OgreRenderWindow.h>
#include <OIS/OISMouse.h>
#include <OgreFramework/PickableObject.h>
#include <OgreFramework/Picking.h>

namespace OgreFramework
{
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \class	PickingSelectionBuffer
	///
	/// \brief	Class handling picking in a 3D scene. This picking is computed with the precise geometry 
	/// 		of the objects.
	/// 		
	/// \author	Fabrice Lamarche, University of Rennes 1
	/// \date	04/12/2011
	////////////////////////////////////////////////////////////////////////////////////////////////////
	class PickingSelectionBuffer : public Picking
	{
	protected:
		/////< Manager for scene
		//Ogre::SceneManager * m_sceneManager ;
		/////< The camera
		//Ogre::Camera * m_camera ;
		/////< The button activating the picking
		//OIS::MouseButtonID m_button ;
		/////< true if this object is active
		//bool m_isActive ;	
		/////< The last selected object, NULL if last picking did not pick a object
		//Ogre::MovableObject * m_lastSelected ;
		///< Buffer for entity selection (handles picking)
		Ogre::SelectionBuffer * mSelectionBuffer;

		//////////////////////////////////////////////////////////////////////////////////////////////////////
		///// \fn	void PickingSelectionBuffer::notifySelected(Ogre::MovableObject * object);
		/////
		///// \brief	Notifies selection.
		/////
		///// \author	Fabrice Lamarche, University of Rennes 1
		///// \date	26/11/2011
		/////
		///// \param object	If non-null, the selected object.
		//////////////////////////////////////////////////////////////////////////////////////////////////////
		//void notifySelected(Ogre::MovableObject * object);

		//////////////////////////////////////////////////////////////////////////////////////////////////////
		///// \fn	void PickingSelectionBuffer::notifyUnselected(Ogre::MovableObject * object);
		/////
		///// \brief	Notifies unselection.
		/////
		///// \author	Fabrice Lamarche, University of Rennes 1
		///// \date	26/11/2011
		/////
		///// \param object	If non-null, the unselected object.
		//////////////////////////////////////////////////////////////////////////////////////////////////////
		//void notifyUnselected(Ogre::MovableObject * object);

	public:
		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	PickingSelectionBuffer::PickingSelectionBuffer(Ogre::SceneManager * sceneManager, Ogre::Camera * camera)
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
		PickingSelectionBuffer(Ogre::RenderWindow *renderWindow, Ogre::SceneManager * sceneManager, Ogre::Camera * camera, OIS::MouseButtonID buttonId);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	void PickingSelectionBuffer::update(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
		///
		/// \brief	Updates the picking.
		///
		/// \author	Fabrice Lamarche, University of Rennes 1
		/// \date	26/11/2011
		///
		/// \param	arg	The mouse envent.
		/// \param	id 	The identifier of the pressed button.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void update(const OIS::MouseEvent &arg, OIS::MouseButtonID id);

		//////////////////////////////////////////////////////////////////////////////////////////////////////
		///// \fn	void PickingSelectionBuffer::setActive(bool isActive)
		/////
		///// \brief	Sets the activity state of this picking instance.
		/////
		///// \author	Fabrice Lamarche, University of Rennes 1
		///// \date	26/11/2011
		/////
		///// \param	isActive	true if this object is active, false otherwise.
		//////////////////////////////////////////////////////////////////////////////////////////////////////
		//void setActive(bool isActive);

		//////////////////////////////////////////////////////////////////////////////////////////////////////
		///// \fn	MovableObject * PickingSelectionBuffer::getLastSelected() const
		/////
		///// \brief	Gets the last selected object. Returns NULL if last picking did not hit an object in the 
		///// 		scene.
		/////
		///// \author	Fabrice Lamarche, University of Rennes 1
		///// \date	26/11/2011
		/////
		///// \return	null if no object selected, else the last selected object.
		//////////////////////////////////////////////////////////////////////////////////////////////////////
		//Ogre::MovableObject * getLastSelected() const;
	};

}

#endif

