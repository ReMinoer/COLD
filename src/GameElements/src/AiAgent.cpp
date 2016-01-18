#include <stdafx.h>
#include <GameElements/AiAgent.h>
#include <Ext/Ogre/ComputeBoundingBox.h>
#include <OgreFramework/GlobalConfiguration.h>

namespace GameElements
{
	AiAgent::AiAgent( const UnitsArchetypes::Archetype * archetype, const WeaponsArchetypes::Archetype * weaponArchetype, Map* map, Team team)
		: Agent(archetype, weaponArchetype), m_team(team), _pathfinder(GridPathfinder(map))
	{}
	
	void AiAgent::update(const Config::Real & dt)
	{
		//if (_currentPath.empty())
		//	  return;
		
		Math::Vector2<Config::Real> diff = _nextDestination - getPosition().projectZ();
		if (diff.norm() != 0)
			_velocity = diff.normalized() * m_archetype->m_speed;

		const Map::GroundCellDescription & currentCell = OgreFramework::GlobalConfiguration::getCurrentMap()->getCell(getPosition().projectZ());
		Math::Vector2<Config::Real> newPosition = getPosition().projectZ() + _velocity * dt * (1.0 - currentCell.m_speedReduction);
		
		Math::Vector2<Config::Real> newDiff = _nextDestination - newPosition;
		if (newDiff * diff <= 0)
		{
			setPosition(_nextDestination.push(0.0));
			//_currentPath.pop();
			//_nextDestination = _currentPath.top();
		}
		else
			setPosition(newPosition.push(0.0));

		setOrientation(_velocity);
	}

	void AiAgent::onCollision (const CollisionMessage & message)
	{
	}

	Math::Vector2<Config::Real> AiAgent::getVelocity() const
	{
		const Map::GroundCellDescription & currentCell = OgreFramework::GlobalConfiguration::getCurrentMap()->getCell(getPosition().projectZ());
		return _velocity * (1.0 - currentCell.m_speedReduction);
	}

	bool AiAgent::setDestination(Math::Vector2<Config::Real> destination)
	{
		_nextDestination = destination;

		/*
		if (!_pathfinder.Initialize(getPosition().projectZ(), destination))
			return false;

		_pathfinder.ComputePath();
		_currentPath = _pathfinder.GetPath();
		_nextDestination = _currentPath.top();
		*/

		return true;
	}
}