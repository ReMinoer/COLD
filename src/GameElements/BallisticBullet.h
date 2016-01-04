#ifndef _GameElements_BallisticBullet_H
#define _GameElements_BallisticBullet_H

#include <GameElements/BulletBase.h>
// In CPP
#include <GameElements/PlayParticleSystem.h>
#include <OgreFramework/GlobalConfiguration.h>
#include <GameElements/Agent.h>

namespace GameElements
{
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \class	BallisticBullet
	///
	/// \brief	Bullet following a ballistic trajectory and exploding on ground impact. This bullet can 
	/// 		not be destroyed until its target is reached.
	///
	/// \author	Fabrice Lamarche, university of Rennes 1
	////////////////////////////////////////////////////////////////////////////////////////////////////
	class BallisticBullet : public BulletBase
	{
	public:

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \typedef	::boost::intrusive_ptr<BallisticBullet> Pointer
		///
		/// \brief	Defines an alias representing the pointer to this instance.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		typedef ::boost::intrusive_ptr<BallisticBullet> Pointer ;

	protected:
		/// \brief	The origin.
		Math::Vector2<Config::Real> m_origin ;
		/// \brief	The current position.
		Math::Vector2<Config::Real> m_position ;
		/// \brief	The targeted position.
		Math::Vector2<Config::Real> m_target ;
		/// \brief	The velocity.
		Config::Real m_speed ;
		/// \brief	The explosion range.
		Config::Real m_explosionRange ;

	public:

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	BallisticBullet::BallisticBullet(Ogre::SceneNode * node, int lifePoints, int armorPoints,
		/// 	Math::Vector2<Config::Real> const & origin, Config::Real speed,
		/// 	Math::Vector2<Config::Real> const & target, Config::Real explosionRange)
		///
		/// \brief	Constructor.
		///
		/// \author	Fabrice Lamarche, university of Rennes 1
		/// \param [in,out]	node  	The graphical representation of the bullet.
		/// \param	lifePoints	  	The life points lost by an agent when hit by the bullet.
		/// \param	armorPoints   	The armor points lost by an agent when hit by the bullet.
		/// \param	origin		  	The origin of the bullet.
		/// \param	speed		  	The speed fo the bullet.
		/// \param	target		  	The target position of the bullet.
		/// \param	explosionRange	The explosion range.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		BallisticBullet(Ogre::SceneNode * node, int lifePoints, int armorPoints, Math::Vector2<Config::Real> const & origin, Config::Real speed, Math::Vector2<Config::Real> const & target, Config::Real explosionRange);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	virtual void BallisticBullet::update(Config::Real const & dt)
		///
		/// \brief	Updates the given dt.
		///
		/// \author	Fabrice Lamarche, university of Rennes 1
		/// \param	dt	The dt.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual void update(Config::Real const & dt);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	virtual Math::Vector2<Config::Real> BulletBase::getVelocity() const = 0;
		///
		/// \brief	Gets the velocity of the bullet.
		///
		/// \author	Fabrice Lamarche, university of Rennes 1
		/// \return	The velocity.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual Math::Vector2<Config::Real> getVelocity() const;
	};
}

#endif