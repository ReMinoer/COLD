#ifndef _Triggers_CollisionDetectorBase_H
#define _Triggers_CollisionDetectorBase_H

#include <System/ConstructionDestructionListener.h>
#include <System/ActiveObject.h>
#include <Triggers/CollisionObject.h>
#include <Triggers/CollisionDetectorBase.h>
#include <set>

namespace Triggers
{
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \class	CollisionDetectorBase
	///
	/// \brief	Base class for collision detection algorithms.
	///
	/// \author	F. Lamarche, Université de Rennes 1
	/// \date	28/11/2014
	////////////////////////////////////////////////////////////////////////////////////////////////////
	class CollisionDetectorBase : public System::ActiveObject, public System::ConstructionDestructionListener<CollisionObject>
	{
	public:

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \typedef	boost::intrusive_ptr<CollisionDetectorBase> Pointer
		///
		/// \brief	Defines an alias representing the pointer.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		typedef boost::intrusive_ptr<CollisionDetectorBase> Pointer ;

	protected:
		/// Handled objects
		::std::vector<CollisionObject::Pointer> m_objects ;
		/// Objects that have been destroyed
		::std::set<CollisionObject::Pointer> m_destroyedObjects ;
		/// CollisionMessage emitter
		mutable System::MessageEmitter<CollisionObject::CollisionMessage> m_collisionEmitter ;


		///////////////////////////////////////////////////////////////////////////////////
		/// \brief Called when an instance of CollisionObject is constructed. This object
		/// 	   is referenced in the collision detector.
		/// 
		/// \param message 
		/// 
		/// \author F. Lamarche, University of Rennes 1.
		///////////////////////////////////////////////////////////////////////////////////
		virtual void onCreateObject(const System::ConstructionMessage<CollisionObject> & message);

		///////////////////////////////////////////////////////////////////////////////////
		/// \brief Called when an instance of CollisionObject is destroyed. This object
		/// 	   is dereferenced.
		/// 
		/// \param message
		/// \return 
		/// 
		/// \author F. Lamarche, University of Rennes 1.
		///////////////////////////////////////////////////////////////////////////////////
		virtual void onDestroyObject(const System::DestructionMessage<CollisionObject> & message);

		///////////////////////////////////////////////////////////////////////////////////
		/// \brief Updates data structures given destroyed and created CollisionObjects
		/// 
		/// \author F. Lamarche, University of Rennes 1.
		///////////////////////////////////////////////////////////////////////////////////
		void handleObjectLife();

		///////////////////////////////////////////////////////////////////////////////////
		/// \brief Test whether object1 and object2 are colliding of not
		/// 
		/// \param object1 The index of the first object in m_objects
		/// \param object2 The index of the second object in m_objects
		/// \return true if objects are colliding, false otherwise.
		/// 
		/// \author F. Lamarche, University of Rennes 1.
		///////////////////////////////////////////////////////////////////////////////////
		bool areColliding(int object1, int object2);

	public:

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	bool CollisionDetectorBase::isColliding(const ::std::vector<Shape> & shape) const
		///
		/// \brief	Query if 'shape' is colliding with referenced objects. 
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	28/11/2014
		///
		/// \param	shape	The tested shape.
		///
		/// \return	true if colliding, false if not.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		bool isColliding(const ::std::vector<Shape> & shape1) const;

		///////////////////////////////////////////////////////////////////////////////////
		/// \brief Returns the CollisionObject::CollisionMessage emitter.
		/// 
		/// \author F. Lamarche, University of Rennes 1.
		///////////////////////////////////////////////////////////////////////////////////
		System::MessageEmitter<CollisionObject::CollisionMessage> * getCollisionEmitter() const;
	};
}

#endif