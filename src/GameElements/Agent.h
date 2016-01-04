#ifndef _GameElements_Agent_H
#define _GameElements_Agent_H

#include <GameElements/GameObject.h>
#include <GameElements/UnitsArchetypes.h>
#include <GameElements/Weapon.h>
#include <OgreFramework/GeometryLoader.h>
#include <GameElements/Perception.h>

namespace GameElements
{
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \class	Agent
	///
	/// \brief	Agent class. An agent is an alive object of the game. It has life points and armor and can
	/// 		be damaged or killed. It is created with archetypes (Cf. UnitsArchetypes::Archetype). 
	/// 		When constructed, the agent loads its geometry and computes its collision shape based on
	/// 		the bounding box of its geometry.
	///
	/// \author	Fabrice Lamarche, University of Rennes 1
	/// \date	26/11/2011
	////////////////////////////////////////////////////////////////////////////////////////////////////
	class Agent : public GameObject
	{
	public:
		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \typedef	::boost::intrusive_ptr<Agent> Pointer
		///
		/// \brief	Defines an alias representing the pointer.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		typedef ::boost::intrusive_ptr<Agent> Pointer ;

	private:
		friend class Bullet ;
		friend class BulletBase ;

		///< The initial life points
		const int m_initialLifePoints ;
		///< The initial armor
		const int m_initialArmorPoints ;
		///< The current life points
		int m_lifePoints ;
		///< The current armor points
		int m_armorPoints ;
		/// \brief	The perception range.
		Config::Real m_perceptionRange ;
		/// \brief	The maximum speed.
		Config::Real m_speed ;


	protected:
		/// \brief	The weapon.
		Weapon m_weapon ;
		/// \brief	The perception of the agent.
		Perception::Pointer m_perception ;
		/// \brief	The archetype associated to this agent.
		const UnitsArchetypes::Archetype * m_archetype ;

	public:

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Agent::Agent(Ogre::SceneManager * sceneManager,
		/// 	const UnitsArchetypes::Archetype * archetype, bool computeCollisionMesh=true);
		///
		/// \brief	Constructor.
		///
		/// \author	Fabrice Lamarche, university of Rennes 1
		/// \param	archetype				The archetype of the unit used for initialization.
		/// \param	computeCollisionMesh	Do we have to compute collision mesh ? Please, note that the 
		/// 								collision mesh is computed with the bounding box of the object
		/// 								in its original position / orientation.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Agent(const UnitsArchetypes::Archetype * archetype, const WeaponsArchetypes::Archetype * weaponArchetype, bool computeCollisionMesh=true);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	int Agent::getLifePoints() const
		///
		/// \brief	Returns the life points.
		///
		/// \author	Fabrice Lamarche, University of Rennes 1
		/// \date	26/11/2011
		///
		/// \return	The life points.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		int getLifePoints() const;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	int Agent::getArmor() const
		///
		/// \brief	Gets the armor.
		///
		/// \author	Fabrice Lamarche, University of Rennes 1
		/// \date	26/11/2011
		///
		/// \return	The armor.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		int getArmor() const;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Config::Real Agent::getPerceptionRange() const
		///
		/// \brief	Gets the perception range.
		///
		/// \author	Fabrice Lamarche, university of Rennes 1
		/// \return	The calculated perception range.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Config::Real getPerceptionRange() const;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Config::Real Agent::getMaxSpeed() const
		///
		/// \brief	Gets the maximum speed.
		///
		/// \author	Fabrice Lamarche, university of Rennes 1
		/// \return	The maximum speed.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Config::Real getMaxSpeed() const;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	const UnitsArchetypes::Archetype * Agent::getArchetype() const
		///
		/// \brief	Gets the archetype associated to this agent.
		///
		/// \author	Fabrice Lamarche, university of Rennes 1
		/// \return	null if it fails, else the archetype.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		const UnitsArchetypes::Archetype * getArchetype() const;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	bool Agent::isDead() const
		///
		/// \brief	Query if this agent is dead.
		///
		/// \author	Fabrice Lamarche, University of Rennes 1
		/// \date	26/11/2011
		///
		/// \return	true if dead, false if not.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		bool isDead() const;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	bool Agent::fire(Math::Vector2<Config::Real> const & target)
		///
		/// \brief	Fires toward the given target.
		///
		/// \author	Fabrice Lamarche, university of Rennes 1
		/// \param	target	Target for the.
		///
		/// \return	true if it succeeds, false if it fails.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		bool fire(Math::Vector2<Config::Real> const & target);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	bool Agent::canFire() const
		///
		/// \brief	Determine if we can fire.
		///
		/// \author	Fabrice Lamarche, university of Rennes 1
		/// \return	true if we can fire, false if not.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		bool canFire() const;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	virtual void Agent::setPosition(Math::Vector3<Config::Real> const & position)
		///
		/// \brief	Sets the position of the agent. This method changes the graphical representation's position,
		/// 		the collision shape position and the perception circle position
		///
		/// \author	Fabrice Lamarche, university of Rennes 1
		/// \param	position	The new position.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual void setPosition(Math::Vector3<Config::Real> const & position) ;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	void BulletBase::setOrientation(Math::Vector2<Config::Real> const & velocityVector)
		///
		/// \brief	Sets the orientation of the element, aligned with the velocity vector.
		///
		/// \author	Fabrice Lamarche, university of Rennes 1
		/// \param	velocityVector	The velocity vector.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void setOrientation(Math::Vector2<Config::Real> const & velocityVector);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	virtual void Agent::destroy();
		///
		/// \brief	Destroys this object.
		///
		/// \author	Fabrice Lamarche, university of Rennes 1
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual void destroy();

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	virtual Math::Vector2<Config::Real> Agent::getVelocity() const = 0;
		///
		/// \brief	Gets the velocity of the agent.
		///
		/// \author	Fabrice Lamarche, university of Rennes 1
		/// \return	The velocity.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual Math::Vector2<Config::Real> getVelocity() const = 0 ;
	};
}

#endif