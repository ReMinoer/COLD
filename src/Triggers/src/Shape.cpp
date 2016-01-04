#include <stdafx.h>

#include <Triggers/Shape.h>

namespace Triggers
{
	

	Shape::Shape( Vector2 const & skeleton, Config::Real extent ) : m_skeleton(new Vector2(skeleton)), m_extent(extent), m_type(point)
	{
		m_transformation = Math::Matrix3x3<Config::Real>::getIdentity() ;
	}

	Shape::Shape( Segment2 const & skeleton, Config::Real extent ) : m_skeleton(new Segment2(skeleton)), m_extent(extent), m_type(segment)
	{
		m_transformation = Math::Matrix3x3<Config::Real>::getIdentity() ;
	}

	Shape::Shape( Triangle2 const & skeleton, Config::Real extent ) : m_skeleton(new Triangle2(skeleton)), m_extent(extent), m_type(triangle)
	{
		m_transformation = Math::Matrix3x3<Config::Real>::getIdentity() ;
	}

	Shape::Shape( Shape const & shape )
	{
		m_type = shape.m_type ;
		m_extent = shape.m_extent ;
		switch(shape.m_type)
		{
		case point:
			m_skeleton = new Vector2(*(Vector2*)shape.m_skeleton) ;
			break ;
		case segment:
			m_skeleton = new Segment2(*(Segment2*)shape.m_skeleton) ;
			break ;
		case triangle:
			m_skeleton = new Triangle2(*(Triangle2*)shape.m_skeleton) ;
			break ;
		default:
			throw ::std::exception("Triggers::Shape incredible bad type, check your pointers!") ;
		}
		m_transformation = shape.m_transformation ;
	}

	Shape::~Shape()
	{
		switch(m_type)
		{
		case point:
			delete (Vector2*)m_skeleton ;
			break ;
		case segment:
			delete (Segment2*)m_skeleton ;
			break ;
		case triangle:
			delete (Triangle2*)m_skeleton ;
			break ;
		default:
			throw ::std::exception("Triggers::Shape incredible bad type, check your pointers!") ;
		}
	}

	Config::Real Shape::subDistance( Shape const & shape1, Shape const & shape2 )
	{
		int index = shape1.m_type+shape2.m_type*last ;
		switch(index)
		{
		case point+point*last:
			return Math::distance(shape1.m_transformation*(*(Vector2*)shape1.m_skeleton), shape2.m_transformation*(*(Vector2*)shape2.m_skeleton)) ;
		case point+segment*last:
			return Math::distance(shape1.m_transformation*(*(Vector2*)shape1.m_skeleton), shape2.m_transformation*(*(Segment2*)shape2.m_skeleton)) ;
		case point+triangle*last:
			return Math::distance(shape1.m_transformation*(*(Vector2*)shape1.m_skeleton), shape2.m_transformation*(*(Triangle2*)shape2.m_skeleton)) ;
		case segment+point*last:
			return Math::distance(shape1.m_transformation*(*(Segment2*)shape1.m_skeleton), shape2.m_transformation*(*(Vector2*)shape2.m_skeleton)) ;
		case segment+segment*last:
			return Math::distance(shape1.m_transformation*(*(Segment2*)shape1.m_skeleton), shape2.m_transformation*(*(Segment2*)shape2.m_skeleton)) ;
		case segment+triangle*last:
			return Math::distance(shape1.m_transformation*(*(Segment2*)shape1.m_skeleton), shape2.m_transformation*(*(Triangle2*)shape2.m_skeleton)) ;
		case triangle+point*last:
			return Math::distance(shape1.m_transformation*(*(Triangle2*)shape1.m_skeleton), shape2.m_transformation*(*(Vector2*)shape2.m_skeleton)) ;
		case triangle+segment*last:
			return Math::distance(shape1.m_transformation*(*(Triangle2*)shape1.m_skeleton), shape2.m_transformation*(*(Segment2*)shape2.m_skeleton)) ;
		case triangle+triangle*last:
			return Math::distance(shape1.m_transformation*(*(Triangle2*)shape1.m_skeleton), shape2.m_transformation*(*(Triangle2*)shape2.m_skeleton)) ;
		}
		return Config::realMaxValue ;
	}

	Config::Real Shape::distance( Shape const & shape1, Shape const & shape2 )
	{
		return ::std::max(subDistance(shape1,shape2)-shape1.m_extent-shape2.m_extent, Config::Real(0.0)) ;
	}

	Shape & Shape::operator=( const Shape & shape )
	{
		if(this!=&shape)
		{
			this->~Shape() ; // Destroy the current object
			new (this) Shape(shape) ; // Call copy constructor on this memory location
		}
		return *this ;
	}

	const Math::Matrix3x3<Config::Real> Shape::getTransform() const
	{
		return m_transformation ;
	}

	void Shape::setTransform( Math::Matrix3x3<Config::Real> const & tranform )
	{
		m_transformation = tranform ;
	}

	void Shape::applyTransform()
	{
		switch(m_type)
		{
		case point:
			{
				Vector2 * tmpV = new Vector2(m_transformation*(*(Vector2*)m_skeleton)) ;
				delete (Vector2*)m_skeleton ;
				m_skeleton = tmpV ;
			}
			break ;
		case segment:
			{
				Segment2 * tmpS = new Segment2(m_transformation*(*(Segment2*)m_skeleton)) ;
				delete (Segment2*)m_skeleton ;
				m_skeleton = tmpS ;
			}
			break ;
		case triangle:
			{
				Triangle2 * tmpT= new Triangle2(m_transformation*(*(Triangle2*)m_skeleton)) ;
				delete (Triangle2*)m_skeleton ;
				m_skeleton = tmpT ;
			}
			break ;
		}
		m_transformation = Math::Matrix3x3<Config::Real>::getIdentity() ;
	}

	Math::BoundingBox2D<Config::Real> Shape::getBoundingBox() const
	{
		Math::BoundingBox2D<Config::Real> result ;
		switch(m_type)
		{
		case point:
			{
				Vector2 * v = (Vector2*)m_skeleton ;
				Vector2 transformed = m_transformation*(*v) ;
				result.update(Segment2(transformed-Vector2(m_extent, m_extent), transformed+Vector2(m_extent, m_extent))) ;
			}
			break ;
		case segment:
			{
				Segment2 * s = (Segment2*)m_skeleton ;
				Segment2 transformed = m_transformation*(*s) ;
				result.update(transformed);
				result.extend(m_extent) ;
			}
			break ;
		case triangle:
			{
				Triangle2 * t = (Triangle2*)m_skeleton ;
				Triangle2 transformed = m_transformation*(*t) ;
				result.update(transformed) ;
				result.extend(m_extent) ;
			}
			break ;
		}
		return result ;
	}

	Shape Shape::getTransformed(const Math::Matrix3x3<Config::Real> & transfo) const
	{
		Shape result(*this) ;
		result.setTransform(transfo*result.getTransform()) ;
		return result ;
	}
}