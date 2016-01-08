#include <stdafx.h>
#include <GameElements\RTSPicking.h>

namespace GameElements
{
RTSPicking::RTSPicking( Ogre::RenderWindow *renderWindow, Ogre::SceneManager * sceneManager, Ogre::Camera * camera, OIS::MouseButtonID buttonId ) 
		: Picking(sceneManager, camera, buttonId)
	{
		mSelectionBuffer = new Ogre::SelectionBuffer(sceneManager, camera, renderWindow);
	}

	void RTSPicking::update( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
	{
		Ogre::Entity *selectedEntity ;
		selectedEntity = mSelectionBuffer->OnSelectionClick(arg.state.X.abs, arg.state.Y.abs) ;
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
				if(dynamic_cast<AiAgent*>(selectedEntity) != NULL)
				{
					//atk
				}
				else
				{
					//move
				}
			}

		}

	}
		
}