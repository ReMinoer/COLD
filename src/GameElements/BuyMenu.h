#ifndef _GameElements_BuyMenu_H
#define _GameElements_BuyMenu_H

#include <OGRE/SdkTrays.h>

namespace GameElements
{
	class BuyMenu
	{
	private:
		int _moneyMax;
		int _moneyActual;

	public:
		BuyMenu(int a_moneyMax) : _moneyMax(a_moneyMax), _moneyActual(a_moneyMax) {};
		void ShowSelectionMenu(OgreBites::SdkTrayManager* a_trayManager, int a_monayActual);
	};
}

#endif // _GameElements_BuyMenu_H