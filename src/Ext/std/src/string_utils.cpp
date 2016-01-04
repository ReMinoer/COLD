#include <stdafx.h>
#include <Ext/std/string_utils.h>


namespace Ext
{
	namespace std
	{
		bool endsWith(::std::string const & src, ::std::string const & end)
		{
			if(src.size()<end.size()) { return false ; }
			for(unsigned int cpt=1, count=(unsigned int)end.size() ; cpt<=count ; ++cpt)
			{
				if(src[src.size()-cpt] != end[end.size()-cpt])
				{
					return false ;
				}
			}
			return true ;
		}
	}
}