#include <stdafx.h>
#include <GameElements/BulletBase.h>
#include <GameElements/Agent.h>

namespace GameElements
{


	void BulletBase::hit( CollisionObject::Pointer object )
	{
		Agent::Pointer agent = boost::dynamic_pointer_cast<Agent>(object) ;
		if(agent != NULL)
		{
			agent->m_lifePoints = agent->m_lifePoints - ::std::max(m_lifePoints-agent->m_armorPoints, 0);
			agent->m_armorPoints = ::std::max(agent->m_armorPoints-m_armorPoints, 0) ;
			if(agent->isDead()) 
			{
				agent->destroy() ;
			}
		}
	}

	void BulletBase::setOrientation( Math::Vector2<Config::Real> const & velocityVector )
	{
		Config::Real radius, theta ;
		velocityVector.polarCoordinates(radius, theta) ;
		GameObject::setOrientation(0,0,theta-Math::piDiv2) ;
	}

	BulletBase::BulletBase( Ogre::SceneNode * node, int lifePoints, int armorPoints ) : GameObject(node), m_lifePoints(lifePoints), m_armorPoints(armorPoints)
	{

	}

	void BulletBase::onCollision( const CollisionMessage & message )
	{
		CollisionObject::Pointer other = message.other(this) ;
		if(m_filter.find(other.get())==m_filter.end()) // If the object is not in the filter list, the collision  is referenced.
		{		
			m_collisions.push_back(other) ;
		}
	}

	void BulletBase::destroy()
	{
		clearCollisions() ;
		GameObject::destroy() ;
	}
}