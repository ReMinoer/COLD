#ifndef _Triggers_Shape_H
#define _Triggers_Shape_H

#include <Math/Vector2.h>
#include <Math/Circle2D.h>
#include <Math/Triangle2D.h>
#include <Math/distance2D.h>
#include <Math/Matrix3x3.h>
#include <Config/Real.h>

namespace Triggers
{
	///////////////////////////////////////////////////////////////////////////////////
	/// \brief A 2D shape that is defined by a skeleton (point, segment, triangle, box)
	/// 	   and a spatial extent around this skeleton.
	/// 
	/// \author F. Lamarche, University of Rennes 1.
	///////////////////////////////////////////////////////////////////////////////////
	class Shape
	{
	public:
		typedef Math::Vector2<Config::Real> Vector2 ;
		typedef Math::Segment2D<Config::Real> Segment2 ;
		typedef Math::Triangle2D<Config::Real> Triangle2 ;

	protected:
		///////////////////////////////////////////////////////////////////////////////////
		/// \brief Type of the skeleton data
		/// 
		/// \author F. Lamarche, University of Rennes 1.
		///////////////////////////////////////////////////////////////////////////////////
		typedef enum 
		{
			point=0,
			segment=1,
			triangle=2,
			last=3
		} 
		SkeletonType ;

		/// Type of the skeleton
		SkeletonType m_type ;
		/// Not really nice, but works... sorry
		void * m_skeleton ;
		/// Spatial extent around the skeleton
		Config::Real m_extent ;
		/// Transformation associated to the shape
		Math::Matrix3x3<Config::Real> m_transformation ;

	public:
		///////////////////////////////////////////////////////////////////////////////////
		/// \brief Constructor
		/// 
		/// \param skeleton a point skeleton
		/// \param extent the spatial extent
		/// \return 
		/// 
		/// \author F. Lamarche, University of Rennes 1.
		///////////////////////////////////////////////////////////////////////////////////
		Shape(Vector2 const & skeleton, Config::Real extent);

		///////////////////////////////////////////////////////////////////////////////////
		/// \brief Constructor
		/// 
		/// \param skeleton a segment skeleton
		/// \param extent the spatial extent
		/// \return 
		/// 
		/// \author F. Lamarche, University of Rennes 1.
		///////////////////////////////////////////////////////////////////////////////////
		Shape(Segment2 const & skeleton, Config::Real extent);

		///////////////////////////////////////////////////////////////////////////////////
		/// \brief Constructor
		/// 
		/// \param skeleton a triangle skeleton
		/// \param extent the spatial extent
		/// \return 
		/// 
		/// \author F. Lamarche, University of Rennes 1.
		///////////////////////////////////////////////////////////////////////////////////
		Shape(Triangle2 const & skeleton, Config::Real extent);

		///////////////////////////////////////////////////////////////////////////////////
		/// \brief Copy constructor
		/// 
		/// \param shape The copied shape
		/// 
		/// \author F. Lamarche, University of Rennes 1.
		///////////////////////////////////////////////////////////////////////////////////
		Shape(Shape const & shape);

		///////////////////////////////////////////////////////////////////////////////////
		/// \brief Assignation operator
		/// 
		/// \param shape The other shape
		/// \return a reference on this
		/// 
		/// \author F. Lamarche, University of Rennes 1.
		///////////////////////////////////////////////////////////////////////////////////
		Shape & operator= (const Shape & shape);

		///////////////////////////////////////////////////////////////////////////////////
		/// \brief Destructor
		/// 
		/// \author F. Lamarche, University of Rennes 1.
		///////////////////////////////////////////////////////////////////////////////////
		~Shape();

		///////////////////////////////////////////////////////////////////////////////////
		/// \brief Returns the transformation associated to this shape
		/// 
		/// \return 
		/// 
		/// \author F. Lamarche, University of Rennes 1.
		///////////////////////////////////////////////////////////////////////////////////
		const Math::Matrix3x3<Config::Real> getTransform() const;

		///////////////////////////////////////////////////////////////////////////////////
		/// \brief Sets the transformation associated to this shape
		/// 
		/// \param tranform
		/// \return 
		/// 
		/// \author F. Lamarche, University of Rennes 1.
		///////////////////////////////////////////////////////////////////////////////////
		void setTransform(Math::Matrix3x3<Config::Real> const & tranform);

		///////////////////////////////////////////////////////////////////////////////////
		/// \brief Apply current transformation on associated geometry and assigns identity
		/// 	   to the current transformation.
		/// 
		/// \author F. Lamarche, University of Rennes 1.
		///////////////////////////////////////////////////////////////////////////////////
		void applyTransform();

		///////////////////////////////////////////////////////////////////////////////////
		/// \brief Computes the bounding box of this shape
		/// 
		/// \return The shape's bounding box.
		/// 
		/// \author F. Lamarche, University of Rennes 1.
		///////////////////////////////////////////////////////////////////////////////////
		Math::BoundingBox2D<Config::Real> getBoundingBox() const ;

		///////////////////////////////////////////////////////////////////////////////////
		/// \brief Returns a copy of this shape in which the new transformation has been
		/// 	   applied.
		/// 
		/// \param transfo The applied transformation.
		/// \return 
		/// 
		/// \author F. Lamarche, University of Rennes 1.
		///////////////////////////////////////////////////////////////////////////////////
		Shape getTransformed(const Math::Matrix3x3<Config::Real> & transfo) const ;

		///////////////////////////////////////////////////////////////////////////////////
		/// \brief Returns the distance between two shapes. If distance is 0.0, shapes are
		/// 	   colliding or inter penetrating. 
		/// 
		/// \param shape1 The first shape
		/// \param shape2 The second one
		/// \return The distance between shape1 and shape2
		/// 
		/// \author F. Lamarche, University of Rennes 1.
		///////////////////////////////////////////////////////////////////////////////////
		static Config::Real distance(Shape const & shape1, Shape const & shape2);

	private:
		static Config::Real subDistance(Shape const & shape1, Shape const & shape2);
	};
}

#endif