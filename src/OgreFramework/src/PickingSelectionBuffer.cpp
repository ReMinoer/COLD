#include <stdafx.h>
#include <OgreFramework/PickingSelectionBuffer.h>

namespace OgreFramework
{


	//void PickingSelectionBuffer::notifySelected( Ogre::MovableObject * object )
	//{
	//	if(object==NULL) { return ; }		
	//	const ::std::map<Ogre::Node*, PickableObject*> & pickableObjects = *PickableObject::m_instances.getInstance() ;
	//	for(Ogre::Node * node = object->getParentNode() ; node!=NULL ; node = node->getParent())
	//	{
	//		::std::map<Ogre::Node*, PickableObject*>::const_iterator it = pickableObjects.find(node) ;
	//		if(it!=pickableObjects.end())
	//		{
	//			it->second->onSelect() ;
	//		}
	//	}
	//}

	//void PickingSelectionBuffer::notifyUnselected( Ogre::MovableObject * object )
	//{
	//	if(object==NULL) { return ; }		
	//	const ::std::map<Ogre::Node*, PickableObject*> & pickableObjects = *PickableObject::m_instances.getInstance() ;
	//	for(Ogre::Node * node = object->getParentNode() ; node!=NULL ; node = node->getParent())
	//	{
	//		::std::map<Ogre::Node*, PickableObject*>::const_iterator it = pickableObjects.find(node) ;
	//		if(it!=pickableObjects.end())
	//		{
	//			it->second->onUnselect() ;
	//		}
	//	}
	//}

	PickingSelectionBuffer::PickingSelectionBuffer( Ogre::RenderWindow *renderWindow, Ogre::SceneManager * sceneManager, Ogre::Camera * camera, OIS::MouseButtonID buttonId ) 
		: Picking(sceneManager, camera, buttonId)
		//m_sceneManager(sceneManager), m_camera(camera), m_button(buttonId), m_isActive(true), m_lastSelected(NULL)
	{
		mSelectionBuffer = new Ogre::SelectionBuffer(sceneManager, camera, renderWindow);
	}

	void PickingSelectionBuffer::update( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
	{
		//if(mSelectionBuffer)
		//	mSelectionBuffer->ShowOverlay(true);

		Ogre::Entity *selectedEntity ;

		if(m_isActive && id==m_button)
		{
			selectedEntity = mSelectionBuffer->OnSelectionClick(arg.state.X.abs, arg.state.Y.abs) ;
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
		
	}

	//void PickingSelectionBuffer::setActive( bool isActive )
	//{
	//	m_isActive = isActive ;
	//}

	//Ogre::MovableObject * PickingSelectionBuffer::getLastSelected() const
	//{
	//	return m_lastSelected ;
	//}
}