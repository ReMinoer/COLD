#ifndef _DataStructure_Grid_H
#define _DataStructure_Grid_H

#include <Config/Real.h>
#include <Math/Interval.h>
#include <Math/Vector2.h>
#include <vector>

namespace DataStructure
{
	///////////////////////////////////////////////////////////////////////////////////
	/// \brief Grid container
	/// 	   
	/// \param Data Type of data stored in the grid cells.
	/// 			
	/// \author F. Lamarche, University of Rennes 1.
	/////////////////////////////////////////////////////////////////////////////////// 
	template <class Data>
	class Grid
	{
	protected:
		Math::Interval<Config::Real> m_xInterval ;
		Math::Interval<Config::Real> m_yInterval ;
		/// Size of a grid cell
		Config::Real m_precision ;
		/// Inverse for the grid cell's size
		Config::Real m_inversePrecision ;
		::std::vector<Data> m_grid ;
		/// Grid size on X axis
		int m_xSize ;
		/// Grid size on Y axis
		int m_ySize ;
		/// Absolute coordinates of the bottom left corner of the grid
		Math::Vector2<Config::Real> m_buttomLeftCorner ;

		///////////////////////////////////////////////////////////////////////////////////
		/// \brief Computes the index of the grid cell at coordinates v
		/// 
		/// \param v The coordinates of the grid cell
		/// \return The index of the grid's cell
		/// 
		/// \author F. Lamarche, University of Rennes 1.
		///////////////////////////////////////////////////////////////////////////////////
		int toGridIndex( Math::Vector2<int> const & v ) const
		{
			return v[0]*m_ySize+v[1] ;
		}

		///////////////////////////////////////////////////////////////////////////////////
		/// \brief Converts a grid index into grid coordinates
		/// 
		/// \param gridIndex
		/// \return 
		/// 
		/// \author F. Lamarche, University of Rennes 1.
		///////////////////////////////////////////////////////////////////////////////////
		Math::Vector2<int> toGridCoordinates(int gridIndex) const
		{
			return Math::Vector2<int>(gridIndex/m_ySize, gridIndex%m_ySize) ;
		}

