#ifndef _GameElements_ConfigurationLoader_H
#define _GameElements_ConfigurationLoader_H

#include <TinyXML/tinyxml.h>
#include <GameElements/Map.h>
#include <GameElements/WeaponsArchetypes.h>
#include <GameElements/UnitsArchetypes.h>

namespace GameElements
{
	class ConfigurationLoader 
	{
	protected:
		/// \brief	The maps.
		::std::map<::std::string, Map *> m_maps ;
		/// \brief	The weapons archetypes.
		WeaponsArchetypes m_weaponsArchetypes ;
		/// \brief	The units archetypes.
		UnitsArchetypes m_unitsArchetypes ;

	public:

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	ConfigurationLoader::ConfigurationLoader(::std::string & file,
		/// 	Ogre::SceneManager * sceneManager)
		///
		/// \brief	Constructor.
		///
		/// \author	Fabrice Lamarche, university of Rennes 1
		/// \param [in,out]	file			The configuration file in XML format.
		/// \param [in,out]	sceneManager	The Ogre scene manager.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		ConfigurationLoader(const ::std::string & file, Ogre::SceneManager * sceneManager);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	void ConfigurationLoader::getMaps(::std::vector<const Map *> & maps) const
		///
		/// \brief	Gets the maps list.
		///
		/// \author	Fabrice Lamarche, university of Rennes 1
		/// \param	maps	The maps.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void getMaps(::std::vector<Map *> & maps) const
		{
			for(auto it=m_maps.begin(), end=m_maps.end() ; it!=end ; ++it)
			{
				maps.push_back(it->second) ;
			}
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Map * ConfigurationLoader::getMap(const std::string & name) const
		///
		/// \brief	Gets a map by name.
		///
		/// \author	Fabrice Lamarche, university of Rennes 1
		/// \param	name	The name of the map.
		///
		/// \return	null if it fails, else the map.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Map * getMap(const std::string & name) const
		{
			auto it = m_maps.find(name) ;
			if(it==m_maps.end()) { return NULL ; }
			return it->second ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	void ConfigurationLoader::getWeaponsArchetypes(::std::vector<const WeaponsArchetypes::Archetype *> & archetypes) const
		///
		/// \brief	Gets the weapons archetypes.
		///
		/// \author	Fabrice Lamarche, university of Rennes 1
		/// \param	archetypes	The archetypes.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void getWeaponsArchetypes(::std::vector<const WeaponsArchetypes::Archetype *> & archetypes) const
		{
			m_weaponsArchetypes.getArchetypeList(archetypes) ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	WeaponsArchetypes const & ConfigurationLoader::getWeaponsArchetypes() const
		///
		/// \brief	Gets the weapons archetypes.
		///
		/// \author	Fabrice Lamarche, university of Rennes 1
		/// \return	The weapons archetypes.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		WeaponsArchetypes const & getWeaponsArchetypes() const
		{
			return m_weaponsArchetypes ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	void ConfigurationLoader::getUnitsArchetypes(::std::vector<const UnitsArchetypes::Archetype *> & archetypes) const
		///
		/// \brief	Gets the units archetypes.
		///
		/// \author	Fabrice Lamarche, university of Rennes 1
		/// \param	archetypes	The archetypes.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void getUnitsArchetypes(::std::vector<const UnitsArchetypes::Archetype *> & archetypes) const
		{
			m_unitsArchetypes.getArchetypeList(archetypes) ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	UnitsArchetypes const & ConfigurationLoader::getUnitsArchetypes()
		///
		/// \brief	Gets the units archetypes.
		///
		/// \author	Fabrice Lamarche, university of Rennes 1
		/// \return	The units archetypes.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		UnitsArchetypes const & getUnitsArchetypes()
		{
			return m_unitsArchetypes ;
		}

	protected:
		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	void ConfigurationLoader::parseMaps( TinyXML::TiXmlElement * root,
		/// 	Ogre::SceneManager * sceneManager )
		///
		/// \brief	Parses maps.
		///
		/// \author	Fabrice Lamarche, university of Rennes 1
		/// \param [in,out]	root			the root element for the configuration file.
		/// \param [in,out]	sceneManager	The Ogre scene manager.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void parseMaps( TinyXML::TiXmlElement * root, Ogre::SceneManager * sceneManager );

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	void ConfigurationLoader::parseUnits( TinyXML::TiXmlElement * root )
		///
		/// \brief	Parse units.
		///
		/// \author	Fabrice Lamarche, university of Rennes 1
		/// \param [in,out]	root	the root element for the configuration file.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void parseUnits( TinyXML::TiXmlElement * root );

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	void ConfigurationLoader::parseWeapons( TinyXML::TiXmlElement * root )
		///
		/// \brief	Parse weapons.
		///
		/// \author	Fabrice Lamarche, university of Rennes 1
		/// \param [in,out]	root	the root element for the configuration file.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void parseWeapons( TinyXML::TiXmlElement * root );
	};
}

#endif