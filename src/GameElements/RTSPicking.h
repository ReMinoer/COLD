#ifndef _GameElements_RTSPicking_H
#define _GameElements_RTSPicking_H

#include <Ogre/SelectionBuffer.h>
#include <Ogre/OgreRenderWindow.h>
#include <OIS/OISMouse.h>
#include <OgreFramework/PickableObject.h>
#include <OgreFramework/Picking.h>
#include <GameElements\AiAgent.h>

namespace GameElements
{
	class RTSPicking: public OgreFramework::Picking
	{
	protected :
		OIS::MouseButtonID m_rightButton;
		Ogre::SelectionBuffer * mSelectionBuffer;
	public:

		RTSPicking (Ogre::RenderWindow *renderWindow, Ogre::SceneManager * sceneManager, Ogre::Camera * camera, OIS::MouseButtonID buttonId);
		void update(const OIS::MouseEvent &arg, OIS::MouseButtonID id);

	};
}

#endif