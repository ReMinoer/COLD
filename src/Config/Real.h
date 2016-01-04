#ifndef _Config_Real
#define _Config_Real

#include <limits>

namespace Config
{

	///////////////////////////////////////////////////////////////////////////////////
	/// \brief Type of the floating point values.
	/// 
	/// \author F. Lamarche, University of Rennes 1.
	///////////////////////////////////////////////////////////////////////////////////
	typedef float Real ;

	/// Maximum value of the floating point value.
	static const Real realMaxValue = ::std::numeric_limits<Real>::max() ;

}

#endif