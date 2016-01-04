#ifndef _Math_Segment_H
#define _Math_Segment_H

#include <Math/Vector.h>
namespace Math
{
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \class	Segment
	///
	/// \brief	Class handling a N-dimensional segment. 
	///
	/// \author	Fabrice Lamarche, University Of Rennes 1
	/// \date	20/12/2009
	////////////////////////////////////////////////////////////////////////////////////////////////////
	template <class Float, int dimensions>
	class Segment 
	{
	public:
		//! Iterator on vertices. 
		//typedef Vector<Float, dimensions> * iterator ;
		//! Const iterator on vertices. 
		typedef const Vector<Float, dimensions> * const_iterator ;

	protected:
		//! Vertices delimiting the segment. 
		Vector<Float, dimensions> m_points[2] ;
		//! segment direction
		mutable Vector<Float, dimensions> m_direction ;
		//! segment length
		mutable Float m_length ;


		void needUpdate()
		{
			m_length=-1.0 ;
		}

		void update() const
		{
			if(m_length<0.0)
			{
				m_direction = m_points[1]-m_points[0] ;
				m_length = m_direction.norm() ;
				m_direction /= m_length ;
			}
			//m_direction = (m_points[1]-m_points[0]).normalized() ;
		}

	public:

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Segment(Vector<Float,dimensions> const & p1, Vector<Float, dimensions> const & p2)
		///
		/// \brief	Constructor. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	20/12/2009
		///
		/// \param [in,out]	p1	the first point. 
		/// \param [in,out]	p2	the second point. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Segment(Vector<Float,dimensions> const & p1 = Math::Vector<Float, dimensions>(), Vector<Float, dimensions> const & p2 = Math::Vector<Float, dimensions>())
		{
			m_points[0] = p1 ;
			m_points[1] = p2 ;
			needUpdate();
			//m_length = -1.0 ;
			//update() ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \brief	Swaps the two points defining the segment. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	20/12/2009
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void swap()
		{
			::std::swap(m_points[0], m_points[1]) ;
			needUpdate();
			//m_length = -1.0 ;
			//update();
		}

		/** \name Iterations and access to vertices */
		//@{

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \brief	Sets the 'index' vertex. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	20/12/2009
		///
		/// \param	index	Zero-based index of the vertex. 
		///
		/// \return	The result of the operation. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void set(int index, const Math::Vector<Float, dimensions> & v)
		{
			m_points[index] = v ;
			needUpdate() ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Math::Vector<Float, dimensions> & operator[] (int index) const
		///
		/// \brief	 Access to the 'index' vertex. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	20/12/2009
		///
		/// \param	index	Zero-based index of the vertex. 
		///
		/// \return	The result of the operation. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		const Math::Vector<Float, dimensions> & operator[] (int index) const
		{ return m_points[index] ; }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	int size() const
		///
		/// \brief	Return the number of vertices. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	20/12/2009
		///
		/// \return	. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		int size() const 
		{ return 2 ; }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	iterator begin() const
		///
		/// \brief	begin iterator. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	20/12/2009
		///
		/// \return	. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		const_iterator begin() const
		{ return m_points ; }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	iterator end() const
		///
		/// \brief	end iterator. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	20/12/2009
		///
		/// \return	. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		const_iterator end() const
		{ return m_points+2 ; }

		//@}

		/** \name Comparison and sorting for STL compliance */
		//@{

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \property	bool operator< (Segment const & seg) const
		///
		/// \brief	 Lexicographical comparison between segments. 
		///
		/// \return	true if operator<( segmentconst&seg)const, false if not. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		bool operator< (Segment const & seg) const
		{ return m_points[0]<seg.m_points[0] || (m_points[0]==seg.m_points[0] && m_points[1]<seg.m_points[1]) ; }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	void sort()
		///
		/// \brief	Sorts the vertices of the segment in lexicographical order. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	20/12/2009
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void sort()
		{
			if(m_points[1]<m_points[0]) 
			{ 
				::std::swap(m_points[0], m_points[1]) ;
				needUpdate();
			}
		}

		//@}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	bool isDegenerated() const
		///
		/// \brief	Query if this segment is degenerated. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	20/12/2009
		///
		/// \return	true if degenerated, false if not. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		bool isDegenerated() const
		{ return m_points[0]==m_points[1] ; }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Float length() const
		///
		/// \brief	return the length of the segment. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	20/12/2009
		///
		/// \return	The length of the segment. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Float length() const
		{
			update() ;
			return m_length ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Math::Vector<Float, dimensions> direction() const
		///
		/// \brief	Returns the normalized direction of the segment. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	20/12/2009
		///
		/// \return	the normalized direction of the segment. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Math::Vector<Float, dimensions> direction() const
		{
			update() ;
			return m_direction ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	bool projectsOn(Math::Vector<Float, dimensions> const & point) const
		///
		/// \brief	Tests if the point projects on the segment. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	20/12/2009
		///
		/// \param [in,out]	point	the point. 
		///
		/// \return	true if the point projects on the segment, false if not. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		bool projectsOn(Math::Vector<Float, dimensions> const & point) const
		{  
			Math::Vector<Float, dimensions> dir = direction() ;
			Float projNorm = (point-m_points[0])*dir ;
			return projNorm>=Float(0.0) && projNorm<=length() ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Float projectedAbscissa(Math::Vector<Float, dimensions> const & point) const
		///
		/// \brief	Return the curvilinear abscissa of the projection of the point on the line supporting the segment. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	20/12/2009
		///
		/// \param [in,out]	point	the point. 
		///
		/// \return	. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Float projectedAbscissa(Math::Vector<Float, dimensions> const & point) const
		{
			Math::Vector<Float, dimensions> dir = direction() ;
			return (point-m_points[0])*dir ;				
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Math::Vector<Float, dimensions> project(Math::Vector<Float,
		/// 	dimensions> const & point) const
		///
		/// \brief	Projects the point on the line supporting the segment. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	20/12/2009
		///
		/// \param point the point. 
		///
		/// \return	The projection of the point on the line supporting the segment. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Math::Vector<Float, dimensions> project(Math::Vector<Float, dimensions> const & point) const 
		{
			Float projNorm = projectedAbscissa(point) ;
			return m_points[0] + direction() * projNorm ;				
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Float distance(Math::Vector<Float, dimensions> const & point) const
		///
		/// \brief	Computes the distance between the point and the segment. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	20/12/2009
		///
		/// \param [in,out]	point	the point. 
		///
		/// \return	. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Float distance(Math::Vector<Float, dimensions> const & point) const
		{
			Float projNorm = projectedAbscissa(point) ;
			if(projNorm<=Float(0.0))
			{
				return (m_points[0]-point).norm() ;
			}
			if(projNorm>=length())
			{
				return (m_points[1]-point).norm() ;
			}
			return (point-m_points[0]-direction()*projNorm).norm() ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Float distance2(Math::Vector<Float, dimensions> const & point) const
		///
		/// \brief	Computes the squared distance between the point and the segment. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	20/12/2009
		///
		/// \param [in,out]	point	the point. 
		///
		/// \return	. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Float distance2(Math::Vector<Float, dimensions> const & point) const
		{
			Float projNorm = projectedAbscissa(point) ;
			if(projNorm<=float(0.0))
			{
				return (m_points[0]-point).norm2() ;
			}
			if(projNorm>=length())
			{
				return (m_points[1]-point).norm2() ;
			}
			return (point-m_points[0]-direction()*projNorm).norm2() ;
		}


	};

}


#endif