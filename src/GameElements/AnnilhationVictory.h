#ifndef _GameElements_AnnilhationVictory_H
#define _GameElements_AnnilhationVictory_H

#include <GameElements\AiAgent.h>
#include <GameElements\IVictoryConditions.h>
#include <map>

namespace GameElements 
{
	class AnnilhationVictory : public IVictoryConditions
	{
	private:
		map<Team,int> remainingUnits;

	public:
		AnnilhationVictory (map<Team,int> units);
		virtual Team isEnd();
		virtual void update();
		void onMessage(System::DestructionMessage<AiAgent> const& msg);

	};
}

#endif