#include <stdafx.h>
#include <GameElements/Perception.h>

namespace GameElements
{


	Perception::Perception( Config::Real distance ) : CollisionObject(trigger), m_distance(distance)
	{
		updateShape() ;
	}

	Config::Real Perception::getDistance() const
	{
		return m_distance ;
	}

	void Perception::setDistance( Config::Real distance )
	{
		m_distance = distance ;
		updateShape() ;
	}

	const ::std::vector<Triggers::CollisionObject::Pointer> & Perception::perceivedAgents() const
	{
		return m_perceivedAgents ;
	}

	void Perception::reset()
	{
		m_perceivedAgents.erase(m_perceivedAgents.begin(), m_perceivedAgents.end()) ;
	}

	void Perception::setUnique()
	{
		::std::sort(m_perceivedAgents.begin(), m_perceivedAgents.end()) ;
		m_perceivedAgents.erase(::std::unique(m_perceivedAgents.begin(), m_perceivedAgents.end()), m_perceivedAgents.end()) ;
	}

	void Perception::setPosition( const Math::Vector2<Config::Real> & position )
	{
		Triggers::CollisionObject::setTransform(Math::Matrix3x3<Config::Real>::getTranslationHomogeneous(position)) ;
	}

	void Perception::onCollision( const CollisionMessage &message )
	{
		m_perceivedAgents.push_back(message.other(this)) ;
	}
}