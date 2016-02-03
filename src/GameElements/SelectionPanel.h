#ifndef _GameElements_SelectionPanel_H
#define _GameElements_SelectionPanel_H

#include <GameElements\AiAgent.h>


namespace GameElements
{
	class SelectionPanel 
	{
	private :
		AiAgent * m_agent;
		OgreBites::SdkTrayManager* m_trayManager;
		OgreBites::ParamsPanel * m_menu;
	public:
		
	SelectionPanel(OgreBites::SdkTrayManager* trayManager);
	void selected(AiAgent * agent);
	void unselected();
	void update();
	
	};
}

#endif