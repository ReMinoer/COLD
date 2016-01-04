#include <stdafx.h>
#include <GameElements/Map.h>
#include <Ext/TinyXML/Helpers.h>
#include <Ext/Ogre/ComputeBoundingBox.h>

int GameElements::Map::getCellType( Ogre::Image &image, int x, int y )
{
	Ogre::ColourValue color = image.getColourAt(x,y,0) ;
	Math::Vector3<Config::Real> ogreColor(color[0], color[1], color[2]) ;
	int nearest = 1 ; // We skip type 0 which is the default value for the map
	Config::Real distance = (ogreColor-m_cellTypes[0].m_colorCode).norm() ;
	for(int cpt=2 ; cpt<(int)m_cellTypes.size() ; ++cpt)
	{
		Config::Real tmpDist = (ogreColor-m_cellTypes[cpt].m_colorCode).norm() ;
		if(tmpDist<distance)
		{
			distance = tmpDist ;
			nearest = cpt ;
		}
	}
	return nearest ;
}

void GameElements::Map::parseCellsTypes( TinyXML::TiXmlElement * mapDescription )
{
	GroundCellDescription description ;
	description.m_name = "default" ;
	description.m_speedReduction = 1.0 ;
	m_cellTypes.push_back(description) ;
	for(TinyXML::TiXmlElement * element = mapDescription->FirstChildElement("ground") ; element!=NULL ; element=element->NextSiblingElement("ground"))
	{
		GroundCellDescription description ;
		description.m_name = Ext::TinyXML::getAttribute(element, "name") ; // element->Attribute("name") ;
		description.m_speedReduction = (Config::Real)atof(Ext::TinyXML::getAttribute(element, "speedReduction")) ; //element->Attribute("speedReduction")) ;
		Config::Real red = (Config::Real)atof(Ext::TinyXML::getAttribute(element, "red"))/255.0f ;
		Config::Real green = (Config::Real)atof(Ext::TinyXML::getAttribute(element, "green"))/255.0f ;
		Config::Real blue = (Config::Real)atof(Ext::TinyXML::getAttribute(element, "blue"))/255.0f ;
		description.m_colorCode = Math::Vector3<Config::Real>(red, green, blue) ;
		m_cellTypes.push_back(description) ;
	}
}

GameElements::Map::Map( Ogre::SceneManager * sceneManager, TinyXML::TiXmlElement * mapDescription )
{
	// Extracts map attributes
	m_name = Ext::TinyXML::getAttribute(mapDescription, "name") ;
	::std::string mesh = Ext::TinyXML::getAttribute(mapDescription, "mesh") ; 
	::std::string mapData = Ext::TinyXML::getAttribute(mapDescription, "mapData") ; 
	Config::Real scale = atof(Ext::TinyXML::getAttribute(mapDescription, "scale")) ; 
	// Extracts cell descriptions		
	parseCellsTypes(mapDescription);
	// Loads the map geometry
	OgreFramework::GeometryLoader loader(sceneManager) ;
	m_node = loader.load(mesh,scale) ;
	// Loads the image of the map
	loadMap(mapData);
	// Hides the map geometry after loading
	show(false) ;
}

void GameElements::Map::loadMap( ::std::string mapData )
{
	// Computes the bounding box of the map geometry and initializes map bounds
	::Ogre::AxisAlignedBox boundingBox = ::Ext::Ogre::computeBoundingBox(m_node) ;
	Math::Interval<Config::Real> xInterval(boundingBox.getMinimum()[0], boundingBox.getMaximum()[0]) ;
	Math::Interval<Config::Real> yInterval(boundingBox.getMinimum()[1], boundingBox.getMaximum()[1]) ;
	// Loads the map grid
	Ogre::Image image ;
	image.load(mapData, Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME) ;
	image.flipAroundX() ;
	//image.flipAroundY() ;
	// Fills the grid by analyzing the loaded image
	Config::Real xRatio = xInterval.delta()/image.getWidth() ;
	Config::Real yRatio = yInterval.delta()/image.getHeight() ;
	::std::cout<<xRatio<<" -- "<<yRatio<<::std::endl ;
	m_grid = new DataStructure::Grid<GridCell>(xInterval, yInterval, xRatio) ;
	//m_grid = new DataStructure::Grid<GridCell>(Math::Interval<Config::Real>(0, (Config::Real)image.getWidth()), Math::Interval<Config::Real>(0, (Config::Real)image.getHeight()), 1) ;
	for(int x=0 ; x<(int)image.getWidth() ; ++x) 
	{
		for(int y=0 ; y<(int)image.getHeight() ; ++y)
		{
			// Search for the type of the grid cell 
			int cellType = getCellType(image, x, y);
			// Fills the grid cell
			GridCell cell ;
			cell.m_type = cellType ;
			(*m_grid)[Math::Vector2<int>(x,y)] = cell ;
		}
	}
}