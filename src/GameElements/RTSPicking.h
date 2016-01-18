#ifndef _GameElements_RTSPicking_H
#define _GameElements_RTSPicking_H

#include <Ogre/SelectionBuffer.h>
#include <Ogre/OgreRenderWindow.h>
#include <OIS/OISMouse.h>
#include <OgreFramework/PickableObject.h>
#include <OgreFramework/Picking.h>
#include <GameElements\AiAgent.h>
#include <OGRE\OgreSceneQuery.h>
#include <System\MessageListener.h>

namespace GameElements
{
	class RTSPicking: public OgreFramework::Picking, System::MessageListener<AiAgent::SelectedAiAgentMessage>
	{
	protected :
		AiAgent* agentSelected;
		OIS::MouseButtonID m_rightButton;
		Ogre::SelectionBuffer * mSelectionBuffer;

		bool getCoord(const OIS::MouseEvent &arg, Math::Vector3<Config::Real> * destination);
	public:

		RTSPicking (Ogre::RenderWindow *renderWindow, Ogre::SceneManager * sceneManager, Ogre::Camera * camera, OIS::MouseButtonID buttonId, OIS::MouseButtonID buttonIdright, System::MessageEmitter<AiAgent::SelectedAiAgentMessage> * emitter);
		void update(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
		void onMessage(AiAgent::SelectedAiAgentMessage const& msg);
	};
}

#endif