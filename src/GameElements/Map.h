#ifndef _GameElements_Map_H
#define _GameElements_Map_H

#include <DataStructure/Grid.h>
#include <Ogre/OgreImage.h>
#include <TinyXML/tinyxml.h>
#include <OgreFramework/GeometryLoader.h>
#include <DataStructure/Grid.h>
#include <Math/Vector3.h>

namespace GameElements
{
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \class	Map
	///
	/// \brief	A map used in the game. By default, the graphical representation of the map is hidden.
	/// 		To unhide the map, call the show method.
	///
	/// \author	Fabrice Lamarche, university of Rennes 1
	////////////////////////////////////////////////////////////////////////////////////////////////////
	class Map
	{
	public:

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \struct	GroundCellDescription
		///
		/// \brief	Description of a ground cell type.
		///
		/// \author	Fabrice Lamarche, university of Rennes 1
		////////////////////////////////////////////////////////////////////////////////////////////////////
		struct GroundCellDescription
		{
			/// \brief	The name of the ground cell type.
			::std::string m_name ;
			/// \brief	The speed reduction associated to this type of cell.
			Config::Real m_speedReduction ;
			/// \brief	The color code associated to this type of cell.
			Math::Vector3<Config::Real> m_colorCode ;

			////////////////////////////////////////////////////////////////////////////////////////////////////
			/// \fn	GroundCellDescription()
			///
			/// \brief	Default constructor. Initializes this cell as an obstacle.
			///
			/// \author	Fabrice Lamarche, university of Rennes 1
			////////////////////////////////////////////////////////////////////////////////////////////////////
			GroundCellDescription()
				: m_speedReduction(1.0)
			{}
		};

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \struct	GridCell
		///
		/// \brief	The grid cell type. It only contains the index of the ground cell type assoicated to the cell
		///
		/// \author	Fabrice Lamarche, university of Rennes 1
		////////////////////////////////////////////////////////////////////////////////////////////////////
		struct GridCell
		{
			/// \brief	The type of the cell i.e. an index in the ground cell type table
			int m_type ;

			////////////////////////////////////////////////////////////////////////////////////////////////////
			/// \fn	GridCell()
			///
			/// \brief	Default constructor.
			///
			/// \author	Fabrice Lamarche, university of Rennes 1
			////////////////////////////////////////////////////////////////////////////////////////////////////
			GridCell()
				: m_type(0)
			{}
		};

	protected:

		/// \brief	The ogre node of the graphics representation of the map.
		Ogre::SceneNode * m_node ;
		/// \brief	List of types of cells.
		::std::vector<GroundCellDescription> m_cellTypes ;
		/// \brief	The grid representing the environment.
		DataStructure::Grid<GridCell> * m_grid ;
		/// \brief	The name of the map.
		::std::string m_name ;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	int Map::getCellType( Ogre::Image &image, int x, int y )
		///
		/// \brief	Gets a cell type from the pixel of the given image.
		///
		/// \author	Fabrice Lamarche, university of Rennes 1
		/// \param [in,out]	image	The image.
		/// \param	x			 	The x coordinate of the pixel.
		/// \param	y			 	The y coordinate of the pixel.
		///
		/// \return	The cell type.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		int getCellType( Ogre::Image &image, int x, int y );

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	void Map::parseCellsTypes( TinyXML::TiXmlElement * mapDescription )
		///
		/// \brief	Parse cells types.
		///
		/// \author	Fabrice Lamarche, university of Rennes 1
		/// \param [in,out]	mapDescription	XML node describing the map.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void parseCellsTypes( TinyXML::TiXmlElement * mapDescription );

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	void Map::loadMap( ::std::string mapData )
		///
		/// \brief	Loads a map from a image file (jpg, tiff etc...)
		///
		/// \author	Fabrice Lamarche, university of Rennes 1
		/// \param	mapData	Information describing the map.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void loadMap( ::std::string mapData );

