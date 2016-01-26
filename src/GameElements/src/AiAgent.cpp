#include <stdafx.h>
#include <GameElements/AiAgent.h>
#include <Ext/Ogre/ComputeBoundingBox.h>
#include <OgreFramework/GlobalConfiguration.h>

namespace GameElements
{
	DesignPattern::StaticMember<System::MessageEmitter<AiAgent::SelectedAiAgentMessage> > AiAgent::AiAgentEmitter ;
	DesignPattern::StaticMember<System::MessageEmitter<AiAgent::UnselectedAiAgentMessage> > AiAgent::AiAgentEmitterUnSelect ;

	AiAgent::AiAgent( const UnitsArchetypes::Archetype * archetype, const WeaponsArchetypes::Archetype * weaponArchetype, Map* map, Ogre::SceneManager * sceneManager, Team team)
		: Agent(archetype, weaponArchetype), m_team(team), _pathfinder(GridPathfinder(map)), m_sceneManager(sceneManager)
	{
		m_circle = NULL;
	}
	
	void AiAgent::update(const Config::Real & dt)
	{
		/*
		if (_currentPath.empty())
			return;
			*/

		Math::Vector2<Config::Real> diff = _nextDestination - getPosition().projectZ();
		if (diff.norm() == 0)
		{
			/*
			if (!_currentPath.empty())
				getNextDestination();
				*/
			return;
		}

		/*
		if (!_pathfinder.isEnd())
			computePath();
			*/
		
		_velocity = diff.normalized() * m_archetype->m_speed;

		const Map::GroundCellDescription & currentCell = OgreFramework::GlobalConfiguration::getCurrentMap()->getCell(getPosition().projectZ());
		Math::Vector2<Config::Real> newPosition = getPosition().projectZ() + _velocity * dt * (1.0 - currentCell.m_speedReduction);
		
		Math::Vector2<Config::Real> newDiff = _nextDestination - newPosition;
		if (newDiff * diff <= 0)
		{
			setPosition(_nextDestination.push(0.0));
			/*
			if (!_currentPath.empty())
				getNextDestination();
				*/
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

		computePath();
		*/
		return true;
	}

	void AiAgent::computePath()
	{
		_pathfinder.ComputePath();
		_currentPath = _pathfinder.GetPath();
		_nextDestination = _currentPath.top();
		cout << "Destination : " << _nextDestination << endl;
	}
	
	void AiAgent::getNextDestination()
	{
		_currentPath.pop();

		if (!_currentPath.empty())
		{
			_nextDestination = _currentPath.top();
			cout << "Destination : " << _nextDestination << endl;
		}
	}

	System::MessageEmitter<AiAgent::SelectedAiAgentMessage> * AiAgent::getAIMessageEmitter()
	{
		return AiAgentEmitter.getInstance();
	}

	System::MessageEmitter<AiAgent::UnselectedAiAgentMessage> * AiAgent::getAIMessageEmitterUnSelect()
	{
		return AiAgentEmitterUnSelect.getInstance();
	}

	void AiAgent::onSelect()
	{
		Agent::onSelect();
		drawCircle();
		getAIMessageEmitter()->send(SelectedAiAgentMessage(*this)) ;
	}

	void AiAgent::onUnselect()
	{
		Agent::onUnselect();
		m_sceneManager->destroyManualObject("Circle");
		getAIMessageEmitterUnSelect()->send(UnselectedAiAgentMessage(*this)) ;
	}

	Team AiAgent::getTeam()
	{
		return m_team;
	}
	void AiAgent::drawCircle()
	{
		m_circle=m_sceneManager->createManualObject("Circle");
		m_circle->begin("BaseWhiteNoLighting", Ogre::RenderOperation::OT_LINE_STRIP);
		const float accuracy = 50;
		//TODO : taille en fct de taille boundingbox
		const float radius = 2;
		unsigned int index = 0;
		for(float theta = 0; theta <= 2 * Ogre::Math::PI; theta += Ogre::Math::PI / accuracy)
		{
			m_circle->position(cos(theta)*radius, sin(theta)*radius, this->m_entity->getPosition().z+0.1 );
			m_circle->index(index++);
		}
		m_circle->index(0);
		m_circle->end();
		this->m_entity->showBoundingBox(false);
		this->m_entity->attachObject(m_circle);
		m_circle->setVisible(true);
	}
}