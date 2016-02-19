#ifndef _GameElements_AnnilhationVictory_H
#define _GameElements_AnnilhationVictory_H

#include <GameElements\AiAgent.h>
#include <GameElements\IVictoryConditions.h>

namespace GameElements 
{
	class AnnilhationVictory : public IVictoryConditions
	{
	private:
		vector<AiAgent*> opponentUnits;
		vector<AiAgent*> controlledUnits;
		Team winningTeam;
		// Faire une map
	public:
		AnnilhationVictory (vector<AiAgent*> opponents, vector<AiAgent*> controlled);
		virtual Team isEnd();
		virtual void update();
		void onMessage(System::DestructionMessage<AiAgent> const& msg);

	};
}

#endif