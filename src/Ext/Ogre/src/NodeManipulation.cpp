#include <stdafx.h>
#include <Ext/Ogre/NodeManipulation.h>
#include <Ogre/OgreParticleSystem.h>

namespace Ext
{
	namespace Ogre
	{
		void destroyMovable(::Ogre::SceneManager * sceneManager, ::Ogre::SceneNode * node)
		{
			{
				::Ogre::SceneNode::ChildNodeIterator it = node->getChildIterator() ;
				while(it.hasMoreElements())
				{
					::Ogre::SceneNode * node = dynamic_cast<::Ogre::SceneNode*>(it.getNext()) ;
					if(node!=NULL)
					{
						destroyMovable(sceneManager, node) ;
					}
				}
			}
			{
				::Ogre::SceneNode::ObjectIterator it = node->getAttachedObjectIterator() ;
				while(it.hasMoreElements())
				{
					::Ogre::MovableObject * object = dynamic_cast<::Ogre::MovableObject *>(it.getNext()) ;
					if(object!=NULL)
					{
						sceneManager->destroyMovableObject(object) ;
					}
				}
			}
		}

		void destroyNode(::Ogre::SceneManager * sceneManager,::Ogre::SceneNode * node)
		{
			destroyMovable(sceneManager, node) ;
			dynamic_cast<::Ogre::SceneNode*>(node->getParent())->removeAndDestroyChild(node->getName()) ;
		}

		void setEmittingParticleSystems(::Ogre::Node * node, bool emitting)
		{
			::std::vector<::Ogre::ParticleSystem*> particleSystems ;
			particleSystems.reserve(16) ;
			findNodes(node, particleSystems) ;
			for(int cpt=0 ; cpt<particleSystems.size() ; ++cpt)
			{
				particleSystems[cpt]->setEmitting(emitting) ;
			}
		}

		bool areAliveParticles(::Ogre::Node * node) 
		{
			bool result = false ;
			::std::vector<::Ogre::ParticleSystem*> particleSystems ;
			particleSystems.reserve(16) ;
			findNodes(node, particleSystems) ;
			for(int cpt=0 ; cpt<particleSystems.size() ; ++cpt)
			{
				result |= particleSystems[cpt]->getNumParticles()!=0 ;
			}
			return result ;
		}
	}
}
