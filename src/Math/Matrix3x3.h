#ifndef _Math_Matrix3x3_H
#define _Math_Matrix3x3_H

#include <cassert>
#include <Math/Vector3.h>
#include <Math/Segment2D.h>
#include <Math/Triangle2D.h>

namespace Math
{
	///////////////////////////////////////////////////////////////////////////////////
	/// \brief 3x3 matrix class. Useful to compute 2D transformations with homogeneous
	/// 	   coordinates.
	/// 
	/// \author F. Lamarche, University of Rennes 1.
	///////////////////////////////////////////////////////////////////////////////////
	template <class Float>
	class Matrix3x3
	{
	protected:
		/// Matrix stored in row major format
		Math::Vector3<Float> m_data[3] ;

	public:
		///////////////////////////////////////////////////////////////////////////////////
		/// \brief Default constructor. Constructs a zero matrix.
		/// 
		/// \author F. Lamarche, University of Rennes 1.
		///////////////////////////////////////////////////////////////////////////////////
		Matrix3x3()
		{
			Math::Vector3<Float> zero(0.0, 0.0, 0.0) ;
			m_data[0] = zero ;
			m_data[1] = zero ;
			m_data[2] = zero ;
		}

		///////////////////////////////////////////////////////////////////////////////////
		/// \brief Contructor with user provided rows.
		/// 
		/// \param r0 the first row
		/// \param r1 the second row
		/// \param r2 the third row
		/// 
		/// \author F. Lamarche, University of Rennes 1.
		///////////////////////////////////////////////////////////////////////////////////
		Matrix3x3(Math::Vector3<Float> const & r0, Math::Vector3<Float> const & r1, Math::Vector3<Float> const & r2)
		{
			m_data[0] = r0 ;
			m_data[1] = r1 ;
			m_data[2] = r2 ;
		}

		///////////////////////////////////////////////////////////////////////////////////
		/// \brief Row retrieval.
		/// 
		/// \param index The index of the row (starting from 0).
		/// \return 
		/// 
		/// \author F. Lamarche, University of Rennes 1.
		///////////////////////////////////////////////////////////////////////////////////
		const Math::Vector3<Float> & getRow(int index) const
		{
			assert(index>=0) ;
			assert(index<3) ;
			return m_data[index] ;
		}

		///////////////////////////////////////////////////////////////////////////////////
		/// \brief Column retrieval.
		/// 
		/// \param index The index of the column (starting from 0)
		/// \return 
		/// 
		/// \author F. Lamarche, University of Rennes 1.
		///////////////////////////////////////////////////////////////////////////////////
		Math::Vector3<Float> getColumn(int index) const
		{
			assert(index>=0) ;
			assert(index<3) ;
			return Math::Vector3<Float>(m_data[0][index], m_data[1][index], m_data[2][index]) ;
		}

		///////////////////////////////////////////////////////////////////////////////////
		/// \brief returns the scalar at location (row, column)
		/// 
		/// \param row the index of the row (starting from 0)
		/// \param column the index of the row (starting from 1)
		/// \return 
		/// 
		/// \author F. Lamarche, University of Rennes 1.
		///////////////////////////////////////////////////////////////////////////////////
		Float & operator() (int row, int column)
		{
			assert(row>=0 && row<3) ;
			assert(column>=0 && column<3) ;
			return m_data[row][column] ;
		}

		///////////////////////////////////////////////////////////////////////////////////
		/// \brief returns the scalar at location (row, column)
		/// 
		/// \param row the index of the row (starting from 0)
		/// \param column the index of the row (starting from 1)
		/// \return 
		/// 
		/// \author F. Lamarche, University of Rennes 1.
		///////////////////////////////////////////////////////////////////////////////////
		const Float & operator() (int row, int column) const
		{
			return m_data[row][column] ;
		}

		///////////////////////////////////////////////////////////////////////////////////
		/// \brief Matrix sum 
		/// 
		/// \param matrix
		/// \return 
		/// 
		/// \author F. Lamarche, University of Rennes 1.
		///////////////////////////////////////////////////////////////////////////////////
		Matrix3x3 operator+ (const Matrix3x3 & matrix) const
		{
			return Matrix3x3(getRow(0)+matrix.getRow(0), getRow(1)+matrix.getRow(1), getRow(2)+matrix.getRow(2)) ;
		}

		///////////////////////////////////////////////////////////////////////////////////
		/// \brief Matrix difference
		/// 
		/// \param matrix
		/// \return 
		/// 
		/// \author F. Lamarche, University of Rennes 1.
		///////////////////////////////////////////////////////////////////////////////////
		Matrix3x3 operator- (const Matrix3x3 & matrix) const
		{
			return Matrix3x3(getRow(0)-matrix.getRow(0), getRow(1)-matrix.getRow(1), getRow(2)-matrix.getRow(2)) ;
		}

		///////////////////////////////////////////////////////////////////////////////////
		/// \brief Matrix multiplication
		/// 
		/// \param matrix
		/// \return 
		/// 
		/// \author F. Lamarche, University of Rennes 1.
		///////////////////////////////////////////////////////////////////////////////////
		Matrix3x3 operator* (const Matrix3x3 & matrix) const
		{
			Matrix3x3 result ;
			for(int otherColumn=0 ; otherColumn<3 ; ++otherColumn)
			{
				Math::Vector3<Float> column = matrix.getColumn(otherColumn) ;
				for(int thisRow=0 ; thisRow<3 ; ++thisRow)
				{
					result(thisRow, otherColumn) = column*getRow(thisRow) ;
				}
			}
			return result ;
		}

