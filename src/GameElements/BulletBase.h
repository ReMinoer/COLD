#ifndef _GameElements_BulletBase_H
#define _GameElements_BulletBase_H

#include <GameElements/GameObject.h>

namespace GameElements
{
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \class	BulletBase
	///
	/// \brief	Base class for bullets and missiles. This is the only class that is able to access agents
	/// 		life points and armor to reduce them. 
	///
	/// \author	Fabrice Lamarche, university of Rennes 1
	////////////////////////////////////////////////////////////////////////////////////////////////////
	class BulletBase : public GameObject
	{
	public:
		typedef ::boost::intrusive_ptr<BulletBase> Pointer ;

	private:
		///< The life points removed by this bullet
		const int m_lifePoints ;
		///< The armor points removed by this bullet
		const int m_armorPoints ;
		///< The detected collisions for this time step
		::std::vector<CollisionObject::Pointer> m_collisions ;
		/// \brief	Used to filter colisions with some objects.
		::std::set<const CollisionObject *> m_filter ;

	protected:

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	void BulletBase::hit(CollisionObject::Pointer object)
		///
		/// \brief	Hits the given object if the object is an agent and removes life and armor points. 
		/// 		Otherwise, do nothing.
		///
		/// \author	Fabrice Lamarche, university of Rennes 1
		/// \param	object	The object.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void hit(CollisionObject::Pointer object);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	const ::std::vector<CollisionObject> BulletBase::getCollisions() const
		///
		/// \brief	Gets the collisions detected after the last call to clearCollisions.
		///
		/// \author	Fabrice Lamarche, university of Rennes 1
		/// \return	The collisions.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		const ::std::vector<CollisionObject::Pointer> & getCollisions() const
		{
			return m_collisions ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	void BulletBase::clearCollisions()
		///
		/// \brief	Clears the collision vector.
		///
		/// \author	Fabrice Lamarche, university of Rennes 1
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void clearCollisions() 
		{
			m_collisions.erase(m_collisions.begin(), m_collisions.end()) ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	void BulletBase::setOrientation(Math::Vector2<Config::Real> const & velocityVector)
		///
		/// \brief	Sets the orientation of the element, aligned with the velocity vector.
		///
		/// \author	Fabrice Lamarche, university of Rennes 1
		/// \param	velocityVector	The velocity vector.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void setOrientation(Math::Vector2<Config::Real> const & velocityVector);

	public:

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	BulletBase::BulletBase(Ogre::SceneNode * node, int lifePoints, int armorPoints)
		///
		/// \brief	Constructor.
		///
		/// \author	Fabrice Lamarche, university of Rennes 1
		/// \param [in,out]	node	The node of the graphical representation.
		/// \param	lifePoints  	The life points removed by the bullet.
		/// \param	armorPoints 	The armor points removed by the bullet.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		BulletBase(Ogre::SceneNode * node, int lifePoints, int armorPoints);

		///////////////////////////////////////////////////////////////////////////////////
		/// \brief Callback method called when a collision is detected
		/// 
		/// \param message The collision information
		/// 
		/// \author F. Lamarche, University of Rennes 1.
		///////////////////////////////////////////////////////////////////////////////////
		virtual void onCollision(const CollisionMessage & message);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	virtual void BulletBase::destroy()
		///
		/// \brief	Destroys this object.
		///
		/// \author	Fabrice Lamarche, university of Rennes 1
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual void destroy();

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	void BulletBase::addFilter(CollisionObject::Pointer const & objectPtr)
		///
		/// \brief	Adds a filter notifying that the given object is removed from collision list.
		///
		/// \author	Fabrice Lamarche, university of Rennes 1
		/// \param	objectPtr	The object pointer.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void addFilter(CollisionObject::Pointer const & objectPtr)
		{
			m_filter.insert(objectPtr.get()) ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	template <class iterator> void BulletBase::addFilter(iterator begin, iterator const & end)
		///
		/// \brief	Adds filters for all the given objects.
		///
		/// \author	Fabrice Lamarche, university of Rennes 1
		/// \tparam	iterator	Type of the iterator.
		/// \param	begin	The begin.
		/// \param	end  	The end.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		template <class iterator>
		void addFilter(iterator begin, iterator const & end)
		{
			for( ; begin!=end ; ++begin)
			{
				addFilter(*begin) ;
			}
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	void BulletBase::removeFilter(CollisionObject::Pointer const & objectPtr)
		///
		/// \brief	Removes objectPtr from the filter list.
		///
		/// \author	Fabrice Lamarche, university of Rennes 1
		/// \param	objectPtr	The object pointer.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void removeFilter(CollisionObject::Pointer const & objectPtr)
		{
			m_filter.erase(objectPtr.get()) ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	virtual Math::Vector2<Config::Real> BulletBase::getVelocity() const = 0;
		///
		/// \brief	Gets the velocity of the bullet.
		///
		/// \author	Fabrice Lamarche, university of Rennes 1
		/// \return	The velocity.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual Math::Vector2<Config::Real> getVelocity() const = 0 ;
	};
}

#endif