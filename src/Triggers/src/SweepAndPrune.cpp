#include <stdafx.h>

#include <Triggers/SweepAndPrune.h>

namespace Triggers
{
	void SweepAndPrune::update( Config::Real const & dt )
	{
		int detectedCollisions = 0 ;
		static ::std::vector<::std::pair<Math::BoundingBox2D<Config::Real>, int> > s_objectList ;
		handleObjectLife() ;
		// Initializes object list 
		s_objectList.erase(s_objectList.begin(), s_objectList.end()) ;
		for(int cpt=0, end=m_objects.size() ; cpt<end ; ++cpt)
		{
			if(m_objects[cpt]->isActive()) // if the object is not active it is ignored
			{
				s_objectList.push_back(::std::make_pair(m_objects[cpt]->getBoundingBox(), cpt)) ;
			}
		}
		// Sorts bounding box list
		::std::sort(s_objectList.begin(), s_objectList.end()) ;
		// Looks for collisions
		//::std::cout<<"Looking for collisions"<<::std::endl ;
		for(int cpt1=0, end=s_objectList.size() ; cpt1<end ; ++cpt1)
		{
			int cpt2=cpt1+1 ;
			while(cpt2<end && s_objectList[cpt1].first.interval(0).intersect(s_objectList[cpt2].first.interval(0)))
			{
				if(!s_objectList[cpt1].first.interval(1).intersect(s_objectList[cpt2].first.interval(1))) { ++cpt2 ; continue ; }
				int object1 = s_objectList[cpt1].second ;
				int object2 = s_objectList[cpt2].second ;
				// If at least one object is not active, do not report collisions
				if(!m_objects[object1]->isActive() || !m_objects[object2]->isActive()) { ++cpt2 ; continue ; }
				// Never report collision between triggers
				if(m_objects[object1]->getType()==CollisionObject::trigger && m_objects[object2]->getType()==CollisionObject::trigger) { ++cpt2 ; continue ; }
				if(areColliding(object1, object2))
				{
					CollisionObject::CollisionMessage message(m_objects[object1], m_objects[object2]) ;
					m_collisionEmitter.send(message) ;
					if(m_objects[object1]->getType()==CollisionObject::trigger) // If object1 if a trigger, the collision is only reported to it
					{
						++detectedCollisions ;
						m_objects[object1]->onCollision(message) ;
					}
					else if(m_objects[object2]->getType()==CollisionObject::trigger) // If object2 if a trigger, the collision is only reported to it
					{
						++detectedCollisions ;
						m_objects[object2]->onCollision(message) ;
					}
					else // The two objects are entities, collision is signaled to both of them
					{
						++detectedCollisions ;
						m_objects[object1]->onCollision(message) ;
						m_objects[object2]->onCollision(message) ;
					}
				}
				++cpt2 ;
			}
		}
		//if(detectedCollisions!=0)
		//{
		//	//::std::cout<<"Sweep and prune detected "<<detectedCollisions<<" collisions."<<::std::endl ;
		//}
	}
}