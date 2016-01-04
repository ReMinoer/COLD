#include <stdafx.h>
#include <Ogre/CollectEntities.h>

namespace Ogre
{
	void Ogre::collectEntities( Node * node, ::std::vector<Entity*> & entities )
	{
		Ogre::SceneNode * sceneNode = dynamic_cast<Ogre::SceneNode*>(node) ;
		if(sceneNode!=NULL)
		{
			Ogre::SceneNode::ObjectIterator it = sceneNode->getAttachedObjectIterator() ;
			while(it.hasMoreElements())
			{
				Ogre::MovableObject * current = it.getNext() ;
				Ogre::Entity * entity = dynamic_cast<Ogre::Entity*>(current) ;
				if(entity!=NULL) 
				{
					entities.push_back(entity) ;
				}
			}
		}

		Ogre::Node::ChildNodeIterator it=node->getChildIterator() ;
		while(it.hasMoreElements())
		{
			Ogre::Node * current = it.getNext() ;
			collectEntities(current, entities) ;
		}
	}
}
