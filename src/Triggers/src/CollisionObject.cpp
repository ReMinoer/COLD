#include <stdafx.h>

#include <Triggers/CollisionObject.h>

namespace Triggers
{


	CollisionObject::CollisionObject(CollisionObjectType type)
		: m_isActive(true)
	{
		System::ConstructionDestructionEmitter<CollisionObject>::getConstructionEmitter()->send(System::ConstructionMessage<CollisionObject>(*this)) ;
		m_transform = Math::Matrix3x3<Config::Real>::getIdentity() ;
		m_type = type ;
	}

	CollisionObject::~CollisionObject()
	{
	}

	const Math::Matrix3x3<Config::Real> & CollisionObject::getTransform() const
	{
		return m_transform ;
	}

	void CollisionObject::setTransform( Math::Matrix3x3<Config::Real> const & tranform )
	{
		m_transform = tranform ;
		for(int cpt=0, size=m_shapes.size() ; cpt<size ; ++cpt)
		{
			m_shapes[cpt].setTransform(m_transform) ;
		}
	}

	void CollisionObject::addShape( const Shape & shape )
	{
		m_shapes.push_back(shape) ;
		m_shapes.back().applyTransform() ;
		m_shapes.back().setTransform(m_transform) ;
	}

	void CollisionObject::resetShapes()
	{
		m_shapes.erase(m_shapes.begin(), m_shapes.end()) ;
	}

	const ::std::vector<Shape> & CollisionObject::getShapes() const
	{
		return m_shapes ;
	}

	CollisionObject::CollisionMessage::CollisionMessage( CollisionObject::Pointer object1, CollisionObject::Pointer object2 ) : m_object1(object1), m_object2(object2)
	{

	}

	CollisionObject::Pointer CollisionObject::CollisionMessage::other( CollisionObject::Pointer object ) const
	{
		assert(object==m_object1 || object==m_object2) ;
		if(object==m_object1) { return m_object2 ; }
		return m_object1 ;
	}

	Math::BoundingBox2D<Config::Real> CollisionObject::getBoundingBox() const
	{
		Math::BoundingBox2D<Config::Real> result = m_shapes[0].getBoundingBox() ;
		for(int cpt=1, end=m_shapes.size() ; cpt<end ; ++cpt)
		{
			result = result+m_shapes[cpt].getBoundingBox() ;
		}
		return result ;
		//Math::BoundingBox2D<Config::Real> result = m_shapes[0].getTransformed(m_transform).getBoundingBox() ;
		//for(int cpt=1, end=m_shapes.size() ; cpt<end ; ++cpt)
		//{
		//	result = result+m_shapes[cpt].getTransformed(m_transform).getBoundingBox() ;
		//}
		//return result ;
	}

	void CollisionObject::setActive( bool isActive ) 
	{
		m_isActive = isActive ;
	}

	bool CollisionObject::isActive() const
	{
		return m_shapes.size()>0 && m_isActive ;
	}

	void CollisionObject::destroy()
	{
		System::ConstructionDestructionEmitter<CollisionObject>::getDestructionEmitter()->send(System::DestructionMessage<CollisionObject>(*this)) ;
	}
}