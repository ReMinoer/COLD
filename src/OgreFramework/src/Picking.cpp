#include <stdafx.h>

#include <OgreFramework/Picking.h>
#include <OgreFramework/PickableObject.h>

namespace OgreFramework
{


	Picking::Picking( Ogre::SceneManager * sceneManager, Ogre::Camera * camera, OIS::MouseButtonID buttonId ) 
		: m_sceneManager(sceneManager), m_camera(camera), m_button(buttonId),/* m_raySceneQuery(sceneManager),*/ m_isActive(true), m_lastSelected(NULL)
	{
		//assert(sceneManager!=NULL) ;
		//assert(camera!=NULL) ;
		//m_raySceneQuery.setSortByDistance(true) ;
	}

	//void Picking::update( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
	//{
	//	if(m_isActive && id==m_button)
	//	{
	//		Ogre::Ray mouseRay = m_camera->getCameraToViewportRay(  arg.state.X.abs/float(arg.state.width), arg.state.Y.abs/float(arg.state.height) );
	//		Ogre::RaySceneQuery & mRaySceneQuery = m_raySceneQuery ;
	//		mRaySceneQuery.setRay(mouseRay);
	//		//mRaySceneQuery.setQueryTypeMask(Ogre::SceneManager::WORLD_GEOMETRY_TYPE_MASK) ;
	//		//mRaySceneQuery.setWorldFragmentType(Ogre::SceneQuery::WFT_SINGLE_INTERSECTION) ;
	//		Ogre::RaySceneQueryResult& result = mRaySceneQuery.execute();
	//		Ogre::RaySceneQueryResult::iterator iter = result.begin();
	//		if(iter!=result.end())
	//		{	
	//			Ogre::MovableObject * object = iter->movable ;
	//			if(object!=m_lastSelected)
	//			{
	//				notifyUnselected(m_lastSelected) ;
	//			}
	//			m_lastSelected = object ;
	//			notifySelected(object); 
	//			::std::cout<<"Picking on object: "<<object->getName()<<::std::endl ;
	//			//::std::cout<<"Intersection: "<<iter->worldFragment->singleIntersection<<::std::endl ;
	//		}
	//		else
	//		{
	//			if(m_lastSelected!=NULL)
	//			{
	//				notifyUnselected(m_lastSelected) ;
	//			}
	//			m_lastSelected = NULL ;
	//		}
	//	}
	//}

	void Picking::setActive( bool isActive )
	{
		m_isActive = isActive ;
	}

	Ogre::MovableObject * Picking::getLastSelected() const
	{
		return m_lastSelected ;
	}

	void Picking::notifySelected( Ogre::MovableObject * object )
	{
		if(object==NULL) { return ; }		

		// New version
		const ::std::map<Ogre::Entity*, PickableObject*> & pickableObjects = *PickableObject::m_pickableInstances.getInstance() ;
		auto it = pickableObjects.find((Ogre::Entity*)(object)) ;
		if(it!=pickableObjects.end())
		{
			it->second->onSelect() ;
		}

		// OLD Version (Bug)
		//const ::std::map<Ogre::Node*, PickableObject*> & pickableObjects = *PickableObject::m_instances.getInstance() ;
		//for(Ogre::Node * node = object->getParentNode() ; node!=NULL ; node = node->getParent())
		//{
		//	::std::map<Ogre::Node*, PickableObject*>::const_iterator it = pickableObjects.find(node) ;
		//	if(it!=pickableObjects.end())
		//	{
		//		it->second->onSelect() ;
		//	}
		//}
	}

	void Picking::notifyUnselected( Ogre::MovableObject * object )
	{
		if(object==NULL) { return ; }		

		// New version
		const ::std::map<Ogre::Entity*, PickableObject*> & pickableObjects = *PickableObject::m_pickableInstances.getInstance() ;
		auto it = pickableObjects.find((Ogre::Entity*)(object)) ;
		if(it!=pickableObjects.end())
		{
			it->second->onUnselect() ;
		}

		// Old version (Bug)
		//const ::std::map<Ogre::Node*, PickableObject*> & pickableObjects = *PickableObject::m_instances.getInstance() ;
		//for(Ogre::Node * node = object->getParentNode() ; node!=NULL ; node = node->getParent())
		//{
		//	::std::map<Ogre::Node*, PickableObject*>::const_iterator it = pickableObjects.find(node) ;
		//	if(it!=pickableObjects.end())
		//	{
		//		it->second->onUnselect() ;
		//	}
		//}
	}
}