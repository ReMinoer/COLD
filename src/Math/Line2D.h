#ifndef _Math_Line2D_H
#define _Math_Line2D_H

#include <math.h>
#include <Math/Vector2.h>
#include <Math/Line.h>

namespace Math
{

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \class	Line2D
	///
	/// \brief	Line in 2D. 
	///
	/// \author	Fabrice Lamarche, University Of Rennes 1
	/// \date	20/12/2009
	////////////////////////////////////////////////////////////////////////////////////////////////////
	template <class Float>
	class Line2D : public Line<Float,2>
	{
	public:
		typedef enum { negativeSide  = -1, onLine  = 0, positiveSide  = 1 } Side ;

	protected: 
		//! the normal vector. 
		//Math::Vector<Float,2> m_normal ;
		//! value such as m_normal*(x,y)+m_c is the line equation. 
		Float m_c ;
		//! The second point defining the line. 
		Math::Vector2<Float> m_p2 ;

		inline Float factor(Line2D const & l) const ;

	public: 

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	inline Line2D()
		///
		/// \brief	Default constructor. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	20/12/2009
		////////////////////////////////////////////////////////////////////////////////////////////////////
		inline Line2D() ; // x-y=0 i.e. y=x

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	inline Line2D(Math::Vector2<Float> const & p1, Math::Vector2<Float> const & p2)
		///
		/// \brief	Constructor. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	20/12/2009
		///
		/// \param [in,out]	p1	the first point. 
		/// \param [in,out]	p2	the second point. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		inline Line2D(Math::Vector2<Float> const & p1, Math::Vector2<Float> const & p2) ;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Float a() const
		///
		/// \brief	Returns a such as a*x+b*y+c=0 is the line equation. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	20/12/2009
		///
		/// \return	. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Float a() const { return normal()[0] ; }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Float b() const
		///
		/// \brief	Returns b such as a*x+b*y+c=0 is the line equation. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	20/12/2009
		///
		/// \return	. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Float b() const { return normal()[1] ; }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Float c() const
		///
		/// \brief	Returns c such as a*x+b*y+c=0 is the line equation.
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	20/12/2009
		///
		/// \return	. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Float c() const { return m_c ; }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Math::Vector<Float, 2> const & p1() const
		///
		/// \brief	Returns the origin of the line. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	20/12/2009
		///
		/// \return	. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Math::Vector<Float, 2> const & p1() const
		{ return m_origin ; }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Math::Vector<Float, 2> const & p2() const
		///
		/// \brief	Returns the second point of the line. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	20/12/2009
		///
		/// \return	. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Math::Vector<Float, 2> const & p2() const
		{ return m_p2 ; }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	inline Math::Vector2<Float> normal() const
		///
		/// \brief	Returns the normal vector of this line. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	20/12/2009
		///
		/// \return	Return the normal vector of this line. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Math::Vector2<Float> normal() const ;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Side classify(Math::Vector2<Float> const & point) const
		///
		/// \brief	Classifies the point in its half space or on line. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	01/06/2010
		///
		/// \param [in,out]	point	the point to classify. 
		///
		/// \return	. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Side classify(Math::Vector2<Float> const & point) const
		{
			Float val = (point-m_origin)*normal() ;
			if(val>0) { return positiveSide ; }
			else if(val<0) { return negativeSide ; }
			return onLine ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	void setPositiveSide(Math::Vector2<Float> const & point)
		///
		/// \brief	Sets a positive side of the line i.e. forces the po. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	01/06/2010
		///
		/// \param [in,out]	point	the point. 
		////////////////////////////////////////////////////////////////////////////////////////////////////

		void setPositiveSide(Math::Vector2<Float> const & point)
		{
			if(classify(point)==negativeSide)
			{
				invertDirection() ;
			}
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	inline Math::Vector2<Float> colinear() const
		///
		/// \brief	Return the opposite of the normal. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	20/12/2009
		///
		/// \return	. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		inline Math::Vector2<Float> colinear() const ;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	inline bool intersect(Line2D const & l) const
		///
		/// \brief	Tests if the two lines intersect. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	20/12/2009
		///
		/// \param [in,out]	l	the. 
		///
		/// \return	true if it succeeds, false if it fails. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		inline bool intersect(Line2D const & l) const ;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	inline Math::Vector2<Float> operator*(Line2D const & l) const
		///
		/// \brief	Computes the intersection of the two lines. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	20/12/2009
		///
		/// \param [in,out]	l	the. 
		///
		/// \return	The result of the operation. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		inline Math::Vector2<Float> operator*(Line2D const & l) const ;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	inline Float distance(Math::Vector2<Float> const & v) const
		///
		/// \brief	Computes the distance between a point and this line. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	20/12/2009
		///
		/// \param [in,out]	v	the v. 
		///
		/// \return	. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		inline Float distance(Math::Vector2<Float> const & v) const ;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	inline Math::Vector2<Float> project(Math::Vector2<Float> const & v) const
		///
		/// \brief	Projects the point on this line. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	20/12/2009
		///
		/// \param [in,out]	v	the v. 
		///
		/// \return	The projection of 'v'. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		inline Math::Vector2<Float> project(Math::Vector2<Float> const & v) const ;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	inline Math::Vector2<Float> projectionNormal(Math::Vector2<Float> const & v) const
		///
		/// \brief	Returns the vector 'v2' such as project(v)+v2==v. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	20/12/2009
		///
		/// \param [in,out]	v	the v. 
		///
		/// \return	. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		inline Math::Vector2<Float> projectionNormal(Math::Vector2<Float> const & v) const ;    

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	inline bool belongs(Math::Vector2<Float> const & v) const
		///
		/// \brief	Tests if 'v' belongs to the line. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	20/12/2009
		///
		/// \param [in,out]	v	the v. 
		///
		/// \return	true if it succeeds, false if it fails. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		inline bool belongs(Math::Vector2<Float> const & v) const ;

		void invertDirection()
		{
			Line<Float,2>::invertDirection() ;
			m_c=-(normal()*m_origin) ;
		}

	} ;

	template <class Float>
	Line2D<Float>::Line2D()
		: /*m_normal(Math::Vector2<Float>((Float)sqrt(2.0), -(Float)sqrt(2.0))), */m_c(0.0), m_p2(1,1)
	{}  

	template <class Float>
	Line2D<Float>::Line2D(Math::Vector2<Float> const & p1, Math::Vector2<Float> const & p2)
		: Line<Float,2>(p1, p2-p1), m_p2(p2)
	{
		//m_normal = Math::Vector2<Float>(p2-p1).rotate90() ;
		m_c=-(normal()*p1) ;
		Float vectorNorm = (p1-p2).norm() ;
		//m_normal = m_normal/vectorNorm ;
		//m_c = m_c/vectorNorm ;
	}

	template <class Float>
	Float Line2D<Float>::factor(Line2D<Float> const & l) const
	{
		Math::Vector2<Float> thisNormal = normal() ;
		Math::Vector2<Float> thatNormal = l.normal() ;
		return thisNormal[0]*thatNormal[1]-thisNormal[1]*thatNormal[0] ;
	}

	template <class Float>
	bool Line2D<Float>::intersect(Line2D<Float> const & l) const
	{
		return factor(l)!=0.0 ;
	}

	template <class Float>
	Math::Vector2<Float> Line2D<Float>::operator*(Line2D<Float> const & s) const 
	{
		Float f = Float(1.0)/factor(s) ;
		Math::Vector2<Float> v1(s.normal()[1], -normal()[1]) ;
		Math::Vector2<Float> v2(-s.normal()[0], normal()[0]) ;
		Math::Vector2<Float> p(-m_c, -s.m_c) ;
		return Math::Vector2<Float>((v1*p)*f, (v2*p)*f) ;
	}

	template <class Float>
	Math::Vector2<Float> Line2D<Float>::normal() const 
	{
		return Math::Vector2<Float>(m_direction).rotate90() ;
	}

	template <class Float>
	Math::Vector2<Float> Line2D<Float>::colinear() const 
	{
		return normal().rotate270() ;
	}

	template <class Float>
	Float Line2D<Float>::distance(Math::Vector2<Float> const & v) const
	{
		return normal()*v+m_c ;
	}

	template <class Float>
	Math::Vector2<Float> Line2D<Float>::project(Math::Vector2<Float> const & v) const
	{
		return v-normal()*distance(v) ;
	}

	template <class Float>
	Math::Vector2<Float> Line2D<Float>::projectionNormal(Math::Vector2<Float> const & v) const
	{
		return normal()*distance(v) ;
	}

	template <class Float>
	bool Line2D<Float>::belongs(Math::Vector2<Float> const & v) const
	{
		return distance(v)==0.0 ;
	}
}

#endif
