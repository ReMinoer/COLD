#include <stdafx.h>

#include<GameElements\SelectionPanel.h>
#include <GameElements/AiAgent.h>

namespace GameElements
{
	
	SelectionPanel::SelectionPanel(OgreBites::SdkTrayManager* trayManager) : m_trayManager(trayManager) 
	{
		m_agent = NULL;
		Ogre::StringVector tmp ;
		tmp.push_back("vie");
		tmp.push_back("armure");
		tmp.push_back("vitesse");
		tmp.push_back("range d'attaque");
		tmp.push_back("puissance");
		tmp.push_back("vitesse d'attaque");
		tmp.push_back("type d'attaque");
		m_menu = m_trayManager->createParamsPanel(OgreBites::TL_RIGHT,"menu",175,tmp);
		m_trayManager->removeWidgetFromTray(m_menu);
		m_menu->hide();
	}
	void SelectionPanel::selected(AiAgent * agent)
	{
		m_agent = agent;
		m_trayManager->moveWidgetToTray(m_menu, OgreBites::TL_RIGHT, 0);
		m_menu->show();
		update();
	}

	void SelectionPanel::unselected()
	{
		m_trayManager->removeWidgetFromTray(m_menu);
		m_menu->hide();
		m_agent = NULL;
	}

	void SelectionPanel::update()
	{
		
		if(m_agent == NULL)
		{
			return;
		}
		if(m_agent->isDead())
		{
			unselected();
			return;
		}
		m_menu->setParamValue(0,Ogre::StringConverter::toString(m_agent->getLifePoints()));
		m_menu->setParamValue(1,Ogre::StringConverter::toString(m_agent->getArmor()));
		m_menu->setParamValue(2,Ogre::StringConverter::toString(m_agent->getMaxSpeed()));
		m_menu->setParamValue(3,Ogre::StringConverter::toString(m_agent->getWeapon().getArchetype()->m_range));
		m_menu->setParamValue(4,Ogre::StringConverter::toString(m_agent->getWeapon().getArchetype()->m_strength));
		m_menu->setParamValue(5,Ogre::StringConverter::toString(m_agent->getWeapon().getArchetype()->m_frequency));
		m_menu->setParamValue(6,m_agent->getWeapon().m_archetype->m_type);
	}
}