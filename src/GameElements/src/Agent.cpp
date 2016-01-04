#include <stdafx.h>

#include <GameElements/Agent.h>
#include <Ext/Ogre/ComputeBoundingBox.h>
#include <OgreFramework/GlobalConfiguration.h>

namespace GameElements
{
	int Agent::getLifePoints() const
	{
		return m_lifePoints ;
	}

	int Agent::getArmor() const
	{
		return m_armorPoints ;
	}

	bool Agent::isDead() const
	{
		return m_lifePoints<0 ;
	}

	Config::Real Agent::getPerceptionRange() const
	{
		return m_perceptionRange ;
	}

	Config::Real Agent::getMaxSpeed() const
	{
		return m_speed ;
	}

	Agent::Agent(const UnitsArchetypes::Archetype * archetype, const WeaponsArchetypes::Archetype * weaponArchetype, bool computeCollisionMesh ) 
		: GameObject(OgreFramework::GlobalConfiguration::getGeometryLoader()->load(archetype->m_mesh, archetype->m_scale)),
		m_initialLifePoints(archetype->m_life), m_initialArmorPoints(archetype->m_armor), m_lifePoints(archetype->m_life), 
		m_armorPoints(archetype->m_armor), m_perceptionRange(archetype->m_perceptionRange), m_speed(archetype->m_speed),
		m_archetype(archetype), m_weapon(weaponArchetype)
	{
		m_perception = new Perception(m_archetype->m_perceptionRange);
		setPosition(Math::Vector3<Config::Real>(0.0,0.0,0.0)) ;
		m_weapon.addFilter(this) ;
		if(computeCollisionMesh)
		{
			// Computes the bounding box of the geometry
			Ogre::AxisAlignedBox boundingBox = Ext::Ogre::computeBoundingBox(m_entity) ;
			// Creates the collision mesh
			Math::Vector2<Config::Real> minV(boundingBox.getMinimum()[0], boundingBox.getMinimum()[1]) ;
			Math::Vector2<Config::Real> maxV(boundingBox.getMaximum()[0], boundingBox.getMaximum()[1]) ;
			Math::Triangle2D<Config::Real> triangle1(minV, maxV, Math::Vector2<Config::Real>(minV[0], maxV[1])) ;
			Math::Triangle2D<Config::Real> triangle2(minV, maxV, Math::Vector2<Config::Real>(maxV[0], minV[1])) ;
			// Adds shapes to the collision object associated to this agent
			addShape(Triggers::Shape(triangle1,0)) ;
			addShape(Triggers::Shape(triangle2,0)) ;
		}
	}

	const UnitsArchetypes::Archetype * Agent::getArchetype() const
	{
		return m_archetype ;
	}

	bool Agent::fire( Math::Vector2<Config::Real> const & target )
	{
		return m_weapon.fire(getPosition().projectZ(), target) ;
	}

	bool Agent::canFire() const
	{
		return m_weapon.canFire() ;
	}

	void Agent::setPosition( Math::Vector3<Config::Real> const & position )
	{
		GameObject::setPosition(position) ;
		m_perception->setPosition(position.projectZ()) ;
	}

	void Agent::setOrientation( Math::Vector2<Config::Real> const & velocityVector )
	{
		Config::Real radius, theta ;
		velocityVector.polarCoordinates(radius, theta) ;
		GameObject::setOrientation(0,0,theta-Math::piDiv2) ;
	}

	void Agent::destroy()
	{
		GameObject::destroy() ;
		m_perception->setActive(false) ;
		m_perception->reset() ;
	}
}