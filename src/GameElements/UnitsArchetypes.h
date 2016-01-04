#ifndef _GameElements_UnitsArchetypes_H
#define _GameElements_UnitsArchetypes_H

#include <TinyXML/tinyxml.h>
#include <Config/Real.h>

namespace GameElements
{

	///////////////////////////////////////////////////////////////////////////////////
	/// \brief Class used to store / consult unit archetypes.
	///
	/// \author Fabrice Lamarche, university of Rennes 1.
	///////////////////////////////////////////////////////////////////////////////////
	class UnitsArchetypes
	{
	public:
		struct Archetype
		{
			/// Name of the archetype
			::std::string m_name ;
			/// Mesh file
			::std::string m_mesh ;
			/// \brief	The graphical representation scale factor
			Config::Real m_scale ;
			/// Cost of the vehicle
			int m_cost ;
			/// Range of the agent perception
			Config::Real m_perceptionRange ;
			/// Speed 
			Config::Real m_speed ;
			/// life points
			int m_life ;
			/// Armor points
			int m_armor ;
			/// Weapon type
			::std::string m_weapon ;
		};

	protected:
		/// Map associating agent archetype names to their description
		::std::map<::std::string, Archetype> m_agentArchetypes ;

	public:

		///////////////////////////////////////////////////////////////////////////////////
		/// \brief
		/// \author Fabrice Lamarche, university of Rennes 1.
		///////////////////////////////////////////////////////////////////////////////////
		UnitsArchetypes() 
		{}

		///////////////////////////////////////////////////////////////////////////////////
		/// \brief Creates a new agent from the given archetype name
		/// \param archetypeName The archetype name
		/// \return A new agent or NULL if the archetype name is unknown
		/// \author Fabrice Lamarche, university of Rennes 1.
		///////////////////////////////////////////////////////////////////////////////////
		const Archetype * get(const ::std::string & archetypeName) const;

		///////////////////////////////////////////////////////////////////////////////////
		/// \brief
		/// \param element The tiny xml element describing the archetype
		/// \author Fabrice Lamarche, university of Rennes 1.
		///////////////////////////////////////////////////////////////////////////////////
		void addArchetype(const TinyXML::TiXmlElement * element);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	void UnitsArchetypes::getArchetypeList(::std::vector<Archetype*> & archetypes)
		///
		/// \brief	Gets an archetype list.
		///
		/// \author	Fabrice Lamarche, university of Rennes 1
		/// \param [in,out]	archetypes	[in,out] If non-null, the archetypes.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void getArchetypeList(::std::vector<const Archetype*> & archetypes) const
		{
			for(auto it=m_agentArchetypes.begin(), end=m_agentArchetypes.end() ; it!=end ; ++it)
			{
				archetypes.push_back(&it->second) ;
			}
		}
	};

}

#endif