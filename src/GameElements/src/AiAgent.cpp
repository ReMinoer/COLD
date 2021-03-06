#include <stdafx.h>
#include <GameElements/AiAgent.h>
#include <Ext/Ogre/ComputeBoundingBox.h>
#include <OgreFramework/GlobalConfiguration.h>

namespace GameElements
{
	DesignPattern::StaticMember<System::MessageEmitter<AiAgent::SelectedAiAgentMessage> > AiAgent::AiAgentEmitter ;
	DesignPattern::StaticMember<System::MessageEmitter<AiAgent::UnselectedAiAgentMessage> > AiAgent::AiAgentEmitterUnSelect ;

	AiAgent::AiAgent( const UnitsArchetypes::Archetype * archetype, const WeaponsArchetypes::Archetype * weaponArchetype, Map* map, Ogre::SceneManager * sceneManager, Team team)
		: Agent(archetype, weaponArchetype), m_team(team), _pathfinder(GridPathfinder(map)), m_sceneManager(sceneManager), stopRushDistance(10), startRushDistance(15)
	{
		m_target = NULL;
		drawCircle();
	}

	AiAgent::~AiAgent()
	{
		//std::cout << "Destruction" << std::endl;
	}
	
	void AiAgent::update(const Config::Real & dt)
	{
		if (m_target != NULL)
		{
			float distance = (m_target->getPosition() - getPosition()).norm();
			if (!tooCloseFromTarget && distance <= stopRushDistance)
				tooCloseFromTarget = true;
			else if (tooCloseFromTarget && distance >= startRushDistance)
			{
				tooCloseFromTarget = false;
				setDestination(m_target->getPosition().projectZ());
			}
		}

		if (!tooCloseFromTarget && (_pathfinder.isEnd() || computePath()))
		{
			_velocity = Vector2<Config::Real>(0,0);
			while (true)
			{
				Math::Vector2<Config::Real> diff = getNextMove();
				if (diff.norm() == 0)
					break;

				const Map::GroundCellDescription & currentCell = OgreFramework::GlobalConfiguration::getCurrentMap()->getCell(getPosition().projectZ());
				float speed = m_archetype->m_speed * (1.0 - currentCell.m_speedReduction);
				
				Math::Vector2<Config::Real> move = diff.normalized() * (speed - _velocity.norm()) * dt;
				Math::Vector2<Config::Real> newPosition = getPosition().projectZ() + move;
				Math::Vector2<Config::Real> newDiff = _nextDestination - newPosition;

				// If agent exceeding his current destination, move and continue
				if (newDiff * diff <= 0)
				{
					_velocity += _nextDestination - getPosition().projectZ();
					setPosition(_nextDestination.push(0.0));
					continue;
				}
				
				// Else, move and stop
				_velocity += newPosition - getPosition().projectZ();
				setPosition(newPosition.push(0.0));
				break;
			}

			setOrientation(_velocity);
		}

		attackInRange();
	}

	void AiAgent::onCollision (const CollisionMessage & message)
	{
		
	}

	Math::Vector2<Config::Real> AiAgent::getVelocity() const
	{
		return _velocity;
	}

	bool AiAgent::setDestination(Math::Vector2<Config::Real> destination)
	{
		return _pathfinder.Initialize(getPosition().projectZ(), destination);
	}

	bool AiAgent::computePath()
	{
		if (!_pathfinder.ComputePath())
			return false;
		
		_currentPath = _pathfinder.GetPath();
		_nextDestination = _currentPath.top();
		return true;
	}
	
	Math::Vector2<Config::Real> AiAgent::getNextMove()
	{
		if (_currentPath.empty())
			return Vector2<Config::Real>();

		Math::Vector2<Config::Real> diff = _nextDestination - getPosition().projectZ();
		while (diff.norm() == 0)
		{
			_currentPath.pop();

			if (_currentPath.empty())
				break;
			
			_nextDestination = _currentPath.top();
			diff = _nextDestination - getPosition().projectZ();
		}
		
		return diff;
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
		this->m_entity->showBoundingBox(false);
		getAIMessageEmitter()->send(SelectedAiAgentMessage(*this)) ;
	}

	void AiAgent::onUnselect()
	{
		Agent::onUnselect();
		m_circle->setVisible(false);
		this->m_entity->showBoundingBox(false);
		getAIMessageEmitterUnSelect()->send(UnselectedAiAgentMessage(*this)) ;
	}

	Team AiAgent::getTeam()
	{
		return m_team;
	}

	void AiAgent::drawCircle()
	{
		std::string name = this->m_entity->getName();
		m_circle=m_sceneManager->createManualObject(name);
		m_circle->begin("BaseWhiteNoLighting", Ogre::RenderOperation::OT_LINE_STRIP);
		const float accuracy = 50;
		//TODO : taille en fct de taille boundingbox
		//TODO : optiminiser m_entity
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
		m_circle->setVisible(false);
		this->m_entity->attachObject(m_circle);
	}

	void AiAgent::attackInRange()
	{
		if(canFire())
		{
			AiAgent::Pointer ptr;
			if (m_target == NULL)
			{
				::std::vector<Triggers::CollisionObject::Pointer> objects = m_perception->perceivedAgents() ;
				for(int cpt=0 ; cpt<objects.size() ; ++cpt)
				{
					if(boost::dynamic_pointer_cast<AiAgent>(objects[cpt])==NULL)
					{
						::std::swap(objects[cpt], objects.back()) ;
						objects.pop_back() ;
					}
				}
				if(objects.size()!=0) // If there is something to shoot, then open fire !!!! 
				{
					int index = rand()%objects.size() ;
					ptr = boost::dynamic_pointer_cast<AiAgent>(objects[index]) ;
					
				}
			}
			else
			{
				ptr = m_target;
			}
			if(ptr!=NULL && ptr != this && ptr->getTeam() != m_team)
			{
				Math::Vector2<Config::Real> otherPosition = ptr->getPosition().projectZ() ;
				Math::Vector2<Config::Real> otherVelocity = ptr->getVelocity() ;
				Config::Real bulletSpeed = m_weapon.getArchetype()->m_speed ;
				Config::Real distanceToTarget = (getPosition().projectZ()-otherPosition).norm() ;
				Config::Real timeToTarget = distanceToTarget/bulletSpeed ;
				if(distanceToTarget <= m_weapon.getArchetype()->m_range)
				{
					fire(otherPosition+otherVelocity*timeToTarget) ;
					//setDestination(this->getPosition().projectZ());
					//fire(ptr->getPosition().projectZ()) ;
				}
			}
		}
		m_perception->reset() ;
	}

	Ogre::ManualObject * AiAgent::getCircle()
	{
		return m_circle;
	}

	void AiAgent::setTarget(AiAgent * target)
	{
		m_target = target;

		if (m_target != NULL)
		{
			float distance = (m_target->getPosition() - getPosition()).norm();
			tooCloseFromTarget = distance <= stopRushDistance;

			setDestination(m_target->getPosition().projectZ());
		}
		else
			tooCloseFromTarget = false;
	}

	AiAgent* AiAgent::getTarget()
	{
		return m_target;
	}

	Weapon AiAgent::getWeapon()
	{
		return m_weapon;
	}

	void AiAgent::destroy()
	{
		std::cout <<"MessageSent" << std::endl;
		System::ConstructionDestructionEmitter<AiAgent>::getDestructionEmitter()->send(System::DestructionMessage<AiAgent>(*this)) ;
		Agent::destroy() ;
		
	}
}