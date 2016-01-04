#ifndef _Math_distance2D_H
#define _Math_distance2D_H

#include <Math/Vector2.h>
#include <Math/Segment2D.h>
#include <Math/Triangle2D.h>
#include <Math/BoundingBox2D.h>


namespace Math
{

	/** \name Distance computation between 2D objects */
	//@{

	template <class Float>
	inline Float distance(Vector<Float, 2> const & p1, Vector2<Float> const & p2)
	{
		return (p1-p2).norm() ;
	}

	template <class Float>
	inline Float distance(Vector<Float, 2> const & p, Segment2D<Float> const & s)
	{
		return s.distance(p) ;
	}

	template <class Float>
	inline Float distance(Segment2D<Float> const & s, Vector2<Float> const & p)
	{
		return s.distance(p) ;
	}

	template <class Float>
	inline Float distance(Vector<Float, 2> const & p, Line2D<Float> const & l)
	{
		return fabs(l.distance(p)) ;
	}

	template <class Float>
	inline Float distance(Line2D<Float> const & l, Vector2<Float> const & p)
	{
		return fabs(l.distance(p)) ;
	}

	template <class Float>
	inline Float distance(Segment2D<Float> const & s1, Segment2D<Float> const & s2)
	{
		return s1.distance(s2) ;
	}

	template <class Float>
	inline Float distance(Triangle2D<Float> const & t, Vector2<Float> const & p)
	{
		return t.distance(p) ;
	}

	template <class Float>
	inline Float distance(Vector<Float, 2> const & p, Triangle2D<Float> const & t)
	{
		return t.distance(p) ;
	}

	template <class Float>
	inline Float distance(Triangle2D<Float> const & t, Segment2D<Float> const & s)
	{
		return t.distance(s) ;
	}

	template <class Float>
	inline Float distance(Segment2D<Float> const & s, Triangle2D<Float> const & t)
	{
		return t.distance(s) ;
	}

	template <class F>
	inline F distance(Triangle2D<F> const & f1, Triangle2D<F> const & f2)
	{
		return f1.distance(f2) ;
	}

	template <class Float>
	inline Float distance(Line2D<Float> const & l, Segment2D<Float> const & s)
	{
		Float d1=l.distance(s.p1()), d2=l.distance(s.p2()) ;
		if(d1*d2<=0.0) { return 0.0 ; }
		return std::min(fabs(d1), fabs(d2)) ;
	}

	template <class Float>
	inline Float distance(Segment2D<Float> const & s, Line2D<Float> const & l)
	{
		return distance(l,s) ;
	}

	template <class F>
	inline F distance(BoundingBox2D<F> const & box, Vector2<F> const & v)
	{
		return box.distance(v) ;
	}

	template <class F>
	inline F distance(Vector2<F> const & v, BoundingBox2D<F> const & box)
	{
		return box.distance(v) ;
	}

	template <class F>
	inline F distance(BoundingBox2D<F> const & box, Segment2D<F> const & seg)
	{
		if(box.isInside(seg[0]) || box.isInside(seg[1])) { return 0.0 ; }
		//F d1 = ::std::numeric_limits<F>::max() ;
		Vector2<F> a = box.minVertex() ;
		Vector2<F> c = box.maxVertex() ;
		Vector2<F> b(a[0], c[1]) ;
		Vector2<F> d(c[0], a[1]) ;
		F d1 = distance(seg, Segment2D<F>(a,b)) ;
		F d2 = distance(seg, Segment2D<F>(b,c)) ;
		F d3 = distance(seg, Segment2D<F>(c,d)) ;
		F d4 = distance(seg, Segment2D<F>(d,a)) ;
		return std::min(std::min(d1,d2), std::min(d3,d4)) ;
	}

	template <class F>
	inline F distance(Segment2D<F> const & s, BoundingBox2D<F> const & box)
	{
		return distance(box, s) ;
	}

	template <class F>
	inline F distance(BoundingBox2D<F> const & box, Triangle2D<F> const & triangle)
	{
		Vector2<F> a = box.minVertex() ;
		Vector2<F> c = box.maxVertex() ;
		Vector2<F> b(a[0], c[1]) ;
		Vector2<F> d(c[0], a[1]) ;
		Triangle2D<F> t1(a,b,c) ;
		Triangle2D<F> t2(c,d,a) ;
		return std::min(distance(triangle, t1), distance(triangle, t2)) ;
	}

	template <class F>
	inline F distance(Triangle2D<F> const & triangle, BoundingBox2D<F> const & box)
	{
		return distance(box, triangle) ;
	}

	template <class F>
	inline F distance(BoundingBox2D<F> const & box, BoundingBox2D<F> const & box2)
	{
		return box.distance(box2) ;
	}

	//@}
} 

#endif