#ifndef _Ext_Ogre_NodeManipulation_H
#define _Ext_Ogre_NodeManipulation_H

#include <Ogre/OgreSceneNode.h>
#include <Ogre/OgreSceneManager.h>

namespace Ext
{
	namespace Ogre
	{
		void destroyMovable(::Ogre::SceneManager * sceneManager,::Ogre::SceneNode * node) ;

		void destroyNode(::Ogre::SceneManager * sceneManager, ::Ogre::SceneNode * node) ;

		void setEmittingParticleSystems(::Ogre::Node * node, bool emitting=false) ;

		bool areAliveParticles(::Ogre::Node * node) ;

		template <class Type>
		void findNodes(::Ogre::Node * node, ::std::vector<Type*> & nodes)
		{
			{
				::Ogre::SceneNode::ChildNodeIterator it = node->getChildIterator() ;
				while(it.hasMoreElements())
				{
					::Ogre::Node * node = it.getNext() ;
					findNodes(node, nodes) ;
					Type * filter = dynamic_cast<Type*>(node) ;
					if(filter!=NULL)
					{
						nodes.push_back(filter) ;
					}
				}
			}
			{
				::Ogre::SceneNode * sceneNode = dynamic_cast<::Ogre::SceneNode*>(node) ;
				if(sceneNode!=NULL)
				{
					::Ogre::SceneNode::ObjectIterator it = sceneNode->getAttachedObjectIterator() ;
					while(it.hasMoreElements())
					{
						Type * object = dynamic_cast<Type *>(it.getNext()) ;
						if(object!=NULL)
						{
							nodes.push_back(object) ;
						}
					}
				}
			}
		}
	}
}

#endif