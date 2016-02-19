#include <stdafx.h>
#include <GameElements\AnnilhationVictory.h>

namespace GameElements
{
	Team AnnilhationVictory::isEnd()
	{
		return Team::none;
	}

	void AnnilhationVictory::update()
	{

	}

	void AnnilhationVictory::onMessage(System::DestructionMessage<AiAgent> const& msg)
	{
		for(int i=0;i<controlledUnits.size();i++)
		{
			if(&msg.m_object == controlledUnits[i])
			{
				/*controlledUnits.erase(controlledUnits.begin()+i);
				if(
				return;*/
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
		isEnd();
	}
}