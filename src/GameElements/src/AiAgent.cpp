#include <stdafx.h>
#include <GameElements/AiAgent.h>
#include <Ext/Ogre/ComputeBoundingBox.h>
#include <OgreFramework/GlobalConfiguration.h>

namespace GameElements
{
	AiAgent::AiAgent( const UnitsArchetypes::Archetype * archetype, const WeaponsArchetypes::Archetype * weaponArchetype, Team team) : Agent(archetype, weaponArchetype), m_team(team)
	{}

	void AiAgent::update(const Config::Real & dt)
	{
		Math::Vector2<Config::Real> diff = _destination - getPosition().projectZ();
		if (diff != Math::Vector2<Config::Real>())
		{
			_velocity = diff.normalized() * m_archetype->m_speed ;
		}

		const Map::GroundCellDescription & currentCell = OgreFramework::GlobalConfiguration::getCurrentMap()->getCell(getPosition().projectZ());
		Math::Vector2<Config::Real> newPosition = getPosition().projectZ() + _velocity * dt * (1.0 - currentCell.m_speedReduction);

		setOrientation(_velocity);
		setPosition(newPosition.push(0.0));
	}

	void AiAgent::onCollision (const CollisionMessage & message)
	{
	}

	Math::Vector2<Config::Real> AiAgent::getVelocity() const
	{
		const Map::GroundCellDescription & currentCell = OgreFramework::GlobalConfiguration::getCurrentMap()->getCell(getPosition().projectZ());
		return _velocity * (1.0 - currentCell.m_speedReduction);
	}

	void AiAgent::setDestination(Math::Vector2<Config::Real> destination)
	{
		_destination = destination;
	}
}