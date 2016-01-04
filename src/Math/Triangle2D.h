#ifndef _Math_Triangle_H
#define _Math_Triangle_H

#include <Math/Vector2.h>
#include <Math/Vector3.h>
#include <Math/Segment2D.h>
#include <Math/Circle2D.h>

namespace Math
{

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \class	Triangle2D
	///
	/// \brief	A triangle in 2D. 
	///
	/// \author	Fabrice Lamarche, University Of Rennes 1
	/// \date	14/05/2010
	////////////////////////////////////////////////////////////////////////////////////////////////////
	template <class Float>
	class Triangle2D
	{
	protected:
		//! Vertices of the triangle. 
		Math::Vector2<Float> m_points[3] ;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	bool edgeOK(int point1, int point2, int point3, Math::Vector<Float,
		/// 	2> const & point) const
		///
		/// \brief	Tests if the point is lying in the half world delimited by (point1,point2) and containing point3. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	14/05/2010
		///
		/// \param	point1			The first point. 
		/// \param	point2			The second point. 
		/// \param	point3			The third point. 
		/// \param [in,out]	point	the point. 
		///
		/// \return	true if it succeeds, false if it fails. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		bool edgeOK(int point1, int point2, int point3, Math::Vector<Float, 2> const & point) const ;

	public:

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Triangle2D(const Math::Vector2<Float> & p1, const Math::Vector2<Float> & p2,
		/// 	const Math::Vector2<Float> & p3)
		///
		/// \brief	Constructor. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	14/05/2010
		///
		/// \param	p1	The first vertex. 
		/// \param	p2	The second vertex. 
		/// \param	p3	The third vertex. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Triangle2D(const Math::Vector2<Float> & p1, const Math::Vector2<Float> & p2, const Math::Vector2<Float> & p3)
		{
			m_points[0] = p1 ;
			m_points[1] = p2 ;
			m_points[2] = p3 ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Triangle2D()
		///
		/// \brief	Default constructor. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	14/05/2010
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Triangle2D()
		{}


		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	bool isInside(Math::Vector<Float, 2> const & point) const
		///
		/// \brief	Query if 'point' is inside the triangle. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	14/05/2010
		///
		/// \param [in,out]	point	the point. 
		///
		/// \return	true if inside, false if not. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		bool isInside(Math::Vector<Float, 2> const & point) const ;


		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Circle2D<Float> circumscribedCircle() const
		///
		/// \brief	Computes the circumscribed circle. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	14/05/2010
		///
		/// \return	the circumscribed circle. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Circle2D<Float> circumscribedCircle() const ;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Circle2D<Float> inscribedCircle() const
		///
		/// \brief	Computes the inscribed circle. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	14/05/2010
		///
		/// \return	the inscribed circle. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Circle2D<Float> inscribedCircle() const
		{
			// Computes the circle center
			Float a=edge(0).length(), b=edge(1).length(), c=edge(2).length() ;
			Float p=a+b+c ;
			Math::Vector2<Float> center = vertex(0)*(a/p)+vertex(1)*(b/p)+vertex(2)*(c/p) ;
			// Computes the circle radius
			Float radius = (Float)(2.0*surface()/p) ;
			return Circle2D<Float>(center, radius) ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Math::Vector2<Float> & operator[] (int index)
		///
		/// \brief	 Returns the index's vertex of the triangle. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	14/05/2010
		///
		/// \param	index	Zero-based index of the vertex. 
		///
		/// \return	the index's vertex of the triangle. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Math::Vector2<Float> & operator[] (int index)
		{ return m_points[index] ; }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	const Math::Vector2<Float> & operator[] (int index) const
		///
		/// \brief	 Returns the index's vertex of the triangle. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	14/05/2010
		///
		/// \param	index	Zero-based index of the vertex. 
		///
		/// \return	the index's vertex of the triangle. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		const Math::Vector2<Float> & operator[] (int index) const
		{ return m_points[index] ; }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	const Math::Vector2<Float> & vertex(int index) const
		///
		/// \brief	 Returns the index's vertex of the triangle. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	14/05/2010
		///
		/// \param	index	Zero-based index of the vertex. 
		///
		/// \return	the index's vertex of the triangle. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		const Math::Vector2<Float> & vertex(int index) const
		{ return (*this)[index] ; }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Segment2D<Float> edge(int no) const
		///
		/// \brief	Returns the no's edge of the triangle i.e. the opposite edge of vertex no. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	14/05/2010
		///
		/// \param	no	The index of the edge in [0;2]. 
		///
		/// \return	the no's edge of the triangle. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Segment2D<Float> edge(int no) const 
		{ return Segment2D<Float>(m_points[(no+1)%3], m_points[(no+2)%3]) ; }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Math::Vector2<Float> center() const
		///
		/// \brief	Returns the center of this triangle. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	14/05/2010
		///
		/// \return	. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Math::Vector2<Float> center() const
		{ return (m_points[0]+m_points[1]+m_points[2])/3.0 ; }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Float height(int index) const
		///
		/// \brief	Return the index's height of the triangle (the height associated to the index's vertex)
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	14/05/2010
		///
		/// \param	index	Zero-based index of the vertex. 
		///
		/// \return	. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Float height(int index) const ;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Float maxHeight() const
		///
		/// \brief	Returns the maximum height of the triangle. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	14/05/2010
		///
		/// \return	the maximum height of the triangle. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Float maxHeight() const ;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Float minHeight() const
		///
		/// \brief	Returns the minimum height of the triangle. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	14/05/2010
		///
		/// \return	the minimum height of the triangle. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Float minHeight() const ;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Float surface() const
		///
		/// \brief	Returns the surface of the triangle. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	14/05/2010
		///
		/// \return	the surface of the triangle. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Float surface() const ;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Float cosinusAngle(unsigned int vertexId) const
		///
		/// \brief	Returns the cosine of the angle associated to a given vertex. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	14/05/2010
		///
		/// \param	vertexId	Identifier of the vertex. 
		///
		/// \return	. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Float cosinusAngle(unsigned int vertexId) const ;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Float minAngleCosinus() const
		///
		/// \brief	Returns the cosine of the minimal angle. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	14/05/2010
		///
		/// \return	the cosine of the minimal angle. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Float minAngleCosinus() const ;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Float distance(Math::Vector2<Float> const & point) const
		///
		/// \brief	Computes the distance between a point and this triangle. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	14/05/2010
		///
		/// \param [in,out]	point	the point. 
		///
		/// \return	the distance between a point and this triangle. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Float distance(Math::Vector2<Float> const & point) const ;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Float distance(Segment2D<Float> const & segment) const
		///
		/// \brief	Computes the distance between a segment and this triangle. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	14/05/2010
		///
		/// \param [in,out]	segment	the segment. 
		///
		/// \return	the distance between a segment and this triangle. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Float distance(Segment2D<Float> const & segment) const ;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Float distance(Triangle2D<Float> const & triangle) const
		///
		/// \brief	Computes the distance between this triangle and another triangle. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	14/05/2010
		///
		/// \param [in,out]	triangle	the triangle. 
		///
		/// \return	the distance between this triangle and another triangle. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Float distance(Triangle2D<Float> const & triangle) const ;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Math::Vector3<Float> barycentricCoordinates(Math::Vector2<Float> const & m) const
		///
		/// \brief	Computes barycentric coordinates of point m. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	06/01/2010
		///
		/// \param [in,out]	m the point. 
		///
		/// \return	The barycentric coordinates. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Math::Vector3<Float> barycentricCoordinates(Math::Vector2<Float> const & m) const
		{
			Math::Vector2<Float> am = m-m_points[0] ;
			Math::Vector2<Float> bm = m-m_points[1] ;
			Math::Vector2<Float> cm = m-m_points[2] ;
			Float det1 = Vector2<Float>::det(bm,cm) ;
			Float det2 = Vector2<Float>::det(cm,am) ;
			Float det3 = Vector2<Float>::det(am,bm) ;
			return Math::Vector3<Float>(det1, det2, det3)/(det1+det2+det3) ; 
		}


		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Triangle2D & operator = (Triangle2D<Float> const & triangle)
		///
		/// \brief	Copy operator. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	14/05/2010
		///
		/// \param [in,out]	triangle	the triangle. 
		///
		/// \return	A shallow copy of this object. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Triangle2D & operator = (Triangle2D<Float> const & triangle) 
		{
			m_points[0] = triangle[0] ;
			m_points[1] = triangle[1] ;
			m_points[2] = triangle[2] ;
			return *this ;
		}
	} ;
}

namespace Math
{
	template <class Float>
	bool Triangle2D<Float>::edgeOK(int point1, int point2, int point3, Math::Vector<Float, 2> const & point) const
	{
		Math::Vector2<Float> u = m_points[point1]-m_points[point2] ;
		u = u.rotate90() ;
		Float res1 = (u*(m_points[point3]-m_points[point1])) ;
		// If triangle is degenerated, we test if the point lies on the segment
		if(res1==0.0) { return Segment2D<Float>(m_points[point1], m_points[point2]).distance(point)==0.0 ; }
		Float res2 = (u*(point-m_points[point1])) ;
		return res1*res2>=0.0 ;
	}

	template <class Float>
	bool Triangle2D<Float>::isInside(Math::Vector<Float, 2> const & point) const
	{
		return edgeOK(0,1,2,point) && edgeOK(0,2,1,point) && edgeOK(1,2,0,point) ;
	}

	template <class Float>
	Float Triangle2D<Float>::height(int index) const
	{
		assert(index>=0 && index<3) ;
		int lineIndex[2] ;
		if(index==0)
		{
			lineIndex[0] = 1 ; lineIndex[1] = 2 ;
		}
		else if(index==1)
		{
			lineIndex[0] = 0 ; lineIndex[1] = 2 ;
		}
		else
		{
			lineIndex[0] = 0 ; lineIndex[1] = 1 ;
		}
		return fabs(Line2D<Float>(m_points[lineIndex[0]], m_points[lineIndex[1]]).distance(m_points[index])) ;
	}

	template <class Float>
	Float Triangle2D<Float>::maxHeight() const
	{
		return std::max(height(0), std::max(height(1), height(2))); 
	}

	template <class Float>
	Float Triangle2D<Float>::minHeight() const
	{
		return std::min(height(0), std::min(height(1), height(2))); 
	}

	template <class Float>
	Float Triangle2D<Float>::distance(Math::Vector2<Float> const & point) const 
	{
		if(isInside(point)) { return 0.0 ; }
		return std::min(edge(0).distance(point), std::min(edge(1).distance(point), edge(2).distance(point))) ;
	}

	template <class Float>
	Float Triangle2D<Float>::distance(Segment2D<Float> const & seg) const 
	{
		if(isInside(seg[0]) || isInside(seg[1])) { return 0.0 ; }
		return std::min(edge(0).distance(seg), std::min(edge(1).distance(seg), edge(2).distance(seg))) ;
	}

	template <class Float>
	Float Triangle2D<Float>::distance(Triangle2D const & triangle) const
	{
		return std::min(std::min(distance(triangle.edge(0)), triangle.distance(edge(0))), std::min(triangle.distance(edge(1)), triangle.distance(edge(2)))) ;
	}

	template <class Float>
	Float Triangle2D<Float>::surface() const 
	{
		return height(0) * (m_points[2]-m_points[1]).norm() / Float(2.0) ;
	}

	template <class Float>
	Float Triangle2D<Float>::cosinusAngle(unsigned int vertexId) const 
	{
		Math::Vector2<Float> delta1 = m_points[(vertexId+1)%3] - m_points[vertexId] ;
		delta1 = delta1.normalized() ;
		Math::Vector2<Float> delta2 = m_points[(vertexId-1)%3] - m_points[vertexId] ;
		delta2 = delta2.normalized() ;
		return delta1 * delta2 ;
	}

	template <class Float>
	Float Triangle2D<Float>::minAngleCosinus() const 
	{
		return std::max(std::max(cosinusAngle(0), cosinusAngle(1)), cosinusAngle(2)) ;
	}

	template <class Float>
	Circle2D<Float> Triangle2D<Float>::circumscribedCircle() const 
	{
		Math::Vector3<Float> p1(m_points[0][0], m_points[0][1], 0.0) ;
		Math::Vector3<Float> p2(m_points[1][0], m_points[1][1], 0.0) ;
		Math::Vector3<Float> p3(m_points[2][0], m_points[2][1], 0.0) ;

		Float radius = (p1-p2).norm()*(p2-p3).norm()*(p3-p1).norm() / (Float(2.0)*(Math::Vector3<Float>(p1-p2)^Math::Vector3<Float>(p2-p3)).norm()) ;

		Float div = (Float(2.0)*(Math::Vector3<Float>(p1-p2)^Math::Vector3<Float>(p2-p3)).norm2()) ;
		Float a = (p2-p3).norm2()*((p1-p2)*(p1-p3)) / div ;
		Float b = (p1-p3).norm2()*((p2-p1)*(p2-p3)) / div ;
		Float c = (p1-p2).norm2()*((p3-p1)*(p3-p2)) / div ;

		Math::Vector3<Float> center = Math::Vector3<Float>((p1*a + p2*b + p3*c)/(a+b+c)) ;
		Float estimated = (center-p1).norm2() ;
		estimated = std::max(estimated, (center-p2).norm2()) ;
		estimated = std::max(estimated, (center-p3).norm2()) ;

		//assert(radius-estimated==0.0) ;

		return Circle2D<Float>(center.projectZ(), estimated, true) ;
	}


}

#endif
