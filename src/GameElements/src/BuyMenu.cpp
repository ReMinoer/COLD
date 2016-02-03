#include <stdafx.h>

#include <GameElements/BuyMenu.h>



namespace GameElements
{
	BuyMenu::BuyMenu(int a_moneyMax) : _moneyMax(a_moneyMax), _moneyActual(a_moneyMax) 
	{}

	void BuyMenu::ShowSelectionMenu(OgreBites::SdkTrayManager* a_trayManager) 
	{
		Ogre::StringVector tmp ;
		Ogre::DisplayString piouuu = "Choose your unity ";
		Ogre::DisplayString bla = std::to_string((long double)_moneyActual);
		tmp.push_back("Moustic -- 250") ;
		tmp.push_back("Croco -- 500") ;
		tmp.push_back("Hippo -- 1000") ;
		tmp.push_back("Stop choice and start Game") ;
		/*OgreBites::ParamsPanel * menu1 = a_trayManager->createParamsPanel(OgreBites::TL_CENTER, "DetailsPanel", 200, tmp);
		if (menu1->isVisible())   // if details panel is visible, then update its contents
			{
				menu1->setParamValue(0, Ogre::StringConverter::toString(250));
				menu1->setParamValue(1, Ogre::StringConverter::toString(500));
				menu1->setParamValue(2, Ogre::StringConverter::toString(1000));
			}*/
		OgreBites::SelectMenu * menu1 = a_trayManager->createThickSelectMenu(OgreBites::TL_CENTER, "menu_unity", piouuu + bla, 250, 15, tmp) ;
	}

	void BuyMenu::BuyVehicle(const GameElements::UnitsArchetypes::Archetype * a_unit)
	{
		_moneyActual -= a_unit->m_cost;

		::std::cout<< "Cost: " <<a_unit->m_cost<<", name: "<< a_unit->m_name<<::std::endl ;
	}
}