	public:

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Map::Map(Ogre::SceneManager * sceneManager, TinyXML::TiXmlElement * mapDescription)
		///
		/// \brief	Constructor.
		///
		/// \author	Fabrice Lamarche, university of Rennes 1
		/// \param [in,out]	sceneManager  	manager for scene, used to load map geometry.
		/// \param [in,out]	mapDescription	XML node describing the map.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Map(Ogre::SceneManager * sceneManager, TinyXML::TiXmlElement * mapDescription);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Map::Map(const Map & map) : m_node(map.m_node), m_cellTypes(map.m_cellTypes),
		/// 	m_grid(new DataStructure::Grid<GridCell>(*map.m_grid)), m_name(map.m_name)
		///
		/// \brief	Copy constructor.
		///
		/// \author	Fabrice Lamarche, university of Rennes 1
		/// \param	map	The map.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Map(const Map & map)
			: m_node(map.m_node), m_cellTypes(map.m_cellTypes), m_grid(new DataStructure::Grid<GridCell>(*map.m_grid)), m_name(map.m_name)
		{}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	int Map::width() const
		///
		/// \brief	Gets the width of the grid.
		///
		/// \author	Fabrice Lamarche, university of Rennes 1
		/// \return	.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		int width() const
		{
			return m_grid->xSize() ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	int Map::height() const
		///
		/// \brief	Gets the height of the grid.
		///
		/// \author	Fabrice Lamarche, university of Rennes 1
		/// \return	.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		int height() const
		{
			return m_grid->ySize() ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	const GroundCellDescription & Map::getCell(Math::Vector2<int> const & gridCoordinates) const
		///
		/// \brief	Gets a cell of the grid from grid coordinates.
		///
		/// \author	Fabrice Lamarche, university of Rennes 1
		/// \param	gridCoordinates	The grid coordinates.
		///
		/// \return	The cell.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		const GroundCellDescription & getCell(Math::Vector2<int> const & gridCoordinates) const
		{
			assert(m_grid->isValid(gridCoordinates)) ;
			return m_cellTypes[(*m_grid)[gridCoordinates].m_type] ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	const GroundCellDescription & Map::getCell(Math::Vector2<Config::Real> const & worldCoordinates) const
		///
		/// \brief	Gets a cell of the grid from world coordinates.
		///
		/// \author	Fabrice Lamarche, university of Rennes 1
		/// \param	worldCoordinates	The world coordinates.
		///
		/// \return	The cell.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		const GroundCellDescription & getCell(Math::Vector2<Config::Real> const & worldCoordinates) const
		{
			assert(m_grid->isValid(worldCoordinates)) ;
			return getCell(m_grid->toGridCoordinates(worldCoordinates)) ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	bool Map::isValid(Math::Vector2<int> const & gridCoordinates) const
		///
		/// \brief	Query if grid coordinates are valid.
		///
		/// \author	Fabrice Lamarche, university of Rennes 1
		/// \param	gridCoordinates	The grid coordinates.
		///
		/// \return	true if valid, false if not.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		bool isValid(Math::Vector2<int> const & gridCoordinates) const
		{
			return m_grid->isValid(gridCoordinates) ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	bool Map::isValid(Math::Vector2<Config::Real> const & worldCoordinates) const
		///
		/// \brief	Query if world coordinates are valid.
		///
		/// \author	Fabrice Lamarche, university of Rennes 1
		/// \param	worldCoordinates	The world coordinates.
		///
		/// \return	true if valid, false if not.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		bool isValid(Math::Vector2<Config::Real> const & worldCoordinates) const
		{
			return m_grid->isValid(worldCoordinates) ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Math::Vector2<int> Map::toGridCoordinates(Math::Vector2<Config::Real> const & worldCoordinates) const
		///
		/// \brief	Converts the world coordinates to grid coordinates.
		///
		/// \author	Fabrice Lamarche, university of Rennes 1
		/// \param	worldCoordinates	The world coordinates.
		///
		/// \return	worldCoordinates as a Math::Vector2&lt;int&gt;
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Math::Vector2<int> toGridCoordinates(Math::Vector2<Config::Real> const & worldCoordinates) const
		{
			return m_grid->toGridCoordinates(worldCoordinates) ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Math::Vector2<Config::Real> Map::toWorldCoordinates(Math::Vector2<int> const & gridCoordinates) const
		///
		/// \brief	Converts the grid coordinates to world coordinates.
		///
		/// \author	Fabrice Lamarche, university of Rennes 1
		/// \param	gridCoordinates	The grid coordinates.
		///
		/// \return	gridCoordinates as a Math::Vector2&lt;Config::Real&gt;
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Math::Vector2<Config::Real> toWorldCoordinates(Math::Vector2<int> const & gridCoordinates) const
		{
			return m_grid->toWorldCoordinates(gridCoordinates) ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	const ::std::string & Map::getName() const
		///
		/// \brief	Gets the name of the map.
		///
		/// \author	Fabrice Lamarche, university of Rennes 1
		/// \return	The name.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		const ::std::string & getName() const
		{
			return m_name ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	void Map::show(bool visible=true)
		///
		/// \brief	Shows / hide the graphical representation of the map.
		///
		/// \author	Fabrice Lamarche, university of Rennes 1
		/// \param	visible	(optional) the visible.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void show(bool visible=true) 
		{
			m_node->setVisible(visible) ;
		}

		Math::Vector2<int> findFreeLocation()
		{
			Math::Vector2<int> position ;
			do 
			{
				position[0] = rand()%width() ;
				position[1] = rand()%height() ;
			} while (getCell(position).m_speedReduction==1.0);
			return position ;
		}
	}; 
}

#endif