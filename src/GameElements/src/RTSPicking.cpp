#include <stdafx.h>
#include <GameElements\RTSPicking.h>
#include <OgreFramework/PickableObject.h>

namespace GameElements
{
RTSPicking::RTSPicking( Ogre::RenderWindow *renderWindow, Ogre::SceneManager * sceneManager, Ogre::Camera * camera, OIS::MouseButtonID buttonId, OIS::MouseButtonID buttonIdright,System::MessageEmitter<AiAgent::SelectedAiAgentMessage> *emitter, System::MessageEmitter<AiAgent::UnselectedAiAgentMessage> * emitterUnSelect, SelectionPanel * menu) 
		: Picking(sceneManager, camera, buttonId), m_rightButton(buttonIdright), MessageListener<AiAgent::SelectedAiAgentMessage>(emitter), MessageListener<AiAgent::UnselectedAiAgentMessage>(emitterUnSelect), m_menu(menu)
	{
		mSelectionBuffer = new Ogre::SelectionBuffer(sceneManager, camera, renderWindow);
		agentSelected = NULL;
	}

	bool RTSPicking::getCoord(const OIS::MouseEvent &arg, Math::Vector3<Config::Real> * destination)
	{
		bool mMovableFound(false);
		Ogre::Plane plan(Ogre::Vector3::UNIT_Z,0);
		Ogre::Ray mouseRay = m_camera->getCameraToViewportRay(arg.state.X.abs / float(arg.state.width),arg.state.Y.abs / float(arg.state.height));
		std::pair<bool, Real> result = mouseRay.intersects(plan);
		if(result.first) 
		{
			Ogre::Vector3 tmp = mouseRay.getPoint(result.second);
			*destination = Math::Vector3<Config::Real> (tmp.x, tmp.y, tmp.z);
			return true;
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
						agentSelected->setTarget(NULL);
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
			agentSelected->getCircle()->setVisible(true);
			m_menu->selected(agentSelected);
		}
		else if (lastbutton == m_rightButton)
		{
			attackTarget(&msg.m_selected);
		}
	}

	void RTSPicking::onMessage(AiAgent::UnselectedAiAgentMessage const& msg)
	{
		agentSelected = NULL;
		m_menu->unselected();
	}

	void RTSPicking::attackTarget(AiAgent * target)
	{
		if (agentSelected->getTeam() != target->getTeam())
		{
			agentSelected->setTarget(target);
			std::cout << "BOOOMMMM" << std::endl;
		}
		else 
		{	//suivre alié ?
			agentSelected->setDestination(target->getPosition().projectZ());
			std::cout << "BOH NAN C 1 COPAIN" << std::endl;
		}
		
	}

}