#include <stdafx.h>
#include <GameElements/StraightBullet.h>

namespace GameElements
{
	

	StraightBullet::StraightBullet( Ogre::SceneNode * node, int lifePoints, int armorPoints, Math::Vector2<Config::Real> const & origin, Math::Vector2<Config::Real> const & velocity, Config::Real range ) : BulletBase(node, lifePoints, armorPoints), m_origin(origin), m_position(origin), m_velocity(velocity), m_range(range)
	{
		// Creates the collision shape of the bullet
		addShape(Triggers::Shape(Triggers::Shape::Vector2(0.0,0.0), 0.1)) ;
		// Sets initial position and orientation
		setPosition(m_position.push(0.02)) ; // Arbitrary height... Needs to be corrected.
		setOrientation(m_velocity) ;
	}

	void StraightBullet::update( Config::Real const & dt )
	{
		// Is there any collision ?
		if(!getCollisions().empty())
		{
			::std::vector<CollisionObject::Pointer> const & collisions = getCollisions() ;
			// Hits colliding objects
			for(::std::vector<CollisionObject::Pointer>::const_iterator it=collisions.begin(), end=collisions.end() ; it!=end ; ++it)
			{
				hit(*it) ;
				(new PlayParticleSystem(OgreFramework::GlobalConfiguration::getGeometryLoader()->load("Explosion.scene",10)))->setPosition(Math::Vector3<Config::Real>(m_position[0], m_position[1],0.0)) ;
			}
			// Destroys the current bullet
			destroy() ;
			return ;
		}
		// There is no collision, the bullet is moved along its path
		m_position = m_position + m_velocity*dt ;
		setPosition(m_position.push(0.02)) ;
		// If the bullet is out of range, it is destroyed
		if((m_position-m_origin).norm()>=m_range)
		{
			destroy() ;
		}
	}

	Math::Vector2<Config::Real> StraightBullet::getVelocity() const
	{
		return m_velocity ;
	}
}