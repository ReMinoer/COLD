#ifndef _Math_BoundingBox_H
#define _Math_BoundingBox_H

#include <Math/Interval.h>
#include <Math/Vector.h>
#include <Ext/std/static_vector.h>

namespace Math
{
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \class	BoundingBox
	///
	/// \brief	N-dimensional bounding box. 
	///
	/// \param Float type of floating point values.
	/// \param dimensions Number of dimensions of the space.
	/// 
	/// \author	Fabrice Lamarche, University Of Rennes 1
	/// \date	17/12/2009
	////////////////////////////////////////////////////////////////////////////////////////////////////
	template <class Float, int dimensions>
	class BoundingBox 
	{
	protected:
		Math::Vector<Float, dimensions> m_center ;
		Math::Vector<Float, dimensions> m_extent ;

		void updateMinMax(Math::Vector<Float,dimensions> const & min, Math::Vector<Float, dimensions> const & max)
		{
			m_center = (min+max)*0.5 ;
			m_extent = (max-m_center).zeroIfNegativeCoordinate() ;
		}

	public:
		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	BoundingBox()
		///
		/// \brief	Default constructor. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	17/12/2009
		////////////////////////////////////////////////////////////////////////////////////////////////////
		BoundingBox()
		{
			m_center = 0.0 ;
			m_extent = 0.0 ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	BoundingBox(Math::Vector<Float,dimensions> const & min, Math::Vector<Float,
		/// 	dimensions> const & max)
		///
		/// \brief	Constructor. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	17/12/2009
		///
		/// \param [in,out]	min	the minimum values for each coordinate. 
		/// \param [in,out]	max	the maximum values for each coordinate. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		BoundingBox(Math::Vector<Float,dimensions> const & min, Math::Vector<Float,dimensions> const & max)
		{
			updateMinMax(min, max) ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Math::Vector<Float, dimensions> minVertex() const
		///
		/// \brief	Return a vector containing minimal coordinates. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	17/12/2009
		///
		/// \return	. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Math::Vector<Float, dimensions> minVertex() const
		{
			return m_center-m_extent ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Math::Vector<Float, dimensions> maxVertex() const
		///
		/// \brief	Returns a vector containing maximal coordinates. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	17/12/2009
		///
		/// \return	. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Math::Vector<Float, dimensions> maxVertex() const
		{
			return m_center+m_extent ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Math::Vector<Float, dimensions> center() const
		///
		/// \brief	Returns the center of the box. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	17/12/2009
		///
		/// \return	. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Math::Vector<Float, dimensions> const & center() const
		{
			return m_center ;
		}

		Math::Vector<Float, dimensions> const & extent() const
		{
			return m_extent ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Math::Vector<Float, dimensions> delta(int dimension) const
		///
		/// \brief	Returns a vector containing the delta value in the given dimension. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	17/12/2009
		///
		/// \param	dimension	The dimension. 
		///
		/// \return	. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Math::Vector<Float, dimensions> delta(int dimension) const
		{
			Math::Vector<Float, dimensions> result ;
			result[dimension] = m_extent[dimension]*Float(2.0) ;
			return result ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Math::Interval<Float> const & interval(int dimension) const
		///
		/// \brief	Returns the interval corresponding to the given dimension. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	16/12/2009
		///
		/// \param	dimension	The dimension. 
		///
		/// \return	The interval. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Math::Interval<Float> interval(int dim) const
		{
			assert(dim>=0 && dim<dimensions) ;
			return Math::Interval<Float>(m_center[dim]-m_extent[dim], m_center[dim]+m_extent[dim]) ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Vector3<Float> deltaSize() const
		///
		/// \brief	Returns the vector on the diagonal of the box. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	04/12/2009
		///
		/// \return	. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Math::Vector<Float,dimensions> deltaSize() const
		{
			return m_extent*Float(2.0) ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	bool isEmpty() const
		///
		/// \brief	Query if this box is empty. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	16/12/2009
		///
		/// \return	true if empty, false if not. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		bool isEmpty() const
		{
			return m_extent.norm2()==Float(0.0) ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	void reset()
		///
		/// \brief	Resets this box to an empty box. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	17/12/2009
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void reset() 
		{
			m_extent = Float(0.0) ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	void divide(Ext::std::static_vector<BoundingBox, (1<<dimensions)> & result)
		///
		/// \brief	Divides the bounding box in two parts along each axis. This generates (1<<dimensions) new
		///			bounding boxes. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	19/12/2009
		///
		/// \param [in,out]	result	the result. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void divide(Ext::std::static_vector<BoundingBox, (1<<dimensions)> & result) const
		//void divide(BoundingBox * result) const
		{
			//Ext::std::static_vector<Math::Interval<Float>, dimensions*2> limits(dimensions*2) ;
			Ext::std::static_vector<Math::Interval<Float>, (1<<dimensions)> limits((1<<dimensions)) ;
			for(int cpt=0 ; cpt<dimensions ; ++cpt)
			{
				Math::Interval<Float> i = interval(cpt) ;
				limits[cpt*2]=(Math::Interval<Float>(i.inf(), i.middle())) ;
				limits[cpt*2+1]=(Math::Interval<Float>(i.middle(), i.sup())) ;
			}
			result.resize(1<<dimensions) ;
			for(int cpt=0 ; cpt<(1<<dimensions) ; ++cpt)
			{
				BoundingBox & box = result[cpt] ;
				for(int bit=0 ; bit<dimensions ; bit++)
				{
					int mask = (1<<bit) ;
					int inc = (cpt & mask)?1:0 ;
					box.setInterval(bit, limits[bit*2+inc]) ;
				}
			}
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	int dividedLocate(Math::Vector<Float, dimensions> const & point)
		///
		/// \brief	Returns the index, in the bounding box table obtained by 
		///			BoundingBox<Float, dimensions>::divide, of the bounding box containing the point. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	19/12/2009
		///
		/// \param point the point. 
		///
		/// \return	The index of the sub-bounding box. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		int dividedLocate(Math::Vector<Float, dimensions> const & point) const
		{
			int result = 0 ;
			for(int cpt=0 ; cpt<dimensions ; ++cpt)
			{
				bool sup = point[cpt]>interval(cpt).middle() ;
				result |= (sup<<cpt) ;
			}
			return result ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	void update(Math::Vector<Float, 2> const & pos)
		///
		/// \brief	Updates the box such as it contains the point. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	16/12/2009
		///
		/// \param [in,out]	pos	the point. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void update(Math::Vector<Float, dimensions> const & pos)
		{		
			updateMinMax(minVertex().simdMin(pos), maxVertex().simdMax(pos)) ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	void compute(Collection const & vectorSet)
		///
		/// \brief	Computes the bounding box of the Math::Vector<Float, dimensions> collection. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	17/12/2009
		///
		/// \param vectorSet	The set of vectors. 
		/// \param Collection A collection type providing a const_iterator internal class (STL compatible)
		////////////////////////////////////////////////////////////////////////////////////////////////////
		template <class Collection>
		void compute(Collection const & vectorSet)
		{
			if(vectorSet.empty())
			{
				return ;
			}
			Math::Vector<Float, dimensions> minV = *vectorSet.begin(), maxV = *vectorSet.begin() ; // minVertex(), maxV = maxVertex() ;
			for(typename Collection::const_iterator it=vectorSet.begin(), end=vectorSet.end() ; it!=end ; ++it)
			{
				minV = minV.simdMin(*it) ;
				maxV = maxV.simdMax(*it) ;
			}
			updateMinMax(minV, maxV) ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	bool isInside(Math::Vector<Float, 2> const & pos) const
		///
		/// \brief	Query if 'pos' is inside. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	16/12/2009
		///
		/// \param [in,out]	pos	the position. 
		///
		/// \return	true if inside, false if not. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		bool isInside(Math::Vector<Float, dimensions> const & pos) const
		{
			Math::Vector<Float, dimensions> zero(Float(0.0)) ;
			return ((pos-m_center).simdAbs()-m_extent).simdMax(zero)==zero ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	void setInterval(int dim, Math::Interval<Float> const & interval)
		///
		/// \brief	Sets an interval. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	19/12/2009
		///
		/// \param	dim					The dimension. 
		/// \param [in,out]	interval	the interval. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void setInterval(int dim, Math::Interval<Float> const & interval)
		{
			m_center[dim] = interval.middle() ;
			m_extent[dim] = interval.delta()/2.0 ;
		}

		/** \name Operations */
		//@{

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	BoundingBox2D operator+(BoundingBox2D<Float> const & box) const
		///
		/// \brief	Merges the two boxes. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	16/12/2009
		///
		/// \param [in,out]	box	the box. 
		///
		/// \return	The result of the operation. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		BoundingBox operator+(BoundingBox const & box) const
		{
			BoundingBox result ;
			result.updateMinMax(minVertex().simdMin(box.minVertex()), maxVertex().simdMax(box.maxVertex())) ;
			return result ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	BoundingBox2D operator*(BoundingBox2D<Float> const & box) const
		///
		/// \brief	Intersects the two boxes. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	16/12/2009
		///
		/// \param [in,out]	box	the box. 
		///
		/// \return	The result of the operation. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		BoundingBox operator*(BoundingBox const & box) const
		{
			BoundingBox result ;
			result.updateMinMax(minVertex().simdMax(box.minVertex()), maxVertex().simdMin(box.maxVertex())) ;
			return result ;
		}

		//@}

		/** \name Distances */
		//@{

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Float distance(Math::Vector<Float, 2> const & pos)
		///
		/// \brief	Computes the squared distance between a point and the box. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	16/12/2009
		///
		/// \param [in,out]	pos	the position. 
		///
		/// \return	. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		__forceinline Float distance2(Math::Vector<Float, dimensions> const & pos) const
		{
			Math::Vector<Float, dimensions> zero(Float(0.0)) ;
			Math::Vector<Float, dimensions> tmp = ((pos-m_center).simdAbs()-m_extent).simdMax(zero) ;
			return tmp * tmp ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Float distance(Math::Vector<Float, 2> const & pos)
		///
		/// \brief	Computes the distance between a point and the box. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	16/12/2009
		///
		/// \param [in,out]	pos	the position. 
		///
		/// \return	. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Float distance(Math::Vector<Float, dimensions> const & pos) const
		{
			return sqrt(distance2(pos)) ;
		}


		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Float distanceToBorders(Math::Vector<Float, dimensions> const & pos) const
		///
		/// \brief	Squared distance between pos and the bounding box borders. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	20/04/2010
		///
		/// \param [in,out]	pos	the position. 
		///
		/// \return	. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Float distanceToBorders2(Math::Vector<Float, dimensions> const & pos) const
		{
			Math::Vector<Float, dimensions> tmp = ((pos-m_center).simdAbs()-m_extent) ;
			return tmp * tmp ;				
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Float distanceToBorders(Math::Vector<Float, dimensions> const & pos) const
		///
		/// \brief	Distance between pos and the bounding box borders. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	20/04/2010
		///
		/// \param [in,out]	pos	the position. 
		///
		/// \return	. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Float distanceToBorders(Math::Vector<Float, dimensions> const & pos) const
		{
			return sqrt(distanceToBorders2(pos)) ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Float distance(BoundingBox const & box) const
		///
		/// \brief	Return the squared distance between two bounding boxes. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	20/12/2009
		///
		/// \param [in,out]	box	the box. 
		///
		/// \return	. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Float distance2(BoundingBox const & box) const
		{
			Float result = Float(0.0) ;
			for(int cpt=0 ; cpt<dimensions ; ++cpt)
			{
				Float tmp = interval(cpt).distance(box.interval(cpt)) ;
				result = result + tmp*tmp ;
			}
			return result ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Float distance(BoundingBox const & box) const
		///
		/// \brief	Return the distance between two bounding boxes. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	20/12/2009
		///
		/// \param [in,out]	box	the box. 
		///
		/// \return	. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Float distance(BoundingBox const & box) const
		{
			return sqrt(distance2(box)) ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	int vertexSize() const
		///
		/// \brief	Returns the number of vertices of the box. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	22/04/2010
		///
		/// \return	the number of vertices of the box. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		int vertexSize()  const
		{
			return 1<<dimensions ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Math::Vector<Float, dimensions> getVertex(int index) const
		///
		/// \brief	Gets the vertex of given index. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	22/04/2010
		///
		/// \param	index	Zero-based index of the. 
		///
		/// \return	The vertex. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Math::Vector<Float, dimensions> getVertex(int index) const
		{
			assert(index>=0 && index<vertexSize()) ;
			Math::Vector<Float, dimensions> result ;
			for(int cpt=0 ; cpt<dimensions ; ++cpt)
			{
				int i = (index>>cpt) & 1 ;
				result[cpt] = interval(cpt)[i] ;
			}
			return result ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	bool isInside(Math::BoundingBox<Float, dimensions> const & box) const
		///
		/// \brief	Query if 'box' is inside. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	22/04/2010
		///
		/// \param [in,out]	box	the box. 
		///
		/// \return	true if inside, false if not. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		bool isInside(Math::BoundingBox<Float, dimensions> const & box) const
		{
			return isInside(box.minVertex()) && isInside(box.maxVertex()) ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Float volume() const
		///
		/// \brief	Returns the volume of this box. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	22/04/2010
		///
		/// \return	the volume of this box. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Float volume() const
		{
			Float result(1.0) ;
			for(int cpt=0 ; cpt<dimensions ; ++cpt)
			{
				result *= m_extent[cpt]*2.0 ;
			}
			return result ;
		}

		///////////////////////////////////////////////////////////////////////////////////
		/// \brief Returns the vector in the bounding box local coordinate system
		/// 
		/// \param v The vector
		/// \return The vector in the local coordinate system
		/// 
		/// \author F. Lamarche, University of Rennes 1.
		///////////////////////////////////////////////////////////////////////////////////
		Math::Vector<Float, dimensions> toLocal(Math::Vector<Float, dimensions> const & v) const
		{
			return v-minVertex() ;
		}

		///////////////////////////////////////////////////////////////////////////////////
		/// \brief Converts a vector in the local coordinate system to a vector in the global coordinate system
		/// 
		/// \param v
		/// \return 
		/// 
		/// \author F. Lamarche, University of Rennes 1.
		///////////////////////////////////////////////////////////////////////////////////
		Math::Vector<Float, dimensions> toGlobal(Math::Vector<Float, dimensions> const & v) const
		{
			return v+minVertex() ;
		}

		//@}
	};

}

#endif