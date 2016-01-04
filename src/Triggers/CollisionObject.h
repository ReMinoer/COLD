#ifndef _Triggers_CollisionObject_H
#define _Triggers_CollisionObject_H

#include <Triggers/Shape.h>
#include <System/ConstructionDestructionEmitter.h>
#include <vector>
#include <Ext/boost/reference_count.h>

namespace Triggers
{
	///////////////////////////////////////////////////////////////////////////////////
	/// \brief An object that handles collisions with other collision objects. If a 
	/// 	   collision is detected, the method onCollision is called. 
	/// 	   
	/// Those objects send the following messages
	///		\li System::ConstructionMessage<CollisionObject> when the instance is contructed and initialized.
	///		\li System::DestructionMessage<CollisionObject> when the instance is destroyed
	/// 
	/// \author F. Lamarche, University of Rennes 1.
	///////////////////////////////////////////////////////////////////////////////////
	class CollisionObject : public virtual Ext::boost::reference_count
	{
	public:

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \typedef	::boost::intrusive_ptr<CollisionObject> Pointer
		///
		/// \brief	Defines an alias representing a smart pointer to this type.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		typedef ::boost::intrusive_ptr<CollisionObject> Pointer ;

		typedef enum 
		{
			/// Objects of type entity perceive collisions with other entity objects but not with trigger objects
			entity,
			/// Objects of type trigger perceive collisions with entity objects but not with trigger objects		
			trigger
		} CollisionObjectType ;

	protected:
		/// All the shapes associated to the current object
		::std::vector<Shape> m_shapes ;
		/// The transformation associated to the current collision object
		::Math::Matrix3x3<Config::Real> m_transform ;
		/// Type of the current collision object
		CollisionObjectType m_type ;
		///< true if this object is active
		bool m_isActive ;
		
	public:
		///////////////////////////////////////////////////////////////////////////////////
		/// \brief Message sent when a collision is detected between two CollisionObjects
		/// 
		/// \author F. Lamarche, University of Rennes 1.
		///////////////////////////////////////////////////////////////////////////////////
		struct CollisionMessage
		{
			/// The first object in collision
			CollisionObject::Pointer const m_object1 ;
			/// The second object in collision
			CollisionObject::Pointer const m_object2 ;

			///////////////////////////////////////////////////////////////////////////////////
			/// \brief Constructor taking the pair of colliding objects
			/// 
			/// \param object1
			/// \param object2
			/// 
			/// \author F. Lamarche, University of Rennes 1.
			///////////////////////////////////////////////////////////////////////////////////
			CollisionMessage(CollisionObject::Pointer object1, CollisionObject::Pointer object2);

			///////////////////////////////////////////////////////////////////////////////////
			/// \brief Returns 
			/// 
			/// \param object
			/// \return 
			/// 
			/// \author F. Lamarche, University of Rennes 1.
			///////////////////////////////////////////////////////////////////////////////////
			CollisionObject::Pointer other(CollisionObject::Pointer object) const;
		};

		///////////////////////////////////////////////////////////////////////////////////
		/// \brief Default constructor
		/// 
		/// \author F. Lamarche, University of Rennes 1.
		///////////////////////////////////////////////////////////////////////////////////
		CollisionObject(CollisionObjectType type = entity);

		///////////////////////////////////////////////////////////////////////////////////
		/// \brief Destructor
		/// 
		/// \author F. Lamarche, University of Rennes 1.
		///////////////////////////////////////////////////////////////////////////////////
		virtual ~CollisionObject();

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	virtual void CollisionObject::destroy();
		///
		/// \brief	Asks for the destruction of this object. This instance will be deleted as soon as
		/// 		the object is no more referenced in the system (in a maximum of one simulation 
		/// 		time step)
		///
		/// \author	Fabrice Lamarche, university of Rennes 1
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual void destroy();

		///////////////////////////////////////////////////////////////////////////////////
		/// \brief Returns the associated transformation
		/// 
		/// \return 
		/// 
		/// \author F. Lamarche, University of Rennes 1.
		///////////////////////////////////////////////////////////////////////////////////
		const Math::Matrix3x3<Config::Real> & getTransform() const;

		///////////////////////////////////////////////////////////////////////////////////
		/// \brief Sets the associated transformation
		/// 
		/// \param tranform The new associated transformation
		/// 
		/// \author F. Lamarche, University of Rennes 1.
		///////////////////////////////////////////////////////////////////////////////////
		void setTransform(Math::Matrix3x3<Config::Real> const & tranform);

		///////////////////////////////////////////////////////////////////////////////////
		/// \brief Adds a shape to the current collision object
		/// 
		/// \param shape The added shape
		/// 
		/// \author F. Lamarche, University of Rennes 1.
		///////////////////////////////////////////////////////////////////////////////////
		void addShape(const Shape & shape);

		///////////////////////////////////////////////////////////////////////////////////
		/// \brief Removes all shapes associated to the current object
		/// 
		/// \author F. Lamarche, University of Rennes 1.
		///////////////////////////////////////////////////////////////////////////////////
		void resetShapes();

		///////////////////////////////////////////////////////////////////////////////////
		/// \brief Returns all shapes associated to the current collision object
		/// 
		/// \return The shapes
		/// 
		/// \author F. Lamarche, University of Rennes 1.
		///////////////////////////////////////////////////////////////////////////////////
		const ::std::vector<Shape> & getShapes() const;

		///////////////////////////////////////////////////////////////////////////////////
		/// \brief Callback method called when a collision is detected
		/// 
		/// \param message The collision information
		/// 
		/// \author F. Lamarche, University of Rennes 1.
		///////////////////////////////////////////////////////////////////////////////////
		virtual void onCollision(const CollisionMessage & message) = 0 ;

		///////////////////////////////////////////////////////////////////////////////////
		/// \brief Return the object type
		/// 
		/// \return The object type
		/// 
		/// \author F. Lamarche, University of Rennes 1.
		///////////////////////////////////////////////////////////////////////////////////
		CollisionObjectType getType() const
		{
			return m_type ;
		}

		///////////////////////////////////////////////////////////////////////////////////
		/// \brief Changes the object type
		/// 
		/// \param type The new type
		/// 
		/// \author F. Lamarche, University of Rennes 1.
		///////////////////////////////////////////////////////////////////////////////////
		void setType(CollisionObjectType type)
		{
			m_type = type ;
		}

		///////////////////////////////////////////////////////////////////////////////////
		/// \brief Returns the bounding box of this object in global cordinates
		/// 
		/// \return The bounding box in global coordinates
		/// 
		/// \author F. Lamarche, University of Rennes 1.
		///////////////////////////////////////////////////////////////////////////////////
		Math::BoundingBox2D<Config::Real> getBoundingBox() const ;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	void CollisionObject::setActive(bool isActive) 
		///
		/// \brief	Sets the activity state of the object. If false, this object is no more taken into account
		/// 		in the collision engine.
		///
		/// \author	Fabrice Lamarche, University of Rennes 1
		/// \date	26/11/2011
		///
		/// \param	isActive	true if this object is active.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void setActive(bool isActive) ;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	bool CollisionObject::isActive() const
		///
		/// \brief	Query if this object is active.
		///
		/// \author	Fabrice Lamarche, University of Rennes 1
		/// \date	26/11/2011
		///
		/// \return	true if active, false if not.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		bool isActive() const;
	};
}

#endif