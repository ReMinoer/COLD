#include <stdafx.h>
#include <GameElements/AIManager.h>

namespace GameElements
{
	AIManager::AIManager ()
		:  MessageListener< System::DestructionMessage<AiAgent> >(System::ConstructionDestructionEmitter<AiAgent>::getDestructionEmitter())
	{
		std::cout << "Constructeur: Manager" <<std::endl;
	}

	void AIManager::onMessage(System::DestructionMessage<AiAgent> const& msg)
	{
		std::cout << "onMessage" <<std::endl;
		for (int i = 0; i < controlledUnits.size(); i++)
		{
			if (&msg.m_object == controlledUnits[i])
			{
				controlledUnits.erase(controlledUnits.begin()+i);
				std::cout << "Remove controlled" <<std::endl;
				return;
			}
		}

		for (int i = 0; i < opponentUnits.size(); i++)
		{
			if (&msg.m_object == opponentUnits[i])
			{
				opponentUnits.erase(opponentUnits.begin()+i);

				for (int j=0; j < controlledUnits.size(); j++)
					if (&msg.m_object == controlledUnits[j]->getTarget())
						assignUnitTarget(controlledUnits[j]);

				std::cout << "Remove opponent" <<std::endl;
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
		Config::Real minDistance = Config::realMaxValue;
		Math::Vector3<Config::Real> shipPosition = agent->getPosition();
		AiAgent* newTarget = NULL;

		for(int i=0; i<opponentUnits.size();i++)
		{
			Config::Real distance = (opponentUnits[i]->getPosition() - shipPosition).norm(); 
			if(distance < minDistance)
			{
				minDistance = distance;
				newTarget = opponentUnits[i];
			}
		}
		
		agent->setTarget(newTarget);
		if (newTarget == NULL)
			agent->setDestination(agent->getPosition().projectZ());
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