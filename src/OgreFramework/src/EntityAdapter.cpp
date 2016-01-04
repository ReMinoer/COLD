#include <stdafx.h>

#include <OgreFramework/EntityAdapter.h>
#include <System/ConstructionDestructionEmitter.h>
#include <OgreFramework/GlobalConfiguration.h>
#include <Ext/Ogre/NodeManipulation.h>

namespace OgreFramework
{
	

	Ogre::Vector3 EntityAdapter::convert( Math::Vector3<Config::Real> const & v )
	{
		return Ogre::Vector3(v[0], v[1], v[2]) ;
	}

	EntityAdapter::EntityAdapter( Ogre::SceneNode * entity ) : PickableObject(entity), m_entity(entity)
	{
		System::ConstructionDestructionEmitter<EntityAdapter>::sendConstruction(*this) ;
	}

	void EntityAdapter::setPosition( Math::Vector3<Config::Real> const & pos )
	{
		m_position=pos ;
		m_entity->setPosition(convert(pos)) ;
	}

	void EntityAdapter::setOrientation( Config::Real xAngle, Config::Real yAngle, Config::Real zAngle )
	{
		Ogre::Quaternion qx(Ogre::Radian(xAngle), Ogre::Vector3(1.0,0.0,0.0)) ;
		Ogre::Quaternion qy(Ogre::Radian(yAngle), Ogre::Vector3(0.0,1.0,0.0)) ;
		Ogre::Quaternion qz(Ogre::Radian(zAngle), Ogre::Vector3(0.0,0.0,1.0)) ;
		m_entity->setOrientation(qx*qy*qz) ;
	}

	EntityAdapter::~EntityAdapter()
	{
		System::ConstructionDestructionEmitter<EntityAdapter>::sendDestruction(*this) ;
		Ext::Ogre::destroyNode(OgreFramework::GlobalConfiguration::getSceneManager(), m_entity) ;
		//System::ConstructionDestructionEmitter<EntityAdapter>::getDestructionEmitter()->send(System::DestructionMessage<EntityAdapter>(*this)) ;
	}

	void EntityAdapter::onSelect()
	{
		PickableObject::onSelect() ;
 		m_entity->showBoundingBox(true) ;
	}

	void EntityAdapter::onUnselect()
	{
		PickableObject::onUnselect() ;
		m_entity->showBoundingBox(false) ;
	}
}