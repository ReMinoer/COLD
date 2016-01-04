#ifndef _Ext_TinyXML_Helpers_H
#define _Ext_TinyXML_Helpers_H

namespace Ext
{
	namespace TinyXML
	{
		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	static const char * getAttribute(const ::TinyXML::TiXmlElement * element,
		/// 	::std::string const & name)
		///
		/// \brief	Gets an attribute from an XML node.
		///
		/// \author	Fabrice Lamarche, university of Rennes 1
		/// \exception	::std::runtime_error	Thrown when a runtime error error condition occurs.
		///
		/// \param	element	The element.
		/// \param	name   	The name.
		///
		/// \return	null if it fails, else the attribute.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		static const char * getAttribute(const ::TinyXML::TiXmlElement * element, ::std::string const & name)
		{
			const char * value = element->Attribute(name.c_str()) ;
			if(value==NULL)
			{
				::std::cerr<<"Attribute "<<name<<" missing in element:"<<*element<<::std::endl ;
				throw ::std::runtime_error("Invalid XML file") ;
			}
			return value ;
		}
	}
}

#endif