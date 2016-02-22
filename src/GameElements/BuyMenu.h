#ifndef _GameElements_BuyMenu_H
#define _GameElements_BuyMenu_H

#include <OGRE/SdkTrays.h>
#include <GameElements/UnitsArchetypes.h>

namespace GameElements
{
	class BuyMenu
	{
	private:
		int _moneyMax;
		int _moneyActual;
		OgreBites::ParamsPanel* m_purchasePanel;
		OgreBites::Button* m_addMousticButton;
		OgreBites::Button* m_addCrocoButton;
		OgreBites::Button* m_addHippoButton;
		OgreBites::Button* m_closeMenuButton;
		::std::vector<::std::string> m_nbVehicle ;

	public:
		BuyMenu(int a_moneyMax = 0);
		void ShowSelectionMenu(OgreBites::SdkTrayManager* a_trayManager);
		void HideSelectionMenu(OgreBites::SdkTrayManager* a_trayManager);
		void BuyVehicle(const GameElements::UnitsArchetypes::Archetype * a_unit);
	};
}

#endif // _GameElements_BuyMenu_H