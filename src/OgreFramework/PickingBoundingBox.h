#ifndef _OgreFramework_PickingBoundingBox_H
#define _OgreFramework_PickingBoundingBox_H

#include <OgreFramework/PickingBoundingBox.h>

#include <OgreFramework/Picking.h>

namespace OgreFramework
{
	class PickingBoundingBox : public Picking
	{
	protected:
		///< The ray scene query object
		Ogre::DefaultRaySceneQuery m_raySceneQuery ;

	public:
		PickingBoundingBox(Ogre::SceneManager * sceneManager, Ogre::Camera * camera, OIS::MouseButtonID buttonId)
			: Picking(sceneManager, camera, buttonId), m_raySceneQuery(sceneManager)
		{
			assert(sceneManager!=NULL) ;
			assert(camera!=NULL) ;
			m_raySceneQuery.setSortByDistance(true) ;			
		}

		virtual void update(const OIS::MouseEvent &arg, OIS::MouseButtonID id) 
		{
			if(m_isActive && id==m_button)
			{
				Ogre::Ray mouseRay = m_camera->getCameraToViewportRay(  arg.state.X.abs/float(arg.state.width), arg.state.Y.abs/float(arg.state.height) );
				Ogre::RaySceneQuery & mRaySceneQuery = m_raySceneQuery ;
				mRaySceneQuery.setRay(mouseRay);
				//mRaySceneQuery.setQueryTypeMask(Ogre::SceneManager::WORLD_GEOMETRY_TYPE_MASK) ;
				//mRaySceneQuery.setWorldFragmentType(Ogre::SceneQuery::WFT_SINGLE_INTERSECTION) ;
				Ogre::RaySceneQueryResult& result = mRaySceneQuery.execute();
				Ogre::RaySceneQueryResult::iterator iter = result.begin();
				if(iter!=result.end())
				{	
					Ogre::MovableObject * object = iter->movable ;
					if(object!=m_lastSelected)
					{
						notifyUnselected(m_lastSelected) ;
					}
					m_lastSelected = object ;
					notifySelected(object); 
					::std::cout<<"Picking on object: "<<object->getName()<<::std::endl ;
					//::std::cout<<"Intersection: "<<iter->worldFragment->singleIntersection<<::std::endl ;
				}
				else
				{
					if(m_lastSelected!=NULL)
					{
						notifyUnselected(m_lastSelected) ;
					}
					m_lastSelected = NULL ;
				}
			}
		}

	};
}

#endif