#ifndef _Ext_std_string_utils_H
#define _Ext_std_string_utils_H

#include <string>

namespace Ext
{
	namespace std
	{
		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	bool endsWith(::std::string const & src, ::std::string const & end)
		///
		/// \brief	Tests if a string ends with a given string.
		///
		/// \author	Fabrice Lamarche, university of Rennes 1
		/// \param	src	The string.
		/// \param	end	The tested end.
		///
		/// \return	true if src ends with end, false otherwise.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		bool endsWith(::std::string const & src, ::std::string const & end) ;
	}
}

#endif