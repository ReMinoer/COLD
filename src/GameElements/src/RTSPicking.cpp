#include <stdafx.h>
#include <GameElements\RTSPicking.h>
#include <OgreFramework/PickableObject.h>

namespace GameElements
{
RTSPicking::RTSPicking( Ogre::RenderWindow *renderWindow, Ogre::SceneManager * sceneManager, Ogre::Camera * camera, OIS::MouseButtonID buttonId, OIS::MouseButtonID buttonIdright,System::MessageEmitter<AiAgent::SelectedAiAgentMessage> *emitter, System::MessageEmitter<AiAgent::UnselectedAiAgentMessage> * emitterUnSelect  ) 
		: Picking(sceneManager, camera, buttonId), m_rightButton(buttonIdright), MessageListener<AiAgent::SelectedAiAgentMessage>(emitter), MessageListener<AiAgent::UnselectedAiAgentMessage>(emitterUnSelect)
	{
		mSelectionBuffer = new Ogre::SelectionBuffer(sceneManager, camera, renderWindow);
		agentSelected = NULL;
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
			mMovableFound = it->movable && it->movable->getName() == "scene0Box001";
			if (mMovableFound)
			{
				Ogre::Vector3 tmp = mouseRay.getPoint(it->distance);
				*destination = Math::Vector3<Config::Real> (tmp.x, tmp.y, tmp.z);
				return true;
			}
		}
		return false;
	}

	void RTSPicking::update( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
	{
		Ogre::Entity *selectedEntity = mSelectionBuffer->OnSelectionClick(arg.state.X.abs, arg.state.Y.abs);
		lastbutton = id;
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
				
				notifySelected(selectedEntity) ;
				if( agentSelected != NULL)
				{	
					//move
					Math::Vector3<Config::Real> destination;
					if (getCoord(arg,&destination))
					{	
						agentSelected->setDestination(destination.projectZ());
					}
				}
				else
				{
					
				}
			

		}

	}
	
	void RTSPicking::onMessage(AiAgent::SelectedAiAgentMessage const& msg)
	{
		if (agentSelected == NULL || lastbutton == m_button) 
		{
			agentSelected = &msg.m_selected;
		}
		else if (lastbutton == m_rightButton)
		{
			attack(&msg.m_selected);
		}
	}

	void RTSPicking::onMessage(AiAgent::UnselectedAiAgentMessage const& msg)
	{
		agentSelected = NULL;
	}

	void RTSPicking::attack(AiAgent * target)
	{
		if (agentSelected->getTeam() != target->getTeam())
		{
			std::cout << "BOOOMMMM" << std::endl;
		}
		else 
		{	//suivre alié ?
			std::cout << "BOH NAN C 1 COPAIN" << std::endl;
		}
		
	}
}