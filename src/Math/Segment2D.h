#ifndef _Math_Segment2D_H
#define _Math_Segment2D_H

#include <Math/Line2D.h>
#include <Math/Segment.h>


namespace Math
{

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \class	Segment2D
	///
	/// \brief	2D Segment. 
	///
	/// \author	Fabrice Lamarche, University Of Rennes 1
	/// \date	18/12/2009
	////////////////////////////////////////////////////////////////////////////////////////////////////
	template <class Float>
	class Segment2D : public Segment<Float,2>
	{
	public:
		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \enum	Side
		///
		/// \brief	Values that represent the Side in which a point can lie. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		typedef enum { positiveSide=0, negativeSide=1, onLine=2 } Side ;

	protected:
		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	void delta(Math::Vector<Float, 2> & d, Float & n) const
		///
		/// \brief	Computes n and d such as n*d = m_points[1]-m_points[0] with d.norm()=1. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	20/12/2009
		///
		/// \param d. 
		/// \param n. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void delta(Math::Vector<Float, 2> & d, Float & n) const
		{
			//d = m_points[1]-m_points[0] ;
			//n = d.norm() ;
			//d = d/n ;
			d = direction() ;
			n = length() ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Float lineDistance(Math::Vector2<Float> const & p) const
		///
		/// \brief	Computes the distance fo 'p' to the line supporting the segment. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	20/12/2009
		///
		/// \param p	the point. 
		///
		/// \return	. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Float lineDistance(Math::Vector2<Float> const & p) const ;

	public:

		// -------------------------------------------------------------------------------------------------------------------------
		/** \name Constructor
		*/
		//@{

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	explicit Segment2D(Math::Vector2<Float> const & p1=Math::Vector2<Float>(),
		/// 	Math::Vector2<Float> const & p2=Math::Vector2<Float>())
		///
		/// \brief	Segment 2 d. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	20/12/2009
		///
		/// \param [in,out]	p1	the first point. 
		/// \param [in,out]	p2	the second point. 
		///
		/// \return	. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		explicit Segment2D(Math::Vector2<Float> const & p1=Math::Vector2<Float>(), Math::Vector2<Float> const & p2=Math::Vector2<Float>())
			: Segment<Float,2>(p1, p2)
		{}

		//@}

		// -------------------------------------------------------------------------------------------------------------------------
		/** \name Segment structure
		*/
		//@{

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	const Math::Vector<Float, 2> & p1() const
		///
		/// \brief	Returns the first vertex. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	20/12/2009
		///
		/// \return	. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		const Math::Vector<Float, 2> & p1() const
		{
			return m_points[0] ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	const Math::Vector<Float, 2> & p2() const
		///
		/// \brief	Returns the second vertex. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	20/12/2009
		///
		/// \return	. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		const Math::Vector<Float, 2> & p2() const
		{
			return m_points[1] ;
		}

		//@}

		// -------------------------------------------------------------------------------------------------------------------------
		/** \name Distances
		*/
		//@{

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Float distance(Segment2D const & seg) const
		///
		/// \brief	Compute the distance between two segments. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	18/12/2009
		///
		/// \param [in,out]	seg	the segment. 
		///
		/// \return	. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Float distance(Segment2D const & seg) const ;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Float distance(Math::Vector<Float, 2> const & point) const
		///
		/// \brief	Computes the distance between a point and the segment. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	18/12/2009
		///
		/// \param [in,out]	point	the point. 
		///
		/// \return	. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Float distance(Math::Vector<Float, 2> const & point) const
		{
			return Segment<Float,2>::distance(point) ;
		}

		//@}


		// -------------------------------------------------------------------------------------------------------------------------
		/** \name Intersection and closest points
		*/
		//@{

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	bool intersect(Segment2D const & s) const
		///
		/// \brief	Tests if the two segment intersect. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	18/12/2009
		///
		/// \param [in,out]	s	the. 
		///
		/// \return	true if the segments intersect, false if not. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		bool intersect(Segment2D const & s) const
		{
			return intersect(*this, s) ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	static bool intersect(Segment2D const & s1, Segment2D const & s2)
		///
		/// \brief	Tests if two segments intersect. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	18/12/2009
		///
		/// \param [in,out]	s1	the first Segment2D const &. 
		/// \param [in,out]	s2	the second Segment2D const &. 
		///
		/// \return	true if it succeeds, false if it fails. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		static bool intersect(Segment2D const & s1, Segment2D const & s2) ;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Math::Vector2<Float> closestPoint(Math::Vector2<Float> const & p) const
		///
		/// \brief	Computes the closest point on the segment. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	18/12/2009
		///
		/// \param [in,out]	p	the point. 
		///
		/// \return	. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Math::Vector2<Float> closestPoint(Math::Vector2<Float> const & p) const ;
		//@}

		// -------------------------------------------------------------------------------------------------------------------------
		/** \name Geometric transformations
		*/
		//@{

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Segment2D operator + (Math::Vector<Float, 2> const & trans) const
		///
		/// \brief	Translates the segment. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	18/12/2009
		///
		/// \param [in,out]	trans	the trans. 
		///
		/// \return	The result of the operation. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Segment2D operator + (Math::Vector<Float, 2> const & trans) const
		{
			return Segment2D(m_points[0]+trans, m_points[1]+trans) ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	bool operator==(Segment2D<Float> const & seg) const
		///
		/// \brief	Equality operator. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	13/06/2010
		///
		/// \param [in,out]	seg	the segment. 
		///
		/// \return	true if the parameters are considered equivalent. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		bool operator==(Segment2D<Float> const & seg) const
		{
			return m_points[0]==seg.m_points[0] && m_points[1]==seg.m_points[1] ;
		}

		//@}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Side side(Math::Vector<Float, 2> const & point) const
		///
		/// \brief	Returns the side on which the point lies.
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	20/12/2009
		///
		/// \param [in,out]	point	the point. 
		///
		/// \return	. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Side side(Math::Vector<Float, 2> const & point) const
		{
			Math::Vector2<Float> direction = m_points[1] - m_points[0] ;
			Math::Vector2<Float> direction90 = direction.rotate90() ;
			Math::Vector2<Float> delta = point - m_points[0] ;
			Float value = delta*direction90 ;
			if(value>0.0)
			{
				return positiveSide ;
			}
			else if(value<0.0)
			{
				return negativeSide ;
			}
			return onLine ;
		}

		// -------------------------------------------------------------------------------------------------------------------------
		/** \name Conversions
		*/
		//@{

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	operator Line2D<Float> () const
		///
		/// \brief	Converts the segment into a line. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	18/12/2009
		////////////////////////////////////////////////////////////////////////////////////////////////////
		operator Line2D<Float> () const
		{
			return Line2D<Float>(p1(), p2()) ;
		}

		//@}

	} ;
}


namespace Math
{

	template <class Float>
	Float Segment2D<Float>::distance(Segment2D<Float> const & seg) const
	{
		if(isDegenerated())
		{
			return seg.distance((*this)[0]) ;
		}
		if(seg.isDegenerated())
		{
			return distance(seg[0]) ;
		}
		if(intersect(seg))
		{
			return 0.0 ;
		}

		return ::std::min(::std::min(distance(seg[0]), distance(seg[1])), ::std::min(seg.distance((*this)[0]), seg.distance((*this)[1]))) ;
	}

	template <class Float>
	Math::Vector2<Float> Segment2D<Float>::closestPoint(Math::Vector2<Float> const & point) const
	{
		if(isDegenerated())
		{ return (*this)[0] ; }

		Math::Vector<Float,2> d ;
		Float				 n ;
		delta(d, n) ;
		Float projNorm = (point-m_points[0])*d ;

		if(projNorm<=0 || projNorm>=n) // Le point se projette en dehors du segment
		{ 
			Float d1 = (point-m_points[0]).norm() ;
			Float d2 = (point-m_points[1]).norm() ;
			if(d1<d2) { return m_points[0] ; }
			return m_points[1] ;
		}

		return m_points[0]+(d*projNorm) ;
	}

	template <class Float>
	Float Segment2D<Float>::lineDistance(Math::Vector2<Float> const & point) const 
	{
		Math::Vector<Float,2> d ;
		Float				 n ;
		delta(d, n) ;

		Float projNorm = (point-m_points[0])*d ;

		return (point-m_points[0]-(d*projNorm)).norm() ;
	}

	template <class Float>
	bool Segment2D<Float>::intersect(Segment2D<Float> const & s1, Segment2D<Float> const & s2)
	{
		assert(!s1.isDegenerated()) ;
		assert(!s2.isDegenerated()) ;
		Math::Vector2<Float> delta1 = Math::Vector2<Float>(s1.direction()).rotate90() ;
		Math::Vector2<Float> delta2 = Math::Vector2<Float>(s2.direction()).rotate90() ;
		return ((s2[0]-s1[0])*delta1) * ((s2[1]-s1[0])*delta1) <= 0.0 && ((s1[0]-s2[0])*delta2) * ((s1[1]-s2[0])*delta2) <= 0.0 ;
	}
}
#endif
