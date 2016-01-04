#ifndef _Math_Circle_H
#define _Math_Circle_H

#include <assert.h>
#include <Math/Vector2.h>
#include <Math/Segment2D.h>
#include <Math/Sphere.h>

namespace Math
{

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \class	Circle2D
	///
	/// \brief	Circle in two dimensions. 
	///
	/// \author	Fabrice Lamarche, University Of Rennes 1
	/// \date	04/12/2009
	////////////////////////////////////////////////////////////////////////////////////////////////////
	template <class Float>
	class Circle2D : public Sphere<Float, 2>
	{
	public: 

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \struct	Intersection : public Serialization::SerializableWithFactory, Serialization::
		/// 		Factory<Intersection>
		///
		/// \brief	Result of a two circle intersection.
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	04/12/2009
		////////////////////////////////////////////////////////////////////////////////////////////////////
		struct Intersection 
		{
			//! Number of intersections. 
			unsigned int		 m_nbIntersections ;
			//! The intersections. 
			Math::Vector2<Float> m_points[2] ;
		} ;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Circle2D(Float radius, bool exp2=false)
		///
		/// \brief	Constructor. Creates a circle centered in (0,0) with a user supplied radius.
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	04/12/2009
		///
		/// \param	radius	The radius or radius^2 (if exp2 is true). 
		/// \param	exp2	true if radius is squared. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Circle2D(Float radius, bool exp2=false)
			: Sphere<Float,2>(radius, exp2)
		{}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Circle2D(Math::Vector2<Float> const & center=Math::Vector2<Float>(), Float rayon=1.0,
		/// 	bool exp2=false)
		///
		/// \brief	Constructor. Creates a circle centered at a user supplied position.
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	04/12/2009
		///
		/// \param [in,out]	center	position of the center of the circle. 
		/// \param	radius			The radius or radius^2 (if exp2 is true). 
		/// \param	exp2			true if radius is squared. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Circle2D(Math::Vector2<Float> const & center=Math::Vector2<Float>(), Float radius=1.0, bool exp2=false)
			: Sphere<Float,2>(center, radius, exp2)
		{}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	bool isInside(Math::Vector2<Float> const & point) const
		///
		/// \brief	Queries if 'point' is inside the circle. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	04/12/2009
		///
		/// \param [in,out]	point	the point. 
		///
		/// \return	true if the point is in the circle. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		bool isInside(Math::Vector<Float, 2> const & point) const
		{
			return Sphere<Float,2>::isInside(point) ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	bool isInside(Segment2D<Float> const & segment) const
		///
		/// \brief	Query if 'segment' is partially of fully inside the circle. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	04/12/2009
		///
		/// \param [in,out]	segment	the segment. 
		///
		/// \return	true if inside, false if not. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		bool isInside(Segment2D<Float> const & segment) const
		{
			Float dist = segment.distance(m_center) ;
			return dist*dist<=m_radiusExp2 ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	bool tangentPoints(Math::Vector2<Float> const & point, Math::Vector2<Float> & leftTangent,
		/// 	Math::Vector2<Float> & rightTangent)
		///
		/// \brief	Given a point point, computes two points leftTangent and rightTangent such as (point,rightTangent) 
		///			and (point,leftTangent) are tangent to the circle. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	04/12/2009
		///
		/// \param [in,out]	point	the source point. 
		/// \param [in,out]	leftTangent	the left tangent point. 
		/// \param [in,out]	rightTangent	the right tangent point. 
		///
		/// \return	true if tangent points exist, false if not. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		bool tangentPoints(Math::Vector2<Float> const & point, Math::Vector<Float, 2> & leftTangent, Math::Vector<Float, 2> & rightTangent) ;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	void intersection(Circle2D const & circle, Intersection & circleIntersection)
		///
		/// \brief	Computes the intersection of two circles. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	04/12/2009
		///
		/// \param circle				the second circle. 
		/// \param [out]	circleIntersection	the circle intersection. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void intersection(Circle2D const & circle, Intersection & circleIntersection) ;

	};

}

namespace Math
{

	template <class Float>
	bool Circle2D<Float>::tangentPoints(Math::Vector2<Float> const & point, Math::Vector<Float, 2> & leftTangent, Math::Vector<Float, 2> & rightTangent)
	{
		//assert(!in(v)) ;
		if(isInside(point)) 
		{ 
			return false ;
			//std::cout<<"circle.tangentPoints :: in!!!!!"<<std::endl ; 
		}
		Math::Vector2<Float> P = point-m_center ;
		Float normP = P.norm() ; //::norm(P) ;
		Float x = m_radiusExp2/normP ;
		Float y = sqrt(m_radiusExp2-x*x) ;
		Math::Vector2<Float> e1 = P*(Float(1.0)/normP) ;
		Math::Vector2<Float> e2 = e1.rotate90();
		leftTangent = e1*x+e2*(-y) ;
		rightTangent = e1*x+e2*y ;
		// Modification pour les besoins de la cause...
		leftTangent = leftTangent + m_center ;
		rightTangent = rightTangent + m_center ;
		return true ;
	}

	template <class Float>
	void Circle2D<Float>::intersection(Circle2D const & circle, Intersection & circleIntersection)
	{
		Math::Vector2<Float> deltaCenter = circle.center() - this->center() ;
		Float deltaCenterNorm2 = deltaCenter.norm2();
		Float radius0 = this->radius(), radius1 = circle.radius();
		Float deltaRadius = radius0 - radius1;

		// Les deux cercles sont confondus
		if (deltaCenterNorm2 <= 0.0 &&  fabs(deltaRadius) <= 0.0)
		{
			circleIntersection.m_nbIntersections = 0;
			return ;
		}

		Float deltaRadius2 = deltaRadius*deltaRadius;

		// Les deux cercles ne s'intersectent pas
		if (deltaCenterNorm2 < deltaRadius2)
		{
			circleIntersection.m_nbIntersections = 0;
			return ;
		}

		Float radiusSum = radius0 + radius1;
		Float radiusSum2 = radiusSum*radiusSum;

		// Les deux cercles ne s'intersectent pas
		if (deltaCenterNorm2 > radiusSum2)
		{
			circleIntersection.m_nbIntersections = 0;
			return ;
		}

		// Les cercles s'intersectent

		if (deltaCenterNorm2 < radiusSum2)
		{
			if (deltaRadius2 < deltaCenterNorm2) // Intersection en deux points
			{
				Float invDeltaCenterNorm2 = ((Float)1.0)/deltaCenterNorm2;
				Float fS = ((Float)0.5)*((radius0*radius0-radius1*radius1)*invDeltaCenterNorm2+(Float)1.0);
				Math::Vector2<Float> kTmp = this->center() + deltaCenter*fS;

				Float fT = sqrt(radius0*radius0*invDeltaCenterNorm2 - fS*fS);
				Math::Vector2<Float> kV(deltaCenter[1],-deltaCenter[0]);
				circleIntersection.m_nbIntersections = 2;
				circleIntersection.m_points[0] = kTmp - kV*fT;
				circleIntersection.m_points[1] = kTmp + kV*fT;
			}
			else // Les deux cercles sont tangents
			{
				circleIntersection.m_nbIntersections = 1;
				circleIntersection.m_points[0] = this->center() + deltaCenter*(radius0/deltaRadius);
			}
		}
		else // Les deux cercles sont tangents
		{
			circleIntersection.m_nbIntersections = 1;
			circleIntersection.m_points[0] = this->center() + deltaCenter*(radius0/radiusSum);
		}

	}
}

#endif
