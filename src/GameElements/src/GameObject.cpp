#include <stdafx.h>

#include <GameElements/GameObject.h>

namespace GameElements
{
	DesignPattern::StaticMember<System::MessageEmitter<GameObject::SelectedGameObjectMessage> > GameObject::m_selectedEmitter ;
	DesignPattern::StaticMember<System::MessageEmitter<GameObject::UnselectedGameObjectMessage> > GameObject::m_unselectedEmitter ;


	GameObject::GameObject(Ogre::SceneNode * node)
		: OgreFramework::EntityAdapter(node), m_position(0.0,0.0), m_orientation(0.0)
	{
		System::ConstructionDestructionEmitter<GameObject>::getConstructionEmitter()->send(System::ConstructionMessage<GameObject>(*this)) ;
	}

	GameObject::~GameObject()
	{
		System::ConstructionDestructionEmitter<GameObject>::getDestructionEmitter()->send(System::DestructionMessage<GameObject>(*this)) ;
	}

	void GameObject::onSelect()
	{
		OgreFramework::EntityAdapter::onSelect() ;
		getSelectedGameObjectEmitter()->send(SelectedGameObjectMessage(*this)) ;
	}

	void GameObject::onUnselect()
	{
		OgreFramework::EntityAdapter::onUnselect() ;
		getUnselectedGameObjectEmitter()->send(UnselectedGameObjectMessage(*this)) ;
	}

	System::MessageEmitter<GameObject::SelectedGameObjectMessage> * GameObject::getSelectedGameObjectEmitter()
	{
		return m_selectedEmitter.getInstance() ;
	}

	System::MessageEmitter<GameObject::UnselectedGameObjectMessage> * GameObject::getUnselectedGameObjectEmitter()
	{
		return m_unselectedEmitter.getInstance() ;
	}

	void GameObject::setPosition( Math::Vector3<Config::Real> const & position )
	{
		m_position = position.projectZ() ;
		updateCollisionShapeTransform() ;
		EntityAdapter::setPosition(position) ;
	}

	void GameObject::setOrientation( Config::Real angleX, Config::Real angleY, Config::Real angleZ )
	{
		m_orientation = angleZ ;
		updateCollisionShapeTransform() ;
		EntityAdapter::setOrientation(angleX, angleY, angleZ) ;
	}

	void GameObject::updateCollisionShapeTransform()
	{
		Math::Matrix3x3<Config::Real> transform = Math::Matrix3x3<Config::Real>::getTranslationHomogeneous(m_position)*Math::Matrix3x3<Config::Real>::getRotationHomogeneous(m_orientation) ;
		setTransform(transform) ;
	}
}