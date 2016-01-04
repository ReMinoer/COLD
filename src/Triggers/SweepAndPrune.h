#ifndef _Triggers_SweepAndPrune_H
#define _Triggers_SweepAndPrune_H

#include <System/ConstructionDestructionListener.h>
#include <System/ActiveObject.h>
#include <Triggers/CollisionObject.h>
#include <Triggers/CollisionDetectorBase.h>
#include <set>

namespace Triggers
{
	///////////////////////////////////////////////////////////////////////////////////
	/// \brief Class implementing a sweep and prune collision detection alogrithm. A lot
	/// 	   faster than the BasicCollisionDetector.
	/// 
	/// This class emits the following messages:
	///		\li CollisionObject::CollisionMessage if two objects are colliding
	///			
	/// \warning The current implementation is sub optimal: all elements of the object
	/// 		 list are sorted at each update. 
	/// 
	/// \author F. Lamarche, University of Rennes 1.
	///////////////////////////////////////////////////////////////////////////////////
	class SweepAndPrune : public CollisionDetectorBase
	{
	protected:

	public:
		typedef ::boost::intrusive_ptr<SweepAndPrune> Pointer ;

		SweepAndPrune() {}

		virtual void update(Config::Real const & dt);
	};
}

#endif