		///////////////////////////////////////////////////////////////////////////////////
		/// \brief Matrix - vector multiplication
		/// 
		/// \param v
		/// \return 
		/// 
		/// \author F. Lamarche, University of Rennes 1.
		///////////////////////////////////////////////////////////////////////////////////
		Vector3<Float> operator* (Math::Vector3<Float> const & v) const
		{
			return Math::Vector3<Float>(getRow(0)*v, getRow(1)*v, getRow(2)*v) ;
		}

		///////////////////////////////////////////////////////////////////////////////////
		/// \brief Matrix - vector multiplication in homogeneous coordinates
		/// 
		/// \param v The vector
		/// 
		/// \author F. Lamarche, University of Rennes 1.
		///////////////////////////////////////////////////////////////////////////////////
		Vector2<Float> operator* (Math::Vector2<Float> const & v) const
		{
			Math::Vector3<Float> result = (*this)*Math::Vector3<Float>(v[0], v[1], 1.0) ;
			return Math::Vector2<Float>(result[0], result[1])/result[2] ;
		}

		///////////////////////////////////////////////////////////////////////////////////
		/// \brief Computes the transformation of a 2D segment in homogeneous coordinates
		/// 
		/// \param segment The segment
		/// \return The transformed segment
		/// 
		/// \author F. Lamarche, University of Rennes 1.
		///////////////////////////////////////////////////////////////////////////////////
		Segment2D<Float> operator* (Math::Segment2D<Float> const & segment) const
		{
			return Math::Segment2D<Float>((*this)*segment.p1(), (*this)*segment.p2()) ;
		}

		///////////////////////////////////////////////////////////////////////////////////
		/// \brief Computes the transformation of a 2D segment in homogeneous coordinates
		/// 
		/// \param triangle the triangle
		/// \return the transformed triangle
		/// 
		/// \author F. Lamarche, University of Rennes 1.
		///////////////////////////////////////////////////////////////////////////////////
		Triangle2D<Float> operator* (Math::Triangle2D<Float> const & triangle) const
		{
			return Math::Triangle2D<Float>((*this)*triangle[0], (*this)*triangle[1], (*this)*triangle[2]) ;
		}

		///////////////////////////////////////////////////////////////////////////////////
		/// \brief Matrix scalar multiplication
		/// 
		/// \param value
		/// \return 
		/// 
		/// \author F. Lamarche, University of Rennes 1.
		///////////////////////////////////////////////////////////////////////////////////
		Matrix3x3 operator* (Float value) const
		{
			return Matrix3x3(getRow(0)*value, getRow(1)*value, getRow(2)*value) ;
		}

		///////////////////////////////////////////////////////////////////////////////////
		/// \brief Matrix scalar division
		/// 
		/// \param value
		/// \return 
		/// 
		/// \author F. Lamarche, University of Rennes 1.
		///////////////////////////////////////////////////////////////////////////////////
		Matrix3x3 operator/ (Float value) const
		{
			return Matrix3x3(getRow(0)/value, getRow(1)/value, getRow(2)/value) ;
		}

		///////////////////////////////////////////////////////////////////////////////////
		/// \brief Returns the identity matrix
		/// 
		/// \author F. Lamarche, University of Rennes 1.
		///////////////////////////////////////////////////////////////////////////////////
		static Matrix3x3<Float> getIdentity()
		{
			return Matrix3x3<Float>(Vector3<Float>(1.0,0.0,0.0), Vector3<Float>(0.0,1.0,0.0), Vector3<Float>(0.0, 0.0, 1.0)) ;
		}

		///////////////////////////////////////////////////////////////////////////////////
		/// \brief Returns a rotation matrix in homogeneous coordinates
		/// 
		/// \param angle the rotation angle
		/// 
		/// \author F. Lamarche, University of Rennes 1.
		///////////////////////////////////////////////////////////////////////////////////
		static Matrix3x3<Float> getRotationHomogeneous(Float angle)
		{
			Float cosine = cos(angle) ;
			Float sine = sin(angle) ;
			return Matrix3x3(Math::Vector3<Float>(cosine, -sine, 0.0), Math::Vector3<Float>(sine, cosine, 0.0), Math::Vector3<Float>(0.0, 0.0, 1.0)) ;
		}

		///////////////////////////////////////////////////////////////////////////////////
		/// \brief Returns a translation matrix in homogeneous coordinates
		/// 
		/// \param v the translation vector
		/// 
		/// \author F. Lamarche, University of Rennes 1.
		///////////////////////////////////////////////////////////////////////////////////
		static Matrix3x3<Float> getTranslationHomogeneous(Math::Vector2<Float> const & v)
		{
			return Matrix3x3(Vector3<Float>(1.0, 0.0, v[0]), Vector3<Float>(0.0, 1.0, v[1]), Vector3<Float>(0.0, 0.0, 1.0)) ;
		}

		///////////////////////////////////////////////////////////////////////////////////
		/// \brief Return a scaling matrix in homogeneous cordinates.
		/// 
		/// \param scaleX scale factor along the X axis
		/// \param scaleY scale factor along the Y axis
		/// 
		/// \author F. Lamarche, University of Rennes 1.
		///////////////////////////////////////////////////////////////////////////////////
		static Matrix3x3<Float> getScaleHomogeneous(Float scaleX, Float scaleY)
		{
			return Matrix3x3(Vector3<Float>(scaleX, 0.0, 0.0), Vector3<Float>(0.0, scaleY, 0.0), Vector3<Float>(0.0, 0.0, 1.0)) ;
		}
 	};


}

#endif