#ifndef _GameElements_IVictoryConditions_H
#define _GameElements_IVictoryConditions_H

#include <GameElements\AiAgent.h>

namespace GameElements 
{
	class IVictoryConditions
	{

	public:
		virtual Team isEnd() = 0;
		virtual void update() = 0;
	};
}

#endif