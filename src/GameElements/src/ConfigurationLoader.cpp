#include <stdafx.h>
#include <GameElements/ConfigurationLoader.h>

GameElements::ConfigurationLoader::ConfigurationLoader( const ::std::string & file, Ogre::SceneManager * sceneManager )
{
	TinyXML::TiXmlDocument document(file.c_str()) ;
	bool res = document.LoadFile() ;
	if(document.Error())
	{
		::std::cout<<"An error occurred while loading configuration file"<<::std::endl ;
		::std::cout<<document.ErrorDesc()<<::std::endl ;
		return ;
 	}
	TinyXML::TiXmlElement * root = document.RootElement() ;
	// Parses weapons
	parseWeapons(root);
	// Parses units
	parseUnits(root);
	// Parses maps
	parseMaps(root, sceneManager);
}

void GameElements::ConfigurationLoader::parseMaps( TinyXML::TiXmlElement * root, Ogre::SceneManager * sceneManager )
{
	::std::cout<<"-- Loading maps"<<::std::endl; 
	TinyXML::TiXmlElement * rootUnits = root->FirstChildElement("maps") ;
	for(TinyXML::TiXmlElement * element = rootUnits->FirstChildElement("map") ; element!=NULL ; element = element->NextSiblingElement("map") )
	{
		::std::cout<<element->Attribute("name")<<::std::endl ;
		Map * map = new Map(sceneManager, element) ;
		m_maps.insert(::std::make_pair(map->getName(), map)) ;
	}
}

void GameElements::ConfigurationLoader::parseUnits( TinyXML::TiXmlElement * root )
{
	::std::cout<<"-- Loading units"<<::std::endl ;
	TinyXML::TiXmlElement * rootUnits = root->FirstChildElement("units") ;
	for(TinyXML::TiXmlElement * element = rootUnits->FirstChildElement("unit") ; element!=NULL ; element = element->NextSiblingElement("unit") )
	{
		::std::cout<<element->Attribute("name")<<::std::endl ;
		m_unitsArchetypes.addArchetype(element) ;
	}
}

void GameElements::ConfigurationLoader::parseWeapons( TinyXML::TiXmlElement * root )
{
	::std::cout<<"-- Loading weapons"<<::std::endl ;
	TinyXML::TiXmlElement * rootWeapons = root->FirstChildElement("weapons") ;
	for(TinyXML::TiXmlElement * element = rootWeapons->FirstChildElement("weapon") ; element!=NULL ; element = element->NextSiblingElement("weapon") )
	{
		::std::cout<<element->Attribute("name")<<::std::endl ;
		m_weaponsArchetypes.addArchetype(element) ;
	}
}