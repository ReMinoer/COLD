#include <stdafx.h>
#include <GameElements/UnitsArchetypes.h>
#include <Ext/TinyXML/Helpers.h>

const GameElements::UnitsArchetypes::Archetype * GameElements::UnitsArchetypes::get( const ::std::string & archetypeName ) const
{
	::std::map<::std::string, Archetype>::const_iterator it=m_agentArchetypes.find(archetypeName) ;
	if(it==m_agentArchetypes.end()) { return NULL ; }
	return &it->second ;
}

void GameElements::UnitsArchetypes::addArchetype( const TinyXML::TiXmlElement * element )
{
	Archetype archetype ;
	archetype.m_name = Ext::TinyXML::getAttribute(element, "name") ;
	archetype.m_mesh = Ext::TinyXML::getAttribute(element, "mesh") ;
	archetype.m_scale = atof(Ext::TinyXML::getAttribute(element, "scale")) ;
	archetype.m_cost = atoi(Ext::TinyXML::getAttribute(element, "cost")) ; 
	archetype.m_speed = atof(Ext::TinyXML::getAttribute(element, "speed")) ;
	archetype.m_perceptionRange = atof(Ext::TinyXML::getAttribute(element, "perceptionRange")) ; 
	archetype.m_speed = atof(Ext::TinyXML::getAttribute(element, "speed")) ; 
	archetype.m_life = atoi(Ext::TinyXML::getAttribute(element, "life")) ; 
	archetype.m_armor = atoi(Ext::TinyXML::getAttribute(element, "armor")) ; 
	archetype.m_weapon = Ext::TinyXML::getAttribute(element, "weapon") ;
	m_agentArchetypes.insert(::std::make_pair(archetype.m_name, archetype)) ;
}