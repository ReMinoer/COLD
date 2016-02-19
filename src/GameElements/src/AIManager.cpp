#include <stdafx.h>
#include <GameElements/AIManager.h>

namespace GameElements
{
	AIManager::AIManager (vector<AiAgent*> opponents, vector<AiAgent*> controlled) : controlledUnits(controlled), opponentUnits(opponents)
	{
	}

	void AIManager::onMessage(System::DestructionMessage<AiAgent> const& msg)
	{
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
		for(int i=0;i<controlledUnits.size();i++)
		{
			assignUnitTarget(controlledUnits[i]);
		}
	}

	void AIManager::assignUnitTarget(AiAgent* agent)
	{
		Math::Vector3<Config::Real> minDistance = realMaxValue;
		Math::Vector3<Config::Real> shipPosition = agent->getPosition();
		AiAgent* newTarget = NULL;

		for(int i=0; i<opponentUnits.size();i++)
		{
			Math::Vector3<Config::Real> distance = opponentUnits[i]->getPosition() - shipPosition; 
			if( distance < minDistance)
			{
				minDistance = distance;
				newTarget = opponentUnits[i];
			}
		}

		agent->setTarget(newTarget);
	}
}