#include <stdafx.h>
#include <GameElements/BallisticBullet.h>

namespace GameElements
{


	BallisticBullet::BallisticBullet( Ogre::SceneNode * node, int lifePoints, int armorPoints, Math::Vector2<Config::Real> const & origin, Config::Real speed, Math::Vector2<Config::Real> const & target, Config::Real explosionRange ) : BulletBase(node, lifePoints, armorPoints), m_origin(origin), m_position(origin), m_target(target), m_speed(speed), m_explosionRange(explosionRange)
	{
		// Sets initial position and orientation
		setPosition(m_position.push(0.0)) ;
		setOrientation(m_target-m_position) ;
		// Sets the type, shape and activity of the collision object
		setType(Triggers::CollisionObject::trigger) ;
		addShape(Triggers::Shape(Triggers::Shape::Vector2(0.0,0.0), m_explosionRange)) ;
		CollisionObject::setActive(false) ;
	}

	void BallisticBullet::update( Config::Real const & dt )
	{
		// Updates the bullet position if the collision object is not active i.e. if the explosion does not occur
		Config::Real ratio = (m_position-m_origin).norm()/(m_origin-m_target).norm() ;
		if(!CollisionObject::isActive())
		{
			Math::Vector2<Config::Real> velocity = (m_target-m_origin).normalized()*m_speed ;
			m_position = m_position + velocity*dt ;
			setPosition(m_position.push(sin(Math::pi*ratio)*10)) ;
		}
		// If the ratio is greater than 1 then the target is reached
		if(ratio>=1.0)
		{
			if(CollisionObject::isActive())
			{
				for(auto it=getCollisions().begin(), end=getCollisions().end() ; it!=end ; ++it)
				{
					hit(*it) ;
					Agent::Pointer agent = ::boost::dynamic_pointer_cast<Agent>(*it) ;
					if(agent!=NULL)
					{
						(new PlayParticleSystem(OgreFramework::GlobalConfiguration::getGeometryLoader()->load("BigExplosion.scene",10)))->setPosition(agent->getPosition()) ;
					}
				}
				(new PlayParticleSystem(OgreFramework::GlobalConfiguration::getGeometryLoader()->load("BigExplosion.scene",10)))->setPosition(m_position.push(0.02)) ;
				//OgreFramework::GlobalConfiguration::playSound("../data/sound/explosion.wav") ;
				destroy() ;
			}
			else
			{
				CollisionObject::setActive(true) ;
			}
		}
	}

	Math::Vector2<Config::Real> BallisticBullet::getVelocity() const
	{
		return (m_target-m_origin).normalized()*m_speed ;
	}
}