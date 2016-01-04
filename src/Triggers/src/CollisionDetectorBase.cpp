#include <stdafx.h>

#include <Triggers/CollisionDetectorBase.h>

namespace Triggers
{
	void CollisionDetectorBase::onCreateObject( const System::ConstructionMessage<CollisionObject> & message )
	{
		m_objects.push_back(&message.m_object) ;
	}

	void CollisionDetectorBase::onDestroyObject( const System::DestructionMessage<CollisionObject> & message )
	{
		m_destroyedObjects.insert(&message.m_object) ;
	}

	void CollisionDetectorBase::handleObjectLife()
	{
		unsigned int cpt=0 ;
		while(cpt<m_objects.size())
		{
			::std::set<CollisionObject::Pointer>::iterator location = m_destroyedObjects.find(m_objects[cpt]) ;
			if(location!=m_destroyedObjects.end())
			{
				m_objects[cpt] = m_objects.back() ;
				m_objects.pop_back() ;
				m_destroyedObjects.erase(location) ;
			}
			else
			{
				++cpt ;
			}
		}
		m_destroyedObjects.clear() ;
	}

	bool CollisionDetectorBase::areColliding( int object1, int object2 )
	{
		const ::std::vector<Shape> & shape1 = m_objects[object1]->getShapes() ;
		const ::std::vector<Shape> & shape2 = m_objects[object2]->getShapes() ;
		for(unsigned int index1 = 0 ; index1 < shape1.size() ; ++index1)
		{
			for(unsigned int index2 = 0 ; index2 < shape2.size() ; ++index2)
			{
				if(Shape::distance(shape1[index1], shape2[index2])==0.0)
				{
					return true ;
				}
			}
		}
		return false ;
	}

	System::MessageEmitter<CollisionObject::CollisionMessage> * CollisionDetectorBase::getCollisionEmitter() const
	{
		return &m_collisionEmitter ;
	}

	bool CollisionDetectorBase::isColliding( const ::std::vector<Shape> & shape1 ) const
	{
		for(int cpt=0 ; cpt<m_objects.size() ; ++cpt)
		{
			if(m_objects[cpt]->isActive() && m_objects[cpt]->getType()!=CollisionObject::trigger)
			{
				const ::std::vector<Shape> & shape2 = m_objects[cpt]->getShapes() ;
				for(unsigned int index1 = 0 ; index1 < shape1.size() ; ++index1)
				{
					for(unsigned int index2 = 0 ; index2 < shape2.size() ; ++index2)
					{
						if(Shape::distance(shape1[index1], shape2[index2])==0.0)
						{
							return true ;
						}
					}
				}
			}
		}
		return false ;
	}

}