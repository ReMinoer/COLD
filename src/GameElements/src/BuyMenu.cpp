#include <stdafx.h>

#include <GameElements/BuyMenu.h>



namespace GameElements
{
	BuyMenu::BuyMenu(int a_moneyMax) 
		: _moneyMax(a_moneyMax)
		, _moneyActual(a_moneyMax) 
		, m_purchasePanel(0)
	{}

	void BuyMenu::ShowSelectionMenu(OgreBites::SdkTrayManager* a_trayManager) 
	{
		// create a params panel for displaying purchase details
		Ogre::StringVector purchases;
		purchases.push_back("Money");
		purchases.push_back("Moustics");
		purchases.push_back("Crocos");
		purchases.push_back("Hippos");
		m_purchasePanel = a_trayManager->createParamsPanel(OgreBites::TL_CENTER, "PurchasePanel", 200, purchases);
		m_purchasePanel->setParamValue(0, Ogre::StringConverter::toString(_moneyActual));

		// create a select menu for purchase vehicle
		Ogre::StringVector tmp ;
		Ogre::DisplayString title = "Choose your unity ";
		tmp.push_back("Stop choice and start Game") ;
		tmp.push_back("Moustic -- 250") ;
		tmp.push_back("Croco -- 500") ;
		tmp.push_back("Hippo -- 1000") ;
		OgreBites::SelectMenu * menu1 = a_trayManager->createThickSelectMenu(OgreBites::TL_CENTER, "menu_unity", title, 250, 15, tmp) ;
	}

	void BuyMenu::HideSelectionMenu()
	{
		m_purchasePanel->hide();
	}

	void BuyMenu::BuyVehicle(const GameElements::UnitsArchetypes::Archetype * a_unit)
	{
		_moneyActual -= a_unit->m_cost;

		int nbMoustic = 0;
		int nbCroco = 0;
		int nbHippo = 0;

		::std::cout<< "Cost: " <<a_unit->m_cost<<", name: "<< a_unit->m_name<<::std::endl ;
		m_nbVehicle.push_back(a_unit->m_name);
		for(int i = 0; i < m_nbVehicle.size(); i++)
		{
			::std::cout<<"Name: "<< m_nbVehicle[i]<<::std::endl ;
			if(m_nbVehicle[i] == "MousticB")
				nbMoustic++;
			if(m_nbVehicle[i] == "CrocoB")
				nbCroco++;
			if(m_nbVehicle[i] == "HippoB")
				nbHippo++;
		}
		
		m_purchasePanel->setParamValue(0, Ogre::StringConverter::toString(_moneyActual));
		m_purchasePanel->setParamValue(1, Ogre::StringConverter::toString(nbMoustic));
		m_purchasePanel->setParamValue(2, Ogre::StringConverter::toString(nbCroco));
		m_purchasePanel->setParamValue(3, Ogre::StringConverter::toString(nbHippo));
	}
}