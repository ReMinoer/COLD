#ifndef _GameElements_StraightBullet_H
#define _GameElements_StraightBullet_H

#include <GameElements/BulletBase.h>
// In CPP
#include <GameElements/PlayParticleSystem.h>
#include <OgreFramework/GlobalConfiguration.h>

namespace GameElements
{
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \class	StraightBullet
	///
	/// \brief	Bullet with a straight trajectory. As soon as the bullet hit an object, it removes life
	/// 		and armor points and is destroyed. This bullet as a range. If this range is reached without
	/// 		collision, the bullet dies. Moreover, this bullet can be destroyed by other bullets. 
	///
	/// \author	Fabrice Lamarche, university of Rennes 1
	////////////////////////////////////////////////////////////////////////////////////////////////////
	class StraightBullet : public BulletBase
	{
	public:

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \typedef	::boost::intrusive_ptr<StraightBullet> Pointer
		///
		/// \brief	Defines an alias representing the pointer to this type of object.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		typedef ::boost::intrusive_ptr<StraightBullet> Pointer ;

	protected:
		/// \brief	The origin.
		Math::Vector2<Config::Real> m_origin ;
		/// \brief	The current position.
		Math::Vector2<Config::Real> m_position ;
		/// \brief	The velocity.
		Math::Vector2<Config::Real> m_velocity ;
		/// \brief	The range.
		Config::Real m_range ;

	public:

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	StraightBullet::StraightBullet(Ogre::SceneNode * node, int lifePoints, int armorPoints,
		/// 	Math::Vector2<Config::Real> const & origin, Math::Vector2<Config::Real> const & velocity,
		/// 	Config::Real range);
		///
		/// \brief	Constructor.
		///
		/// \author	Fabrice Lamarche, university of Rennes 1
		/// \param [in,out]	node	The node of the graphical representation.
		/// \param	lifePoints  	The life points removed by the bullet.
		/// \param	armorPoints 	The armor points removed by the bullet.
		/// \param	origin			The origin of the trajectory.
		/// \param	velocity		The velocity.
		/// \param	range			The range.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		StraightBullet(Ogre::SceneNode * node, int lifePoints, int armorPoints, 
					   Math::Vector2<Config::Real> const & origin, Math::Vector2<Config::Real> const & velocity, Config::Real range);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	virtual void StraightBullet::update(Config::Real const & dt);
		///
		/// \brief	Updates with the given dt.
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