#ifndef _GameElements_Bullet_H
#define _GameElements_Bullet_H

#include <GameElements/GameObject.h>
#include <GameElements/Agent.h>

namespace GameElements
{
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \class	Bullet
	///
	/// \brief	Agent representing a bullet evolving in the world.
	///
	/// \author	Fabrice Lamarche, University of Rennes 1
	/// \date	26/11/2011
	////////////////////////////////////////////////////////////////////////////////////////////////////
	class Bullet : GameObject
	{
	public:
		typedef ::boost::intrusive_ptr<Bullet> Pointer ;

	private:
		///< The life points removed by this bullet
		const int m_lifePoints ;
		///< The armor points removed by this bullet
		const int m_armorPoints ;
		///< The detected collisions for this time step
		::std::vector<CollisionObject::Pointer> m_collisions ;

	protected:
		/// \brief	The start position of the bullet.
		Math::Vector2<Config::Real> m_startPosition ;
		///< The position of the bullet
		Math::Vector2<Config::Real> m_position ;
		///< The velocity vector of the bullet
		Math::Vector2<Config::Real> m_velocity ;
		/// \brief	The range of the bullet, it deseapers if no object is touched after that range.
		Config::Real m_range ;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	void Bullet::hit(CollisionObject * object)
		///
		/// \brief	When a bullet hits an agent, life and armor points are updated by calling this method.
		///
		/// \author	Fabrice Lamarche, University of Rennes 1
		/// \date	26/11/2011
		///
		/// \param [in,out]	object	If non-null, the object.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void hit(CollisionObject::Pointer object);

	public:

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Bullet::Bullet(Ogre::SceneNode * node, int lifePoints, int armorPoints,
		/// 	Math::Vector2<Config::Real> const & origin, Math::Vector2<Config::Real> const & velocity,
		/// 	Config::Real range)
		///
		/// \brief	Constructor.
		///
		/// \author	Fabrice Lamarche, University of Rennes 1
		/// \date	26/11/2011
		///
		/// \param	node	   	The scene node.
		/// \param	lifePoints 	The life points removed.
		/// \param	armorPoints	The armor points removed.
		/// \param	origin	   	The start position of the bullet.
		/// \param	velocity   	The velocity of the bullet.
		/// \param	range	   	The range of the bullet.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Bullet(Ogre::SceneNode * node, int lifePoints, int armorPoints, Math::Vector2<Config::Real> const & origin, Math::Vector2<Config::Real> const & velocity, Config::Real range);

		///////////////////////////////////////////////////////////////////////////////////
		/// \brief Callback method called when a collision is detected
		/// 
		/// \param message The collision information
		/// 
		/// \author F. Lamarche, University of Rennes 1.
		///////////////////////////////////////////////////////////////////////////////////
		virtual void onCollision(const CollisionMessage & message);

		///////////////////////////////////////////////////////////////////////////////////
		/// \brief The update method called at each frame.
		/// 
		///		This method handles position update, collision with Agents and agent life 
		///		update.
		///		
		///		Warning: the 3D geometric object position is not updated!
		/// 
		/// \param dt Time elapsed since last call.
		/// 
		/// \author F. Lamarche, University of Rennes 1.
		///////////////////////////////////////////////////////////////////////////////////
		virtual void update(Config::Real const & dt);
	};
}

#endif