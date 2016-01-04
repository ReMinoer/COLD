#ifndef _GameElements_ActiveObject_H
#define _GameElements_ActiveObject_H

#include <System/ConstructionDestructionEmitter.h>
#include <Config/Real.h>
#include <Ext/boost/reference_count.h>

namespace System
{
	///////////////////////////////////////////////////////////////////////////////////
	/// \brief An object that have an associated behavior which is regularly triggered
	/// 	   by calling the update method.
	/// 	   
	/// This class sends
	///		\li a System::ConstructionMessage<ActiveObject> when an instance is constructed
	///		\li a System::DestructionMessage<ActiveObject> when an instance is destroyed
	///		\li a ActiveObject::ActivityState message when the activity state changes (including object construction)
	/// 
	/// \author F. Lamarche, University of Rennes 1.
	///////////////////////////////////////////////////////////////////////////////////
	class ActiveObject : public virtual Ext::boost::reference_count
	{
	public:

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \typedef	::boost::intrusive_ptr<CollisionObject> Pointer
		///
		/// \brief	Defines an alias representing a smart pointer to this type.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		typedef ::boost::intrusive_ptr<ActiveObject> Pointer ;

		///////////////////////////////////////////////////////////////////////////////////
		/// \brief Message sent when object active state changes.
		/// 
		/// \author F. Lamarche, University of Rennes 1.
		///////////////////////////////////////////////////////////////////////////////////
		struct ActivityStateMessage
		{
			const ActiveObject & m_object ;

			friend class ActiveObject ;

		private:
			ActivityStateMessage(const ActiveObject & object)
				: m_object(object)
			{}
		};

	protected:
		///////////////////////////////////////////////////////////////////////////////////
		/// \brief Helper method sending a construction message.
		/// 
		/// \param object The constructed object.
		/// \param Type the type of the created object (automatically inferred during call)
		/// 
		/// \author F. Lamarche, University of Rennes 1.
		///////////////////////////////////////////////////////////////////////////////////
		template <class Type>
		void sendConstructionMessage(Type & object)
		{
			System::ConstructionDestructionEmitter<Type>::sendConstruction(object) ;
		}

		///////////////////////////////////////////////////////////////////////////////////
		/// \brief helper method sending a destruction message.
		/// 
		/// \param object The destroyed object.
		/// \param Type the type of the created object (automatically inferred during call)
		/// 
		/// \author F. Lamarche, University of Rennes 1.
		///////////////////////////////////////////////////////////////////////////////////
		template <class Type>
		void sendDestructionMessage(Type & object)
		{
			System::ConstructionDestructionEmitter<Type>::sendDestruction(object) ;
		}

		/// If true, the object is active and update method must be called. Otherwise, the object is in pause state.
		bool m_isActive ;
		/// Emitter of the activity state message
		mutable System::MessageEmitter<ActivityStateMessage> m_activityEmitter ;

	public:
		///////////////////////////////////////////////////////////////////////////////////
		/// \brief Creates an active object. Emits a System::ConstructionMessage<ActiveObject>
		/// 	   when the object is created and an ActiveObject::ActivityStateMessage.
		/// 
		/// \param isActive Tells wether the object is active or not.
		/// \return 
		/// 
		/// \author F. Lamarche, University of Rennes 1.
		///////////////////////////////////////////////////////////////////////////////////
		ActiveObject(bool isActive=true)
			: m_isActive(isActive)
		{
			sendConstructionMessage(*this) ;
			m_activityEmitter.send(ActivityStateMessage(*this)) ;
		}

		///////////////////////////////////////////////////////////////////////////////////
		/// \brief 
		/// 
		/// \return 
		/// 
		/// \author F. Lamarche, University of Rennes 1.
		///////////////////////////////////////////////////////////////////////////////////
		virtual ~ActiveObject()
		{
			//sendDestructionMessage(*this) ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	virtual void :::destroy()
		///
		/// \brief	Asks for the destruction of this object. This instance will be deleted as soon as
		/// 		the object is no more referenced in the system (in a maximum of one simulation 
		/// 		time step).
		///
		/// \author	Fabrice Lamarche, university of Rennes 1
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual void destroy()
		{
			sendDestructionMessage(*this) ;
		}

		///////////////////////////////////////////////////////////////////////////////////
		/// \brief Return true if the object is active, false otherwise.
		/// 
		/// \return 
		/// 
		/// \author F. Lamarche, University of Rennes 1.
		///////////////////////////////////////////////////////////////////////////////////
		bool isActive() const
		{
			return m_isActive ;
		}

		///////////////////////////////////////////////////////////////////////////////////
		/// \brief Set the activity state of the object.
		/// 
		/// \param isActive
		/// 
		/// \author F. Lamarche, University of Rennes 1.
		///////////////////////////////////////////////////////////////////////////////////
		void setActive(bool isActive)
		{
			// If activity state changes, a message is sent
			if(m_isActive!=isActive)
			{
				m_isActive = isActive ;
				m_activityEmitter.send(ActivityStateMessage(*this)) ;
			}
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
		/// \brief Returns the activity state emitter for this instance. 
		/// 
		/// \return 
		/// 
		/// \author F. Lamarche, University of Rennes 1.
		///////////////////////////////////////////////////////////////////////////////////
		System::MessageEmitter<ActivityStateMessage> * getActivityStateEmitter() const
		{
			return &m_activityEmitter ;
		}
	};
}

#endif