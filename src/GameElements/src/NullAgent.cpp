#include <stdafx.h>
#include <GameElements/NullAgent.h>
#include <Ext/Ogre/ComputeBoundingBox.h>
#include <OgreFramework/GlobalConfiguration.h>

namespace GameElements
{
	NullAgent::NullAgent( const UnitsArchetypes::Archetype * archetype, const WeaponsArchetypes::Archetype * weaponArchetype ) : Agent(archetype, weaponArchetype)
	{}

	void NullAgent::update(const Config::Real & dt)
	{
		//const Map::GroundCellDescription & currentCell = OgreFramework::GlobalConfiguration::getCurrentMap()->getCell(getPosition().projectZ()) ;
		//double x = rand() ; //-RAND_MAX/2 ;
		//double y = rand() ; //-RAND_MAX/2 ;
		//Math::Vector2<Config::Real> speed(x,y) ;
		//speed = speed.normalized()*m_archetype->m_speed ; //*(1.0-currentCell.m_speedReduction) ;
		//Math::Vector2<Config::Real> newPosition = getPosition().projectZ()+speed*dt ;
		//if(OgreFramework::GlobalConfiguration::getCurrentMap()->isValid(newPosition) && OgreFramework::GlobalConfiguration::getCurrentMap()->getCell(newPosition).m_speedReduction!=1.0)
		//{
		//	//::std::cout<<"setting position"<<::std::endl ;
		//	setPosition(newPosition.push(0.0)) ;
		//	assert(getPosition().projectZ()==newPosition) ;
		//}

	}

	void NullAgent::onCollision (const CollisionMessage & message)
	{}

	Math::Vector2<Config::Real> NullAgent::getVelocity() const
	{
		return Math::Vector2<Config::Real>(0.0, 0.0) ;
	}
}