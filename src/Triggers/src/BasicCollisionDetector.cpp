#include <stdafx.h>

#include <Triggers/BasicCollisionDetector.h>

namespace Triggers
{
	void BasicCollisionDetector::update( Config::Real const & dt )
	{
		__int64 nbTests = 0 ;
		handleObjectLife() ;
		for(unsigned int object1=0 ; object1<m_objects.size() ; ++object1)
		{
			for(unsigned int object2=object1+1 ; object2<m_objects.size() ; ++object2)
			{
				++nbTests ;
				// If at least one object is not active, do not report collisions
				if(!m_objects[object1]->isActive() || !m_objects[object2]->isActive()) { continue ; }
				// Never report collision between triggers
				if(m_objects[object1]->getType()==CollisionObject::trigger && m_objects[object2]->getType()==CollisionObject::trigger) { continue ; }
				if(areColliding(object1, object2))
				{
					CollisionObject::CollisionMessage message(m_objects[object1], m_objects[object2]) ;
					m_collisionEmitter.send(message) ;
					if(m_objects[object1]->getType()==CollisionObject::trigger) // If object1 if a trigger, collision is only reported to it
					{
						m_objects[object1]->onCollision(message) ;
					}
					else if(m_objects[object2]->getType()==CollisionObject::trigger) // If object2 if a trigger, collision is only reported to it
					{
						m_objects[object2]->onCollision(message) ;
					}
					else // The two objects are entities, collision is signaled to both of them
					{
						m_objects[object1]->onCollision(message) ;
						m_objects[object2]->onCollision(message) ;
					}
				}
			}
		}
		//::std::cout<<"Number of tests: "<<nbTests<<std::endl  ;
	}
}