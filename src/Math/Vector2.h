#ifndef _Math_Vector2_H
#define _Math_Vector2_H

#include <Math/Vector.h>
#include <Math/Constant.h>


namespace Math
{
	///////////////////////////////////////////////////////////////////////////////////
	/// \brief Two dimensional vectors.
	/// 	   
	/// \param Float scalar type.
	/// 
	/// \author F. Lamarche, University of Rennes 1.
	///////////////////////////////////////////////////////////////////////////////////
	template <class Float>
	class Vector2 : public Vector<Float, 2>
	{
	public:
		///////////////////////////////////////////////////////////////////////////////////
		/// \brief Copy constructor
		/// 
		/// \param v
		/// 
		/// \author F. Lamarche, University of Rennes 1.
		///////////////////////////////////////////////////////////////////////////////////
		Vector2(Vector<Float, 2> const & v)
			: Vector<Float, 2>(v)
		{}

		///////////////////////////////////////////////////////////////////////////////////
		/// \brief Constructor
		/// 
		/// \param x X coordinate
		/// \param y Y coordinate
		/// 
		/// \author F. Lamarche, University of Rennes 1.
		///////////////////////////////////////////////////////////////////////////////////
		Vector2(Float const & x=0.0, Float const & y=0.0)
		{
			(*this)[0] = x ;
			(*this)[1] = y ;
		}

		///////////////////////////////////////////////////////////////////////////////////
		/// \brief Computes polar coordinates
		/// 
		/// \param r vector length
		/// \param theta angle with X axis (in radians)
		/// 
		/// \author F. Lamarche, University of Rennes 1.
		///////////////////////////////////////////////////////////////////////////////////
		void polarCoordinates(Float & r, Float & theta) const
		{
			r = norm() ;
			Float x = (*this)[0] ;
			Float y = (*this)[1] ;

			if(x==0)
			{
				if(y>0)
				{
					theta = Float(Math::pi)/Float(2.0) ;
				}
				else
				{
					theta =  -Float(Math::pi)/Float(2.0) ;
				}
			}
			else if(x>0)
			{
				theta = atan(y/x) ;
			}
			else // x<0
			{
				if(y>0)
				{
					theta = atan(y/x)+Float(Math::pi) ;
				}
				else
				{
					theta = atan(y/x)-Float(Math::pi) ;
				}
			}
		}

		///////////////////////////////////////////////////////////////////////////////////
		/// \brief Computes a rotation of the vector
		/// 
		/// \param angle the rotation angle (in radians)
		/// \return the rotated vector
		/// 
		/// \author F. Lamarche, University of Rennes 1.
		///////////////////////////////////////////////////////////////////////////////////
		Vector2<Float> rotate(Float angle) const
		{
			Vector2<Float> result ;
			result[0] = Float(cos(angle))*(*this)[0]-Float(sin(angle))*(*this)[1] ;
			result[1] = Float(sin(angle))*(*this)[0]+Float(cos(angle))*(*this)[1] ;
			return result ;
		}


		///////////////////////////////////////////////////////////////////////////////////
		/// \brief Computes a rotation of the vector (angle : PI/2)
		///  
		/// \return the rotated vector
		/// 
		/// \author F. Lamarche, University of Rennes 1.
		///////////////////////////////////////////////////////////////////////////////////
		Vector2<Float> rotate90() const
		{ return Vector2<Float>(-(*this)[1], (*this)[0]) ; }

		///////////////////////////////////////////////////////////////////////////////////
		/// \brief Computes a rotation of the vector (angle : PI)
		/// 
		/// \return the rotated vector
		/// 
		/// \author F. Lamarche, University of Rennes 1.
		///////////////////////////////////////////////////////////////////////////////////
		Vector2<Float> rotate180() const
		{ return (*this)*(-1.0) ; }

		///////////////////////////////////////////////////////////////////////////////////
		/// \brief Computes a rotation of the vector (angle : 3/2*PI)
		/// 
		/// \return the rotated vector
		/// 
		/// \author F. Lamarche, University of Rennes 1.
		///////////////////////////////////////////////////////////////////////////////////
		Vector2<Float> rotate270() const
		{ return (*this).rotate90().rotate180() ; }

		static Float det(Vector2 const & v1, Vector2 const & v2)
		{
			return v1[0]*v2[1]-v1[1]*v2[0] ;
		}
	} ;
}


#endif
