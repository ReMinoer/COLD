#include <stdafx.h>

#include <GameElements/BuyMenu.h>



namespace GameElements
{
	void BuyMenu::ShowSelectionMenu(OgreBites::SdkTrayManager* a_trayManager, int a_moneyActual) 
	{
		Ogre::StringVector tmp ;
		int piou = a_moneyActual;
		Ogre::DisplayString piouuu = "Choose your unity ";
		Ogre::DisplayString bla = std::to_string((long double)piou);
		tmp.push_back("Moustic -- 250") ;
		tmp.push_back("Croco -- 500") ;
		tmp.push_back("Hippo -- 1000") ;
		OgreBites::SelectMenu * menu1 = a_trayManager->createThickSelectMenu(OgreBites::TL_TOPLEFT, "menu_unity", piouuu + bla, 200, 15, tmp) ;
	}
}