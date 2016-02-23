#include <stdafx.h>
#include <GameElements\AnnilhationVictory.h>

namespace GameElements
{
	AnnilhationVictory::AnnilhationVictory (map<Team,int> units) 
	{
		remainingUnits = units;
	}

	Team AnnilhationVictory::isEnd()
	{
		Team winner = Team::none;
		for(map<Team,int>::iterator it=remainingUnits.begin() ; it!=remainingUnits.end() ; ++it)
		{
			if(it->second != 0)
			{
				if(winner == Team::none)
				{
					winner = it->first;
				}
				else
				{
					return Team::none;
				}
			}
		}
		return winner;
	}

	void AnnilhationVictory::update()
	{

	}

	void AnnilhationVictory::onMessage(System::DestructionMessage<AiAgent> const& msg)
	{
		for(map<Team,int>::iterator it=remainingUnits.begin() ; it!=remainingUnits.end() ; ++it)
		{
			if(msg.m_object.getTeam() == it->first)
			{
				it->second = it->second -1;
			}
		}
	}
}