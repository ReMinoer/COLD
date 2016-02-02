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
		OgreBites::SelectMenu * menu1 = a_trayManager->createThickSelectMenu(OgreBites::TL_TOPLEFT, "menu_unity", piouuu + bla, 200, 15, tmp) ;
	}

	/*void BuyMenu::HideSelectionMenu(OgreBites::SdkTrayManager* a_trayManager)
	{

	}*/

	void BuyMenu::BuyVehicle(const GameElements::UnitsArchetypes::Archetype * a_unit)
	{
		_moneyActual -= a_unit->m_cost;

		::std::cout<< "Cost: " <<a_unit->m_cost<<", name: "<< a_unit->m_name<<::std::endl ;
	}
}