		///////////////////////////////////////////////////////////////////////////////////
		/// \brief Converts absolute coordinates into grid index
		/// 
		/// \param v
		/// \return 
		/// 
		/// \author F. Lamarche, University of Rennes 1.
		///////////////////////////////////////////////////////////////////////////////////
		int toGridIndex(Math::Vector2<Config::Real> const & v) const
		{
			return toGridIndex(toGridCoordinates(v)) ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	void Grid::validate(Math::Vector2<int> const & v)
		///
		/// \brief	Validates coordinates of a grid cell. This validation is assertion based and thus only
		/// 		present for debug purpose.
		///
		/// \author	Fabrice Lamarche, University of Rennes 1
		/// \date	23/11/2011
		///
		/// \param	v	The v.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void validate(Math::Vector2<int> const & v) const
		{
			assert(v[0]>=0 && v[0]<m_xSize) ;
			assert(v[1]>=0 && v[1]<m_ySize) ;
		}

	public:
		///////////////////////////////////////////////////////////////////////////////////
		/// \brief Initializes a new grid.  
		/// 
		/// \param xInterval x spatial extent of the grid
		/// \param yInterval y spatial extent of the grid
		/// \param precision precision of the grid (border length of each square)
		/// 
		/// \author F. Lamarche, University of Rennes 1.
		///////////////////////////////////////////////////////////////////////////////////
		Grid(Math::Interval<Config::Real> const & xInterval, Math::Interval<Config::Real> const & yInterval, Config::Real precision)
			: m_xInterval(xInterval), m_yInterval(yInterval)
		{
			m_precision = precision ;
			m_inversePrecision = Config::Real(1.0) / precision ;
			m_buttomLeftCorner = Math::Vector2<Config::Real>(xInterval.inf(), yInterval.inf()) ;
			m_xSize = int(xInterval.delta()/precision) ;
			m_ySize = int(yInterval.delta()/precision) ;
			m_grid.resize(m_xSize*m_ySize) ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Grid::Grid(const Grid & grid)
		///
		/// \brief	Copy constructor.
		///
		/// \author	Fabrice Lamarche, university of Rennes 1
		/// \param	grid	The grid.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Grid(const Grid & grid)
			: m_xInterval(grid.m_xInterval), m_yInterval(grid.m_yInterval), m_precision(grid.m_precision), m_inversePrecision(grid.m_inversePrecision), m_grid(grid.m_grid), 
			m_xSize(grid.m_xSize), m_ySize(grid.m_ySize), m_buttomLeftCorner(grid.m_buttomLeftCorner)
		{}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	bool Grid::isValid(Math::Vector2<Config::Real> const & v) const
		///
		/// \brief	Query if 'v' contains coordinates of a valid cell.
		///
		/// \author	Fabrice Lamarche, University of Rennes 1
		/// \date	23/11/2011
		///
		/// \param	v	The vector to validate.
		///
		/// \return	true if valid, false if not.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		bool isValid(Math::Vector2<int> const & v) const
		{
			return v[0]>=0 && v[0]<m_xSize && v[1]>=0 && v[1]<m_ySize ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	bool Grid::isValid(Math::Vector<Config::Real> const & v) const
		///
		/// \brief	Query if 'v' is inside the grid.
		///
		/// \author	Fabrice Lamarche, University of Rennes 1
		/// \date	23/11/2011
		///
		/// \param	v	The coordinates.
		///
		/// \return	true if inside the grid, false if not.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		bool isValid(Math::Vector2<Config::Real> const & v) const
		{
			return isValid(toGridCoordinates(v)) ;
		}

		///////////////////////////////////////////////////////////////////////////////////
		/// \brief Computes grid coordinates vector from a world coordinate vector
		/// 
		/// \param v The world coordinate vector
		/// \return The coordinates of the grid cell containing v
		/// 
		/// \author F. Lamarche, University of Rennes 1.
		///////////////////////////////////////////////////////////////////////////////////
		Math::Vector2<int> toGridCoordinates(Math::Vector2<Config::Real> const & v) const
		{
			Math::Vector2<int> result(int((v[0]-m_buttomLeftCorner[0])*m_inversePrecision), int((v[1]-m_buttomLeftCorner[1])*m_inversePrecision)) ;
			//result[0] = ::std::max(::std::min(result[0],m_xSize-1),0) ;
			//result[1] = ::std::max(::std::min(result[1],m_ySize-1),0) ;
			return result ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Math::Vector2<Config::Real> Grid::toWorldCoordinates(Math::Vector2<int> const & v) const
		///
		/// \brief	Converts a grid coordinates into world coordinates. The returned coordinates are located 
		/// 		at the center of the grid cell
		///
		/// \author	Fabrice Lamarche, University of Rennes 1
		/// \date	23/11/2011
		///
		/// \param	v	The grid coordinates.
		///
		/// \return	The coordinate of the center of the cell located at coordinates v
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Math::Vector2<Config::Real> toWorldCoordinates(Math::Vector2<int> const & v) const
		{
			validate(v) ;
			Math::Vector2<Config::Real> result = Math::Vector2<Config::Real>(Config::Real(v[0]), Config::Real(v[1])) ;
			return result*m_precision+m_buttomLeftCorner+Math::Vector2<Config::Real>(m_precision*Config::Real(0.5), m_precision*Config::Real(0.5)) ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	int Grid::xSize() const
		///
		/// \brief	Gets the X size of the grid.
		///
		/// \author	Fabrice Lamarche, University of Rennes 1
		/// \date	23/11/2011
		///
		/// \return	.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		int xSize() const
		{
			return m_xSize ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	int Grid::ySize() const
		///
		/// \brief	Gets the Y size of the grid.
		///
		/// \author	Fabrice Lamarche, University of Rennes 1
		/// \date	23/11/2011
		///
		/// \return	.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		int ySize() const
		{
			return m_ySize ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	const Data & Grid::operator[] (Math::Vector2<int> const & v) const
		///
		/// \brief	Array indexer operator return the value contained by the grid cell.
		///
		/// \author	Fabrice Lamarche, University of Rennes 1
		/// \date	23/11/2011
		///
		/// \param	v	The grid cell coordinates.
		///
		/// \return	The value contained by the cell.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		const Data & operator[] (Math::Vector2<int> const & v) const
		{
			validate(v) ;
			return m_grid[toGridIndex(v)] ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Data & Grid::operator[] (Math::Vector2<int> const & v))
		///
		/// \brief	Array indexer operator return the value contained by the grid cell.
		///
		/// \author	Fabrice Lamarche, University of Rennes 1
		/// \date	23/11/2011
		///
		/// \param	v	The grid cell coordinates.
		/// 			
		/// \return	The value contained by the cell.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Data & operator[] (Math::Vector2<int> const & v)
		{
			validate(v) ;
			return m_grid[toGridIndex(v)] ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	template <class CellType> Grid<CellType> Grid::duplicateStructure()
		///
		/// \brief	Creates a new grid with cells of type CellType with this grid structure (same intervals,
		/// 		precision...).
		///
		/// \author	Fabrice Lamarche, university of Rennes 1
		/// \tparam	CellType	Type of the cell type.
		///
		/// \return	The created grid.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		template <class CellType>
		Grid<CellType> duplicateStructure()
		{
			return Grid<CellType>(m_xInterval, m_yInterval, m_precision) ;
		}
	};
}

#endif