#ifndef _Math_Sphere_H
#define _Math_Sphere_H

#include <Math/Vector.h>

namespace Math
{
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \class	Sphere
	///
	/// \brief	A N dimensional sphere. 
	///
	/// \param Float the float type
	/// \param dimensions The number of dimensions
	///
	/// \author	Fabrice Lamarche, University Of Rennes 1
	/// \date	18/12/2009
	////////////////////////////////////////////////////////////////////////////////////////////////////
	template <class Float, int dimensions>
	class Sphere
	{
	protected:
		//! Circle center. 
		Math::Vector<Float, dimensions> m_center ;
		//! Circle radius. 
		Float m_radiusExp2 ;

	public:

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Sphere(Float radius=0.0, bool exp2=false)
		///
		/// \brief	Constructor. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	18/12/2009
		///
		/// \param	radius	The radius or radius^2 (if exp2 is true). 
		/// \param	exp2	true if radius is squared. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Sphere(Float radius=0.0, bool exp2=false)
		{
			if(exp2) { m_radiusExp2 = radius ; }
			else { m_radiusExp2 = radius * radius ; }
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Sphere(Math::Vector<Float,dimensions> const & center, Float radius, bool exp2=false)
		///
		/// \brief	Constructor. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	18/12/2009
		///
		/// \param 	center	the center. 
		/// \param	radius			The radius or radius^2 (if exp2 is true). 
		/// \param	exp2			true if radius is squared. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Sphere(Math::Vector<Float,dimensions> const & center, Float radius, bool exp2=false)
			: m_center(center)
		{
			if(exp2) { m_radiusExp2 = radius ; }
			else { m_radiusExp2 = radius * radius ; }
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Float radius() const
		///
		/// \brief	Returns the radius of the sphere. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	18/12/2009
		///
		/// \return	. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Float radius() const
		{ 
			return sqrt(m_radiusExp2) ; 
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Float radiusExp2() const
		///
		/// \brief	Returns the squared radius of the sphere 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	18/12/2009
		///
		/// \return	. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Float radiusExp2() const
		{
			return m_radiusExp2 ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Math::Vector<Float, dimensions> const & center() const
		///
		/// \brief	Returns the center of the sphere. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	18/12/2009
		///
		/// \return	. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Math::Vector<Float, dimensions> const & center() const
		{ return m_center ; }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	void setCenter(Math::Vector<Float, dimensions> const & newCenter)
		///
		/// \brief	Sets the center of the sphere. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	18/01/2010
		///
		/// \param [in]	newCenter the new center. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void setCenter(Math::Vector<Float, dimensions> const & newCenter)
		{
			m_center = newCenter ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	bool isInside(Math::Vector<Float, dimensions> const & point) const
		///
		/// \brief	Query if 'point' is inside the sphere. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	18/12/2009
		///
		/// \param [in,out]	point	the point. 
		///
		/// \return	true if inside, false if not. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		bool isInside(Math::Vector<Float, dimensions> const & point) const
		{
			Math::Vector<Float, dimensions> delta = point-m_center ;
			return delta*delta<=m_radiusExp2 ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	bool intersect(Sphere<Float, dimensions> const & circle) const
		///
		/// \brief	Tests of two spheres intersect. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	18/12/2009
		///
		/// \param [in,out]	circle	the circle. 
		///
		/// \return	true if the spheres intersect, false if not. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		bool intersect(Sphere<Float, dimensions> const & circle) const
		{
			Float d2 = (m_center-circle.m_center).norm2() ;
			Float r2 = (radius()+circle.radius()) ;
			r2 *= r2 ;
			return d2<r2 ;
		}
	};

}


#endif