#ifndef _GameElements_AIManager_H
#define _GameElements_AIManager_H

#include <GameElements/AiAgent.h>
#include <System\MessageEmitter.h>
#include <vector>

namespace GameElements 
{
	class AIManager
	{
	private:
		vector<AiAgent*> opponentUnits;
		vector<AiAgent*> controlledUnits;

	public:
		AIManager (vector<AiAgent*> opponents, vector<AiAgent*> controlled);
		void onMessage(System::DestructionMessage<AiAgent> const& msg);
		void assignAllUnitsTarget();

	private:
		void assignUnitTarget(AiAgent* agent);
	};
}

#endif