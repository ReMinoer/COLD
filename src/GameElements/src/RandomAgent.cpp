#include <stdafx.h>
#include <GameElements/RandomAgent.h>
#include <GameElements/BulletBase.h>

namespace GameElements
{


	void RandomAgent::onCollision( const CollisionMessage & message )
	{

	}

	Math::Vector2<Config::Real> RandomAgent::getVelocity() const
	{
		const Map::GroundCellDescription & currentCell = OgreFramework::GlobalConfiguration::getCurrentMap()->getCell(getPosition().projectZ()) ;
		return m_velocity*(1.0-currentCell.m_speedReduction) ;
	}

	RandomAgent::RandomAgent( const UnitsArchetypes::Archetype * archetype, const WeaponsArchetypes::Archetype * weaponArchetype, bool computeCollisionMesh/*=true*/ ) : Agent(archetype, weaponArchetype, computeCollisionMesh)
	{
		m_velocity = randomVelocity() ;
	}

	void RandomAgent::update( const Config::Real & dt )
	{
		// Computes movements
		const Map::GroundCellDescription & currentCell = OgreFramework::GlobalConfiguration::getCurrentMap()->getCell(getPosition().projectZ()) ;
		Math::Vector2<Config::Real> newPosition = getPosition().projectZ()+m_velocity*dt*(1.0-currentCell.m_speedReduction) ;
		// If displacement is valid, the agent moves, otherwise, a new random velocity is computed
		if(OgreFramework::GlobalConfiguration::getCurrentMap()->isValid(newPosition) && OgreFramework::GlobalConfiguration::getCurrentMap()->getCell(newPosition).m_speedReduction!=1.0)
		{
			setOrientation(m_velocity) ;
			setPosition(newPosition.push(0.0)) ;
		}
		else
		{
			m_velocity = randomVelocity() ;
		}
		// Handles perception and fires on agents
		if(canFire())
		{
			::std::vector<Triggers::CollisionObject::Pointer> objects = m_perception->perceivedAgents() ;
			for(int cpt=0 ; cpt<objects.size() ; ++cpt)
			{
				if(boost::dynamic_pointer_cast<Agent>(objects[cpt])==NULL)
				{
					::std::swap(objects[cpt], objects.back()) ;
					objects.pop_back() ;
				}
			}
			if(objects.size()!=0) // If there is something to shoot, then open fire !!!! 
			{
				int index = rand()%objects.size() ;
				Agent::Pointer ptr = boost::dynamic_pointer_cast<Agent>(objects[index]) ;
				if(ptr!=NULL && ptr != this)
				{
					Math::Vector2<Config::Real> otherPosition = ptr->getPosition().projectZ() ;
					Math::Vector2<Config::Real> otherVelocity = ptr->getVelocity() ;
					Config::Real bulletSpeed = m_weapon.getArchetype()->m_speed ;
					Config::Real distanceToTarget = (getPosition().projectZ()-otherPosition).norm() ;
					Config::Real timeToTarget = distanceToTarget/bulletSpeed ;
					fire(otherPosition+otherVelocity*timeToTarget) ;
					//fire(ptr->getPosition().projectZ()) ;
				}
			}
		}
		m_perception->reset() ;
	}
}