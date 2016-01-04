#ifndef _GameElements_Weapon_H
#define _GameElements_Weapon_H

#include <GameElements/WeaponsArchetypes.h>
#include <Math/Vector2.h>
#include <tbb/tick_count.h>
#include <Triggers/CollisionObject.h>


namespace GameElements
{
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \class	Weapon
	///
	/// \brief	Weapon.
	///
	/// \author	Fabrice Lamarche, university of Rennes 1
	////////////////////////////////////////////////////////////////////////////////////////////////////
	class Weapon
	{
	public:
		const WeaponsArchetypes::Archetype * m_archetype ;
		::tbb::tick_count m_lastFireDate ;
		/// \brief	Used to filter colisions with some objects.
		::std::set<Triggers::CollisionObject *> m_filter ;

	protected:

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	void Weapon::createBullet(Math::Vector2<Config::Real> const & origin,
		/// 	Math::Vector2<Config::Real> const & target) const
		///
		/// \brief	Creates a bullet from the archetype description.
		///
		/// \author	Fabrice Lamarche, university of Rennes 1
		/// \param	origin	The origin.
		/// \param	target	Target for the.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void createBullet(Math::Vector2<Config::Real> const & origin, Math::Vector2<Config::Real> const & target) const;

	public:

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Weapon::Weapon(const WeaponsArchetypes::Archetype * archetype) : m_archetype(archetype),
		/// 	m_lastFireDate(::tbb::tick_count::now())
		///
		/// \brief	Constructor.
		///
		/// \author	Fabrice Lamarche, university of Rennes 1
		/// \param	archetype	The archetype.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Weapon(const WeaponsArchetypes::Archetype * archetype);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	bool Weapon::fire(Math::Vector2<Config::Real> const & origin,
		/// 	Math::Vector2<Config::Real> const & target)
		///
		/// \brief	Fires a bullet from origin to target.
		///
		/// \author	Fabrice Lamarche, university of Rennes 1
		/// \param	origin	The origin fo the bullet trajectory.
		/// \param	target	Target of the bullet.
		///
		/// \return	true if a bullet if fired, false if not.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		bool fire(Math::Vector2<Config::Real> const & origin, Math::Vector2<Config::Real> const & target);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	bool Weapon::canFire() const
		///
		/// \brief	Determine if this weapon can fire now (handles fire frequency)
		///
		/// \author	Fabrice Lamarche, university of Rennes 1
		/// \return	true if it can fire, false if not.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		bool canFire() const;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	void Weapon::addFilter(CollisionObject::Pointer const & objectPtr)
		///
		/// \brief	Adds a filter notifying that the given object is removed from collision list.
		///
		/// \author	Fabrice Lamarche, university of Rennes 1
		/// \param	objectPtr	The object pointer.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void addFilter(Triggers::CollisionObject::Pointer const & objectPtr)
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
		/// \fn	void Weapon::removeFilter(CollisionObject::Pointer const & objectPtr)
		///
		/// \brief	Removes objectPtr from the filter list.
		///
		/// \author	Fabrice Lamarche, university of Rennes 1
		/// \param	objectPtr	The object pointer.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void removeFilter(Triggers::CollisionObject::Pointer const & objectPtr)
		{
			m_filter.erase(objectPtr.get()) ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	const WeaponsArchetypes::Archetype * Weapon::getArchetype() const
		///
		/// \brief	Gets the archetype.
		///
		/// \author	Fabrice Lamarche, university of Rennes 1
		/// \return	null if it fails, else the archetype.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		const WeaponsArchetypes::Archetype * getArchetype() const
		{
			return m_archetype ;
		}
	};
}

#endif