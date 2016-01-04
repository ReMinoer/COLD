#ifndef _GameElements_WeaponsArchetypes_H
#define _GameElements_WeaponsArchetypes_H

#include <Config/Real.h>

namespace GameElements
{
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \class	WeaponsArchetypes
	///
	/// \brief	Weapons archetypes used to instanciate weapons associated to vehicles.
	///
	/// \author	Fabrice Lamarche, university of Rennes 1
	////////////////////////////////////////////////////////////////////////////////////////////////////
	class WeaponsArchetypes
	{
	public: 

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \struct	Archetype
		///
		/// \brief	The weapon archetype.
		///
		/// \author	Fabrice Lamarche, university of Rennes 1
		////////////////////////////////////////////////////////////////////////////////////////////////////
		struct Archetype
		{
			/// name of the archetype
			::std::string m_name ;
			/// Strength of the bullets
			int m_strength ;
			/// Armor damages of the bullets
			int m_armorDamage ;
			/// Fire frequency
			Config::Real m_frequency ;
			/// Speed of the bullet
			Config::Real m_speed ;
			/// Spatial extent in case of explosive bullets
			Config::Real m_extent ;
			/// Type (straight or ballistic)
			::std::string m_type ;
			/// Range of fire
			Config::Real m_range ;
			/// Mesh of the fired bullet
			::std::string m_bulletMesh ;
			/// \brief	The scale factor applied to the mesh.
			Config::Real m_scale ;
		};

	protected:
		/// Map associating agent archetype names to their description
		::std::map<::std::string, Archetype> m_agentArchetypes ;

	public:

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	WeaponsArchetypes::WeaponsArchetypes()
		///
		/// \brief	Default constructor.
		///
		/// \author	Fabrice Lamarche, university of Rennes 1
		////////////////////////////////////////////////////////////////////////////////////////////////////
		WeaponsArchetypes()
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
		void addArchetype(const TinyXML::TiXmlElement * element) ;

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