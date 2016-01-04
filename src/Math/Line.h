#ifndef _Math_Line_H
#define _Math_Line_H

#include <Math/Vector.h>
#include <Math/finite.h>

namespace Math
{

	///////////////////////////////////////////////////////////////////////////////////
	/// \brief A N dimensional line
	/// 	   
	/// \param Float scalar type
	/// \param dimensions number of dimensions
	/// 
	/// \author F. Lamarche, University of Rennes 1.
	///////////////////////////////////////////////////////////////////////////////////
	template <class Float, int dimensions>
	class Line 
	{
	protected:
		//! The origin of the line. 
		Math::Vector<Float, dimensions> m_origin ;
		//! The direction of the line. 
		Math::Vector<Float, dimensions> m_direction ;

	public:

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Line(Math::Vector<Float, dimensions> const & origin=Math::Vector<Float, dimensions>(),
		/// 	Math::Vector<Float, dimensions> const & p2=Math::Vector<Float, dimensions>())
		///
		/// \brief	Constructor. Intializes a line thanls to two points belonging to it.
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	20/12/2009
		///
		/// \param origin		 The first point. 
		/// \param direction The direction of the line (it is automatically normalized). 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Line(Math::Vector<Float, dimensions> const & origin=Math::Vector<Float, dimensions>(), Math::Vector<Float, dimensions> const & direction=Math::Vector<Float, dimensions>())
			: m_origin(origin), m_direction(direction.normalized())
		{}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	const Math::Vector<Float, dimensions> & origin() const
		///
		/// \brief	Return the origin of the line. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	20/12/2009
		///
		/// \return	. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		const Math::Vector<Float, dimensions> & origin() const
		{
			return m_origin ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	const Math::Vector<Float, dimensions> & direction() const
		///
		/// \brief	Returns the direction of the line. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	20/12/2009
		///
		/// \return	. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		const Math::Vector<Float, dimensions> & direction() const
		{
			return m_direction ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	void invertDirection()
		///
		/// \brief	Inverses line direction. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	01/06/2010
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void invertDirection()
		{
			m_direction = -m_direction ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	bool isDegenerated() const
		///
		/// \brief	Query if this line is degenerated. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	20/12/2009
		///
		/// \return	true if degenerated, false if not. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		bool isDegenerated() const
		{
			Float norm2 = m_direction*m_direction ;
			return !isFinite(norm2) || norm2==Float(0.0) ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	bool parallel(Line const & line) const
		///
		/// \brief	Tests if the this line is parallel to 'line'. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	20/12/2009
		///
		/// \param line the line. 
		///
		/// \return	true if the two lines are parallel, false if not. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		bool parallel(Line const & line) const
		{
			return m_direction==line.m_direction ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	bool belongs(Math::Vector<Float, dimensions> const & point) const
		///
		/// \brief	Tests if the point belongs to the line. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	20/12/2009
		///
		/// \param point the point. 
		///
		/// \return	true if the point belongs to the line, false if not. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		bool belongs(Math::Vector<Float, dimensions> const & point) const
		{
			return distance(point)==Float(0.0) ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Float projectedAbscissa(Math::Vector<Float, dimensions> const & point) const
		///
		/// \brief	Return the curvilinear abscissa of the projection of the point on the line. 
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
			return (point-m_origin)*m_direction ;				
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Math::Vector<Float, dimensions> project(Math::Vector<Float,
		/// 	dimensions> const & point) const
		///
		/// \brief	Returns the projection of the point on the line. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	20/12/2009
		///
		/// \param [in,out]	point	the point. 
		///
		/// \return	. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Math::Vector<Float, dimensions> project(Math::Vector<Float, dimensions> const & point) const
		{
			return m_origin+m_direction*projectedAbscissa(point) ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Math::Vector<Float, dimensions> projectionNormal(Math::Vector<Float,
		/// 	dimensions> const & point) const
		///
		/// \brief	Return the vector 'v' such as project(point)+v==point. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	20/12/2009
		///
		/// \param [in,out]	point the point. 
		///
		/// \return	. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Math::Vector<Float, dimensions> projectionNormal(Math::Vector<Float, dimensions> const & point) const
		{
			return point-project(point) ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Float distance(Math::Vector<Float, dimensions> const & point) const
		///
		/// \brief	Returns the distance between the point and the line. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	20/12/2009
		///
		/// \param point	the point. 
		///
		/// \return	. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Float distance(Math::Vector<Float, dimensions> const & point) const
		{
			return (point-project(point)).norm() ;
		}

	};

}

#endif