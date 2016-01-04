#ifndef _Math_BoundingBox2D_H
#define _Math_BoundingBox2D_H

#include <Math/Vector.h>
#include <Math/Interval.h>
#include <Math/Segment2D.h>
#include <Math/Triangle2D.h>
#include <Math/BoundingBox.h>

namespace Math
{
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \class	BoundingBox2D
	///
	/// \brief	Bounding box in 2D. Specialization of ::Rennes1::Math::BoundingBox.
	///
	/// \author	Fabrice Lamarche, University Of Rennes 1
	/// \date	16/12/2009
	////////////////////////////////////////////////////////////////////////////////////////////////////
	template <class Float>
	class BoundingBox2D : public BoundingBox<Float,2>
	{
	public:
		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	BoundingBox2D()
		///
		/// \brief	Default constructor. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	16/12/2009
		////////////////////////////////////////////////////////////////////////////////////////////////////
		BoundingBox2D()
		{}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	BoundingBox2D(BoundingBox<FLOAT, 2> const & box)
		///
		/// \brief	Copy constructor. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	10/03/2010
		///
		/// \param [in,out]	box	the box. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		BoundingBox2D(BoundingBox<Float, 2> const & box)
			: BoundingBox<Float,2>(box)
		{}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	BoundingBox2D(Math::Vector<Float,2> const & min, Math::Vector<Float,2> const & max)
		///
		/// \brief	Initializes a bounding box thanks to extremum points. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	16/12/2009
		///
		/// \param [in,out]	min	the minimum point. 
		/// \param [in,out]	max	the maximum point. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		BoundingBox2D(Math::Vector<Float,2> const & min, Math::Vector<Float,2> const & max)
		{
			updateMinMax(min, max) ;
			//m_coordInterval[0] = Math::Interval<Float>(min[0], max[0]) ;
			//m_coordInterval[1] = Math::Interval<Float>(min[1], max[1]) ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	BoundingBox2D(Math::Interval<Float> const & xInterval,
		/// 	Math::Interval<Float> const & yInterval)
		///
		/// \brief	Initializes a bounding box thanks to intervals. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	16/12/2009
		///
		/// \param [in,out]	xInterval	the x coordinate interval. 
		/// \param [in,out]	yInterval	the y coordinate interval. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		BoundingBox2D(Math::Interval<Float> const & xInterval, Math::Interval<Float> const & yInterval)
		{
			setInterval(0, xInterval) ;
			setInterval(1, yInterval) ;
			//m_coordInterval[0] = xInterval ;
			//m_coordInterval[1] = yInterval ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	void update(Math::Segment2D<Float> const & seg)
		///
		/// \brief	Updates the box such as it contains the segment.
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	16/12/2009
		///
		/// \param [in,out]	seg	the segment. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void update(Math::Segment2D<Float> const & seg)
		{
			if(isEmpty())
			{
				updateMinMax(seg[0].simdMin(seg[1]), seg[0].simdMax(seg[1])) ;
			}
			else
			{
				BoundingBox<Float,2>::update(seg[0]) ;
				BoundingBox<Float,2>::update(seg[1]) ;
			}
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	void update(Math::Triangle2D<Float> const & triangle)
		///
		/// \brief	Updates the box such as it contains the triangle.
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	16/12/2009
		///
		/// \param [in,out]	triangle	the triangle. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void update(Math::Triangle2D<Float> const & triangle)
		{
			if(isEmpty())
			{
				updateMinMax(triangle[0].simdMin(triangle[1]).simdMin(triangle[2]), triangle[0].simdMax(triangle[1]).simdMax(triangle[2]));
			}
			else
			{
				BoundingBox<Float,2>::update(triangle[0]) ;
				BoundingBox<Float,2>::update(triangle[1]) ;
				BoundingBox<Float,2>::update(triangle[2]) ;
			}
		}

		///////////////////////////////////////////////////////////////////////////////////
		/// \brief Extend the bounding box with the given distance
		/// 
		/// \param distance The spatial extent added to the bounding box.
		/// \return 
		/// 
		/// \author F. Lamarche, University of Rennes 1.
		///////////////////////////////////////////////////////////////////////////////////
		void extend(Float distance)
		{
			BoundingBox<Float,2>::m_extent = BoundingBox<Float,2>::m_extent+Math::Vector2<Float>(distance, distance) ;
		}

		/** \name Intervals */
		//@{

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Math::Interval<Float> const & xInterval() const
		///
		/// \brief	X coordinate interval. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	16/12/2009
		///
		/// \return	. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Math::Interval<Float> xInterval() const
		{
			return interval(0) ;
			//return m_coordInterval[0] ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Math::Interval<Float> const & yInterval() const
		///
		/// \brief	Y coordinate interval. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	16/12/2009
		///
		/// \return	. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Math::Interval<Float> yInterval() const
		{
			return interval(1) ;
			//return m_coordInterval[1] ;
		}

		///////////////////////////////////////////////////////////////////////////////////
		/// \brief Compares two boxes in lexicographical order of (X,Y) intervals.
		/// 
		/// \param box
		/// \return 
		/// 
		/// \author F. Lamarche, University of Rennes 1.
		///////////////////////////////////////////////////////////////////////////////////
		bool operator<(BoundingBox2D<Float> const & box) const
		{
			return interval(0)<box.interval(0) || (interval(0)==box.interval(0) && interval(1)<box.interval(1)) ;
		}

		//@}
	};
}


#endif