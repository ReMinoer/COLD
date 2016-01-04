#ifndef _GameElements_GameObject_H
#define _GameElements_GameObject_H

#include <System/ActiveObject.h>
#include <Triggers/CollisionObject.h>
#include <OgreFramework/EntityAdapter.h>

namespace GameElements
{
	///////////////////////////////////////////////////////////////////////////////////
	/// \brief This class is the super class of all active objects of the game.
	/// 	   
	/// This class is connected to the whole system. Once an instance is created, it is 
	/// referenced in the controller, in the collision detector and can be selected with 
	/// picking.
	/// 
	///		\li If the object is selected by picking, the method onSelect is called (can be overridden)
	///		\li If the object is unselected by picking, the method onUnselect is called (can be overridden)
	///		\li If a collision is detected, the method onCollision is called (must be defined by inheritance)
	///		\li At every time step of the simulation, the method update is called (must be defined by inheritance)
	/// 	   
	/// 	   This class emits the following messages:
	/// 		\li System::ConstructionMessage<GameObject>
	/// 		\li System::DestructionMessage<GameObject>
	/// 		\li All messages emitted by System::ActiveObject and Triggers::CollisionObject 
	/// 			and OgreFramework::EntityAdapter
	/// 		\li GameObject::SelectedObjectMessage when the object is selected by picking manager
	/// 		\li GameObject::UnselectedObjectMessage when the object is unselected by picking manager
	/// 
	/// \author F. Lamarche, University of Rennes 1.
	///////////////////////////////////////////////////////////////////////////////////
	class GameObject : public System::ActiveObject, public Triggers::CollisionObject, public OgreFramework::EntityAdapter
	{
	public:
		typedef ::boost::intrusive_ptr<GameObject> Pointer ;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \struct	SelectedGameObjectMessage
		///
		/// \brief	Selected game object message.
		///
		/// \author	Fabrice Lamarche, University of Rennes 1
		/// \date	26/11/2011
		////////////////////////////////////////////////////////////////////////////////////////////////////
		struct SelectedGameObjectMessage
		{
			GameObject & m_selected ;

			SelectedGameObjectMessage(GameObject & selected)
				: m_selected(selected)
			{}
		};

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \struct	UnselectedGameObjectMessage
		///
		/// \brief	Unselected game object message.
		///
		/// \author	Fabrice Lamarche, University of Rennes 1
		/// \date	26/11/2011
		////////////////////////////////////////////////////////////////////////////////////////////////////
		struct UnselectedGameObjectMessage
		{
			GameObject & m_unselected ;

			UnselectedGameObjectMessage(GameObject & selected)
				: m_unselected(selected)
			{}
		};

	private:
		///< The selected emitter
		static DesignPattern::StaticMember<System::MessageEmitter<SelectedGameObjectMessage> > m_selectedEmitter ;
		///< The unselected emitter
		static DesignPattern::StaticMember<System::MessageEmitter<UnselectedGameObjectMessage> > m_unselectedEmitter ;

	protected:
		/// \brief	The 2D position of the agent.
		Math::Vector2<Config::Real> m_position ;
		/// \brief	The orientation of the agent.
		Config::Real m_orientation ;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	void Agent::updateCollisionShapeTransform()
		///
		/// \brief	Updates the collision shape transform.
		///
		/// \author	Fabrice Lamarche, university of Rennes 1
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void updateCollisionShapeTransform();

	public: 

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	static System::MessageEmitter<SelectedGameObjectMessage> * GameObject::getSelectedGameObjectEmitter()
		///
		/// \brief	Gets the SelectedGameObjectMessage emitter.
		///
		/// \author	Fabrice Lamarche, University of Rennes 1
		/// \date	26/11/2011
		///
		/// \return	the emitter.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		static System::MessageEmitter<SelectedGameObjectMessage> * getSelectedGameObjectEmitter();

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	static System::MessageEmitter<UnselectedGameObjectMessage> * GameObject::getUnselectedGameObjectEmitter()
		///
		/// \brief	Gets the UnselectedGameObjectMessage emitter.
		///
		/// \author	Fabrice Lamarche, University of Rennes 1
		/// \date	26/11/2011
		///
		/// \return	the emitter.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		static System::MessageEmitter<UnselectedGameObjectMessage> * getUnselectedGameObjectEmitter();
 
		///////////////////////////////////////////////////////////////////////////////////
		/// \brief Default constructor
		/// 
		/// \param node The ogre scene node associated to the 3D representation of this 
		/// 			object.
		/// 
		/// \author F. Lamarche, University of Rennes 1.
		///////////////////////////////////////////////////////////////////////////////////
		GameObject(Ogre::SceneNode * node) ;

		///////////////////////////////////////////////////////////////////////////////////
		/// \brief Destructor
		/// 
		/// \author F. Lamarche, University of Rennes 1.
		///////////////////////////////////////////////////////////////////////////////////
		virtual ~GameObject();

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	virtual void :::destroy()
		///
		/// \brief	Asks for the destruction of this object. This instance will be deleted as soon as
		/// 		the object is no more referenced in the system (in a maximum of one simulation 
		/// 		time step)
		///
		/// \author	Fabrice Lamarche, university of Rennes 1
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual void destroy()
		{
			System::ActiveObject::destroy() ;
			Triggers::CollisionObject::destroy() ;
		}

		///////////////////////////////////////////////////////////////////////////////////
		/// \brief The update method called at each frame.
		/// 
		/// \param dt Time elapsed since last call
		/// 
		/// \author F. Lamarche, University of Rennes 1.
		///////////////////////////////////////////////////////////////////////////////////
		virtual void update(Config::Real const & dt) = 0 ;

		///////////////////////////////////////////////////////////////////////////////////
		/// \brief Callback method called when a collision is detected
		/// 
		/// \param message The collision information
		/// 
		/// \author F. Lamarche, University of Rennes 1.
		///////////////////////////////////////////////////////////////////////////////////
		virtual void onCollision(const CollisionMessage & message) = 0 ;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	virtual void GameObject::onSelect()
		///
		/// \brief	Executes the select action.
		///
		/// \author	Fabrice Lamarche, University of Rennes 1
		/// \date	26/11/2011
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual void onSelect();

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	virtual void GameObject::onUnselect()
		///
		/// \brief	Executes the unselect action.
		///
		/// \author	Fabrice Lamarche, University of Rennes 1
		/// \date	26/11/2011
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual void onUnselect();

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	virtual void Agent::setPosition(Math::Vector3<Config::Real> const & position)
		///
		/// \brief	Sets the position of the agent. This method changes the graphical representation's position
		/// 		and the collision shape position.
		///
		/// \author	Fabrice Lamarche, university of Rennes 1
		/// \param	position	The new position.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual void setPosition(Math::Vector3<Config::Real> const & position);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	virtual void Agent::setOrientation(Config::Real angleX, Config::Real angleY,
		/// 	Config::Real angleZ)
		///
		/// \brief	Sets the orientation of the agent. This method changes the graphical representation's orientation
		/// 		and the collision shape orientation.
		///
		/// \author	Fabrice Lamarche, university of Rennes 1
		/// \param	angleX	The angle x coordinate.
		/// \param	angleY	The angle y coordinate.
		/// \param	angleZ	The angle z coordinate.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual void setOrientation(Config::Real angleX, Config::Real angleY, Config::Real angleZ);
	};
}

#endif