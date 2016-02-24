#include <stdafx.h>
#include <GameElements/AIManager.h>

namespace GameElements
{
	AIManager::AIManager ()
	{
		std::cout << "Constructeur: Manager" <<std::endl;
	}

	void AIManager::onMessage(System::DestructionMessage<AiAgent> const& msg)
	{
		std::cout << "onMessage" <<std::endl;
		for(int i=0;i<controlledUnits.size();i++)
		{
			if(&msg.m_object == controlledUnits[i])
			{
				controlledUnits.erase(controlledUnits.begin()+i);
				return;
			}
			if(&msg.m_object == controlledUnits[i]->getTarget())
			{
				assignUnitTarget(controlledUnits[i]);
			}
		}
		for(int i=0;i<opponentUnits.size();i++)
		{
			if(&msg.m_object == opponentUnits[i])
			{
				opponentUnits.erase(opponentUnits.begin()+i);
				return;
			}
		}
	}

	void AIManager::assignAllUnitsTarget()
	{
		std::cout << "AssignAllUnitsTarget" <<std::endl;
		for(int i=0;i<controlledUnits.size();i++)
		{
			assignUnitTarget(controlledUnits[i]);
		}
	}

	void AIManager::assignUnitTarget(AiAgent* agent)
	{
		std::cout << "AssignTarget" <<std::endl;
		Math::Vector3<Config::Real> minDistance = realMaxValue;
		Math::Vector3<Config::Real> shipPosition = agent->getPosition();
		Math::Vector3<Config::Real> destination;
		AiAgent* newTarget = NULL;

		for(int i=0; i<opponentUnits.size();i++)
		{
			
			Math::Vector3<Config::Real> distance = opponentUnits[i]->getPosition() - shipPosition; 
			if( distance < minDistance)
			{
				minDistance = distance;
				newTarget = opponentUnits[i];
				destination = opponentUnits[i]->getPosition();
			}
		}
		agent->setDestination(destination.projectZ());
		agent->setTarget(newTarget);
	}

	void AIManager::addUnitToControlledUnits(AiAgent* unit)
	{
		std::cout << "AddToControlled" <<std::endl;
		controlledUnits.push_back(unit);
	}
	void AIManager::addUnitToOpponentUnits(AiAgent* unit)
	{
		std::cout << "AddToOpponent" <<std::endl;
		opponentUnits.push_back(unit);
	}
}