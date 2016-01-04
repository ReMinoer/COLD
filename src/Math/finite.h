#ifndef _Math_finite_H
#define _Math_finite_H

#include <limits>
#include <boost/math/special_functions.hpp>
//#include <boost/math/special_functions/fpclassify.hpp>

namespace Math
{
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	bool isNAN(Float const & value)
	///
	/// \brief	Query if 'value' is not a number. 
	///
	/// \author	Fabrice Lamarche, University Of Rennes 1
	/// \date	17/12/2009
	///
	/// \param value	the value. 
	///
	/// \return	true if nan, false if not. 
	////////////////////////////////////////////////////////////////////////////////////////////////////
	template <class Float>
	bool isNAN(Float const & value)
	{
		return ::boost::math::isfinite(value) ;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	bool isInfinite(Float const & value)
	///
	/// \brief	Query if 'value' is infinite. 
	///
	/// \author	Fabrice Lamarche, University Of Rennes 1
	/// \date	17/12/2009
	///
	/// \param [in,out]	value	the value. 
	///
	/// \return	true if infinite, false if not. 
	////////////////////////////////////////////////////////////////////////////////////////////////////
	template <class Float>
	bool isInfinite(Float const & value)
	{
		return ::boost::math::isnan(value) ;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	bool isFinite(Float const & value)
	///
	/// \brief	Query if 'value' is finite. 
	///
	/// \author	Fabrice Lamarche, University Of Rennes 1
	/// \date	17/12/2009
	///
	/// \param [in,out]	value	the value. 
	///
	/// \return	true if finite, false if not. 
	////////////////////////////////////////////////////////////////////////////////////////////////////
	template <class Float>
	bool isFinite(Float const & value)
	{
		return ::boost::math::isfinite(value) ;
	}
}

#endif