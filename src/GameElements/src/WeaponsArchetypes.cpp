#include <stdafx.h>
#include <GameElements/WeaponsArchetypes.h>
#include <Ext/TinyXML/Helpers.h>

const  GameElements::WeaponsArchetypes::Archetype *  GameElements::WeaponsArchetypes::get(const ::std::string & archetypeName) const
{
	::std::map<::std::string, Archetype>::const_iterator it=m_agentArchetypes.find(archetypeName) ;
	if(it==m_agentArchetypes.end()) { return NULL ; }
	return &(it->second) ;
}

void GameElements::WeaponsArchetypes::addArchetype(const TinyXML::TiXmlElement * element)
{
	Archetype archetype ;
	archetype.m_name = Ext::TinyXML::getAttribute(element, "name"); //element->Attribute("name") ;
	archetype.m_strength = atoi(Ext::TinyXML::getAttribute(element, "strength")) ; //element->Attribute("strength")) ;
	archetype.m_armorDamage = atoi(Ext::TinyXML::getAttribute(element, "armorDamage")) ; //element->Attribute("armorDamage")) ;
	archetype.m_frequency = atof(Ext::TinyXML::getAttribute(element, "frequency")) ;//element->Attribute("frequency")) ;
	archetype.m_extent = atof(Ext::TinyXML::getAttribute(element, "extent")) ; //element->Attribute("extent")) ;
	archetype.m_type = Ext::TinyXML::getAttribute(element, "type") ; //element->Attribute("type") ;
	archetype.m_range = atof(Ext::TinyXML::getAttribute(element, "range")) ; //element->Attribute("range")) ;
	archetype.m_bulletMesh = Ext::TinyXML::getAttribute(element, "bulletMesh"); //element->Attribute("bulletMesh") ;
	archetype.m_scale = atof(Ext::TinyXML::getAttribute(element, "scale")) ; 
	archetype.m_speed = atof(Ext::TinyXML::getAttribute(element, "speed")) ;
	m_agentArchetypes.insert(::std::make_pair(archetype.m_name, archetype)) ;
}