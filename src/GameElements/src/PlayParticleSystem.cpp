#include <stdafx.h>
#include <GameElements/PlayParticleSystem.h>

namespace GameElements
{

	PlayParticleSystem::PlayParticleSystem( Ogre::SceneNode * entity ) : GameObject(entity), m_firstStep(true)
	{

	}

	void PlayParticleSystem::onCollision( const CollisionMessage &message )
	{

	}

	void PlayParticleSystem::update( Config::Real const &dt )
	{
		if(!m_firstStep && !Ext::Ogre::areAliveParticles(m_entity))
		{
			destroy() ; //delete this ;
			return ;
		}
		if(m_firstStep) { m_firstStep = false ; }
	}
}