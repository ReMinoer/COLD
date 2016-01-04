#ifndef _GameElements_Perception_H
#define _GameElements_Perception_H

#include <Triggers/CollisionObject.h>
#include <algorithm>

namespace GameElements 
{
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \class	Perception
	///
	/// \brief	Class handling the perception of an agent. The perception is a circle that should remain 
	/// 		centered on the agent position. The perception distance can be modified dynamically.
	/// 		
	/// \warning An instance of this class always must be created dynamically.
	///
	/// \author	Fabrice Lamarche, university of Rennes 1
	////////////////////////////////////////////////////////////////////////////////////////////////////
	class Perception : public Triggers::CollisionObject
	{
	public:

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \typedef	::boost::intrusive_ptr<Perception> Pointer
		///
		/// \brief	Defines an alias representing the pointer to this type of objects.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		typedef ::boost::intrusive_ptr<Perception> Pointer ;

	protected:
		Config::Real m_distance ;
		::std::vector<Triggers::CollisionObject::Pointer> m_perceivedAgents ;

		void updateShape()
		{
			// We reset the shape of the trigger
			Triggers::CollisionObject::resetShapes() ; 
			// We set the new shape
			this->addShape(Triggers::Shape(Math::Vector2<Config::Real>(0.0, 0.0), m_distance)) ;
		}

	public:

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Perception::Perception(Config::Real distance)
		///
		/// \brief	Constructor.
		///
		/// \author	Fabrice Lamarche, university of Rennes 1
		/// \param	distance	The dperception istance.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Perception(Config::Real distance);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Config::Real Perception::getDistance() const
		///
		/// \brief	Gets the perception distance.
		///
		/// \author	Fabrice Lamarche, university of Rennes 1
		/// \return	The distance.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Config::Real getDistance() const;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	void Perception::setDistance(Config::Real distance)
		///
		/// \brief	Sets the perception distance.
		///
		/// \author	Fabrice Lamarche, university of Rennes 1
		/// \param	distance	The distance.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void setDistance(Config::Real distance);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	const ::std::vector<Agent::Pointer> & Perception::perceivedAgents() const
		///
		/// \brief	Gets the perceived agents.
		///
		/// \author	Fabrice Lamarche, university of Rennes 1
		/// \return	.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		const ::std::vector<Triggers::CollisionObject::Pointer> & perceivedAgents() const;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	void Perception::reset()
		///
		/// \brief	Resets the perceived agents buffer. This method should be called each time perceived
		/// 		agents have been handled.
		///
		/// \author	Fabrice Lamarche, university of Rennes 1
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void reset();

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	void Perception::setUnique()
		///
		/// \brief	Ensures that the perception buffer contains only one instance of a perceived agent.
		/// 		This is useful if the perception process is not ran at each timestep.
		///
		/// \author	Fabrice Lamarche, university of Rennes 1
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void setUnique();

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	void Perception::setPosition(const Math::Vector2<Config::Real> & position)
		///
		/// \brief	This method changes the position of the perception trigger. It should be called each
		/// 		time the agent moves.
		///
		/// \author	Fabrice Lamarche, university of Rennes 1
		/// \param	position	The position.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void setPosition(const Math::Vector2<Config::Real> & position);

		virtual void onCollision(const CollisionMessage &message);
	};
}

#endif