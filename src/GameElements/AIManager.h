#ifndef _GameElements_AIManager_H
#define _GameElements_AIManager_H

#include <GameElements/AiAgent.h>
#include <System\MessageEmitter.h>
#include <System\MessageListener.h>
#include <vector>

namespace GameElements 
{
	class AIManager : public System::MessageListener<System::DestructionMessage<AiAgent>>
	{
	private:
		vector<AiAgent*> opponentUnits;
		vector<AiAgent*> controlledUnits;

	public:
		AIManager ();
		void onMessage(System::DestructionMessage<AiAgent> const& msg);
		void assignAllUnitsTarget();

		void addUnitToControlledUnits(AiAgent* unit);
		void addUnitToOpponentUnits(AiAgent* unit);

	private:
		void assignUnitTarget(AiAgent* agent);

	};
}

#endif