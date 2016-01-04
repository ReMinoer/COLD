#ifndef _OgreFramework_EntityAdapter_H
#define _OgreFramework_EntityAdapter_H

#include <OGRE/OgreEntity.h>
#include <OGRE/OgreSceneNode.h>
#include <Config/Real.h>
#include <Math/Vector3.h>
#include <OgreFramework/PickableObject.h>

namespace OgreFramework
{
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \class	EntityAdapter
	///
	/// \brief	This entity encapsulate 3D Ogre object to hide Ogre related classes from the application.
	/// 		
	/// This class sends
	///		\li a System::ConstructionMessage<OgreFramework::EntityAdapter> when an instance is constructed
	///		\li a System::DestructionMessage<OgreFramework::EntityAdapter> when an instance is destroyed
	///
	/// \author	Fabrice Lamarche, University of Rennes 1
	/// \date	23/11/2011
	////////////////////////////////////////////////////////////////////////////////////////////////////
	class EntityAdapter : public PickableObject
	{
	protected:
		///< The entity associated to this adapter
		Ogre::SceneNode * m_entity ;
		/// \brief	The position.
		Math::Vector3<Config::Real> m_position ;

	public:
		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	static Ogre::Vector3 EntityAdapter::convert(Math::Vector3<Config::Real> const & v)
		///
		/// \brief	Converts a Math::Vector3<Real> into a Ogre::Vector3 vector.
		///
		/// \author	Fabrice Lamarche, University of Rennes 1
		/// \date	23/11/2011
		///
		/// \param	v	The v.
		///
		/// \return	.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		static Ogre::Vector3 convert(Math::Vector3<Config::Real> const & v);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	EntityAdapter::EntityAdapter(Ogre::SceneNode * entity)
		///
		/// \brief	Constructor.
		///
		/// \author	Fabrice Lamarche, University of Rennes 1
		/// \date	23/11/2011
		///
		/// \param [in,out]	entity	If non-null, the entity associated to this adapter.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		EntityAdapter(Ogre::SceneNode * entity);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	EntityAdapter::~EntityAdapter()
		///
		/// \brief	Destructor.
		///
		/// \author	Fabrice Lamarche, University of Rennes 1
		/// \date	24/11/2011
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual ~EntityAdapter();

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	void EntityAdapter::setPosition(Math::Vector3<Config::Real> const & pos)
		///
		/// \brief	Sets the position of the entity.
		///
		/// \author	Fabrice Lamarche, University of Rennes 1
		/// \date	23/11/2011
		///
		/// \param	pos	The position.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual void setPosition(Math::Vector3<Config::Real> const & pos);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	const Math::Vector3<Config::Real> & EntityAdapter::getPosition() const
		///
		/// \brief	Gets the position.
		///
		/// \author	Fabrice Lamarche, university of Rennes 1
		/// \return	The position.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		const Math::Vector3<Config::Real> & getPosition() const
		{
			return m_position ;
		}


		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	void EntityAdapter::setOrientation(Config::Real xAngle, Config::Real yAngle,
		/// 	Config::realMaxValue zAngle)
		///
		/// \brief	Sets the orientation of the entity qiven Euler angles.
		///
		/// \author	Fabrice Lamarche, University of Rennes 1
		/// \date	23/11/2011
		///
		/// \param	xAngle	The X angle.
		/// \param	yAngle	The Y angle.
		/// \param	zAngle	The Z angle.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual void setOrientation(Config::Real xAngle, Config::Real yAngle, Config::Real zAngle);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	virtual void EntityAdapter::onSelect()
		///
		/// \brief	Called when this object is selected.
		///
		/// \author	Fabrice Lamarche, University of Rennes 1
		/// \date	26/11/2011
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual void onSelect();

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	virtual void EntityAdapter::onUnselect()
		///
		/// \brief Called when this object is unselected.
		///
		/// \author	Fabrice Lamarche, University of Rennes 1
		/// \date	26/11/2011
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual void onUnselect() ;
	};
}

#endif