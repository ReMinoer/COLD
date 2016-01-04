#include <stdafx.h>

#include <GameElements/Bullet.h>
#include <Ext/Ogre/NodeManipulation.h>
#include <GameElements/PlayParticleSystem.h>
#include <OgreFramework/GlobalConfiguration.h>

namespace GameElements
{


	void Bullet::update( Config::Real const & dt )
	{
		// Updates collided objects life
		for(int cpt=0, size=(int)m_collisions.size() ; cpt<size ; ++cpt)
		{
			hit(m_collisions[cpt]) ;
		}
		if(m_collisions.size()>0)
		{
			CollisionObject::setActive(false) ; // No more collisions
			Ext::Ogre::setEmittingParticleSystems(m_entity, false) ;
			(new PlayParticleSystem(OgreFramework::GlobalConfiguration::getGeometryLoader()->load("Explosion.scene",10)))->setPosition(Math::Vector3<Config::Real>(m_position[0], m_position[1],0.0)) ;
		}
		m_collisions.erase(m_collisions.begin(), m_collisions.end()) ;
		// Updates position
		m_position = m_position+m_velocity*dt ;
		// Updates collision object position and orientation
		Config::Real radius, theta ;
		m_velocity.polarCoordinates(radius, theta) ;
		//Math::Matrix3x3<Config::Real> transform = Math::Matrix3x3<Config::Real>::getTranslationHomogeneous(m_position)*Math::Matrix3x3<Config::Real>::getRotationHomogeneous(theta);
		//CollisionObject::setTransform(transform) ;
		//setPosition(Math::Vector3<Config::Real>(m_position[0], m_position[1], 0.0)) ;
		Config::Real distanceFactor = (m_position-m_startPosition).norm()/m_range ;
		//if(distanceFactor<=1.0)
		{
			setPosition(Math::Vector3<Config::Real>(m_position[0], m_position[1], 0.1/*sin(distanceFactor*Math::pi)*10*/)) ; //0.1
			setOrientation(0,0,theta-Math::piDiv2) ;
		}
		if((m_position-m_startPosition).norm()>=m_range)
		{
			if(CollisionObject::isActive())
			{	
				CollisionObject::setActive(false) ; // No more collisions
				Ext::Ogre::setEmittingParticleSystems(m_entity, false) ;
				(new PlayParticleSystem(OgreFramework::GlobalConfiguration::getGeometryLoader()->load("Explosion.scene")))->setPosition(Math::Vector3<Config::Real>(m_position[0], m_position[1],0.0)) ;
			}
			if(!Ext::Ogre::areAliveParticles(m_entity))
			{
				destroy() ;
				//delete this ; // This bullet no longer exists
			}
		}
	}

	void Bullet::onCollision( const CollisionMessage & message )
	{
		// Stores collisions
		CollisionObject::Pointer other = message.other(this) ;
		m_collisions.push_back(other) ;
	}

	Bullet::Bullet( Ogre::SceneNode * node, int lifePoints, int armorPoints, Math::Vector2<Config::Real> const & origin, Math::Vector2<Config::Real> const & velocity, Config::Real range ) 
		: GameObject(node), m_lifePoints(lifePoints), m_armorPoints(armorPoints), m_startPosition(origin), m_position(origin), m_velocity(velocity), m_range(range)
	{
		//addShape(Triggers::Shape(Triggers::Shape::Vector2(0.0,0.0), 0.1)) ;
		addShape(Triggers::Shape(Triggers::Shape::Vector2(0.0,0.0), 0.1)) ;
		//Triggers::CollisionObject::setActive(false);
		setPosition(Math::Vector3<Config::Real>(origin[0], origin[1], 0.0)) ;
	}

	void Bullet::hit( CollisionObject::Pointer object )
	{
		//Agent * agent = dynamic_cast<Agent*>(object);
		Agent::Pointer agent = boost::dynamic_pointer_cast<Agent>(object) ;
		if(agent != NULL)
		{
			agent->m_lifePoints = agent->m_lifePoints - ::std::max(m_lifePoints-agent->m_armorPoints, 0);
			agent->m_armorPoints = ::std::max(agent->m_armorPoints-m_armorPoints, 0) ;
			if(agent->isDead()) 
			{
				//::std::cout<<"Agent "<<agent<<" is dead !"<<::std::endl ;
				agent->destroy() ;
			}
		}
	}
}