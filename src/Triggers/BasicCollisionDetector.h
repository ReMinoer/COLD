#ifndef _Triggers_BasicCollisionDetector_H
#define _Triggers_BasicCollisionDetector_H

#include <System/ConstructionDestructionListener.h>
#include <System/ActiveObject.h>
#include <Triggers/CollisionObject.h>
#include <Triggers/CollisionDetectorBase.h>
#include <set>

namespace Triggers
{
	///////////////////////////////////////////////////////////////////////////////////
	/// \brief A really basic collision detector. Suitable for small scenes with few
	/// 	   objects.
	/// 
	/// This class emits the following messages:
	///		\li CollisionObject::CollisionMessage if two objects are colliding
	/// 
	/// \author F. Lamarche, University of Rennes 1.
	///////////////////////////////////////////////////////////////////////////////////
	class BasicCollisionDetector : public CollisionDetectorBase 
	{
	public:

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \typedef	::boost::intrusive_ptr<BasicCollisionDetector> Pointer
		///
		/// \brief	Defines an alias representing the pointer.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		typedef ::boost::intrusive_ptr<BasicCollisionDetector> Pointer ;

		///////////////////////////////////////////////////////////////////////////////////
		/// \brief Default constructor
		/// 
		/// \author F. Lamarche, University of Rennes 1.
		///////////////////////////////////////////////////////////////////////////////////
		BasicCollisionDetector()
		{}

		///////////////////////////////////////////////////////////////////////////////////
		/// \brief Updates collision detection data structures. 
		/// 
		/// \param dt
		/// \return 
		/// 
		/// \author F. Lamarche, University of Rennes 1.
		///////////////////////////////////////////////////////////////////////////////////
		virtual void update(Config::Real const & dt);
	};
}

#endif