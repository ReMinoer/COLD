#include <stdafx.h>
#include <GameElements\RTSPicking.h>
#include <OgreFramework/PickableObject.h>

namespace GameElements
{
RTSPicking::RTSPicking( Ogre::RenderWindow *renderWindow, Ogre::SceneManager * sceneManager, Ogre::Camera * camera, OIS::MouseButtonID buttonId, OIS::MouseButtonID buttonIdright,System::MessageEmitter<AiAgent::SelectedAiAgentMessage> *emitter ) 
		: Picking(sceneManager, camera, buttonId), m_rightButton(buttonIdright), MessageListener(emitter)
	{
		mSelectionBuffer = new Ogre::SelectionBuffer(sceneManager, camera, renderWindow);
	}

	bool RTSPicking::getCoord(const OIS::MouseEvent &arg, Math::Vector3<Config::Real> * destination)
	{
		bool mMovableFound(false);
		Ogre::Ray mouseRay = m_camera->getCameraToViewportRay(arg.state.X.abs / float(arg.state.width),arg.state.Y.abs / float(arg.state.height));
		Ogre::RaySceneQuery* raySceneQuery = m_sceneManager->createRayQuery(mouseRay);
		raySceneQuery->setSortByDistance(true);
		Ogre::RaySceneQueryResult& result = raySceneQuery->execute();

		for (Ogre::RaySceneQueryResult::iterator it = result.begin(); it != result.end(); it++)
		{
			mMovableFound = it->movable;
			if (mMovableFound)
			{
				Ogre::Vector3 tmp =it->worldFragment->singleIntersection;
				*destination = Math::Vector3<Config::Real> (tmp.x, tmp.y, tmp.z);
				return true;
			}
		}
		return false;
	}

	void RTSPicking::update( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
	{
		Ogre::Entity *selectedEntity = mSelectionBuffer->OnSelectionClick(arg.state.X.abs, arg.state.Y.abs);
			
		if(m_isActive && id==m_button)
		{
			
			if(static_cast<Ogre::MovableObject*>(selectedEntity)!=m_lastSelected)
			{
				notifyUnselected(getLastSelected()) ;
			}
			if(selectedEntity!=0)
			{
				m_lastSelected = selectedEntity ;
				notifySelected(selectedEntity) ;
				::std::cout<<"Picking on object: "<<selectedEntity->getName()<<::std::endl ;
			}
		}
		if (m_isActive && id==m_rightButton)
		{
			if(dynamic_cast<AiAgent*>(m_lastSelected) != NULL)
			{
				if( agentSelected != NULL)
				{
					//atk
				}
				else
				{
					//move
					Math::Vector3<Config::Real> destination;
					if (getCoord(arg,&destination))
					{
						agentSelected->setDestination(destination.projectZ());
					}
				}
			}

		}

	}
	
	void RTSPicking::onMessage(AiAgent::SelectedAiAgentMessage const& msg)
	{
		agentSelected = &msg.m_selected;
	}
}