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
		
		m_closeMenuButton = a_trayManager->createButton(OgreBites::TL_CENTER, "CloseMenuButton", "Close Menu") ;

		Ogre::StringVector purchases ;
		purchases.push_back("Money") ;
		purchases.push_back("Moustics") ;
		purchases.push_back("Crocos") ;
		purchases.push_back("Hippos") ;
		m_purchasePanel = a_trayManager->createParamsPanel(OgreBites::TL_CENTER, "PurchasePanel", 200, purchases) ;
		m_purchasePanel->setParamValue(0, Ogre::StringConverter::toString(_moneyActual)) ;
		
		m_addMousticButton = a_trayManager->createButton(OgreBites::TL_CENTER, "MousticButton", "Add Moustic") ;
		m_addCrocoButton = a_trayManager->createButton(OgreBites::TL_CENTER, "CrocoButton", "Add Croco") ;
		m_addHippoButton = a_trayManager->createButton(OgreBites::TL_CENTER, "HippoButton", "Add Hippo") ;
	}

	void BuyMenu::HideSelectionMenu(OgreBites::SdkTrayManager* a_trayManager)
	{
		m_closeMenuButton->hide() ;
		m_purchasePanel->hide() ;
		m_addMousticButton->hide() ;
		m_addCrocoButton->hide() ;
		m_addHippoButton->hide() ;
		
		a_trayManager->removeWidgetFromTray("CloseMenuButton") ;
		a_trayManager->removeWidgetFromTray("PurchasePanel") ;
		a_trayManager->removeWidgetFromTray("MousticButton") ;
		a_trayManager->removeWidgetFromTray("CrocoButton") ;
		a_trayManager->removeWidgetFromTray("HippoButton") ;
	}

	void BuyMenu::BuyVehicle(const GameElements::UnitsArchetypes::Archetype * a_unit)
	{
		int nbMoustic = 0 ;
		int nbCroco = 0 ;
		int nbHippo = 0 ;
		
		::std::cout<< "Cost: " <<a_unit->m_cost<<", name: "<< a_unit->m_name<<::std::endl ;
		::std::cout<< "Actual Money: " <<_moneyActual<<::std::endl ;
		if (_moneyActual >= a_unit->m_cost)
		{
			_moneyActual -= a_unit->m_cost ;

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
		else 
		{
			::std::cout<<"Not enough money"<<::std::endl ;
		}
	}
}