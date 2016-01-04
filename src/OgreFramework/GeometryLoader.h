#ifndef _OgreFramework_GeometryLoader_H
#define _OgreFramework_GeometryLoader_H

#include <Ogre/DotSceneLoader.h>
#include <OGRE/OgreSceneManager.h>
#include <OGRE/OgreEntity.h>
#include <Config/Real.h>
#include <Ext/std/string_utils.h>
#include <string>

namespace OgreFramework
{
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \class	GeometryLoader
	///
	/// \brief	Class handling geometry loading for Ogre 3D. Currently, this class loads .mesh and .scene
	/// 		formats.
	///
	/// \author	Fabrice Lamarche, University of Rennes 1
	/// \date	19/12/2011
	////////////////////////////////////////////////////////////////////////////////////////////////////
	class GeometryLoader
	{
	protected:
		///< The current scene manager
		Ogre::SceneManager * m_sceneManager ;
		///< The scene loader
		Ogre::DotSceneLoader * m_sceneLoader ;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Ogre::SceneNode * GeometryLoader::getRootSceneNode()
		///
		/// \brief	Gets the root scene node.
		///
		/// \author	Fabrice Lamarche, University of Rennes 1
		/// \date	03/12/2011
		///
		/// \return	null if it fails, else the root scene node.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Ogre::SceneNode * getRootSceneNode();

	public:
		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	GeometryLoader::GeometryLoader(Ogre::SceneManager * sceneManager)
		///
		/// \brief	Constructor.
		///
		/// \author	Fabrice Lamarche, University of Rennes 1
		/// \date	03/12/2011
		///
		/// \param sceneManager	The associated scene manager.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		GeometryLoader(Ogre::SceneManager * sceneManager);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	GeometryLoader::~GeometryLoader()
		///
		/// \brief	Destructor.
		///
		/// \author	Fabrice Lamarche, University of Rennes 1
		/// \date	03/12/2011
		////////////////////////////////////////////////////////////////////////////////////////////////////
		~GeometryLoader();

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Ogre::SceneNode * GeometryLoader::loadMesh(const ::std::string & fileName,
		/// 	bool yUp = true)
		///
		/// \brief	Loads a mesh file.
		///
		/// \author	Fabrice Lamarche, University of Rennes 1
		/// \date	03/12/2011
		///
		/// \param	fileName	Filename of the file.
		/// \param  scaleFactor Scale factor appiled to this geometry
		/// \param	yUp			Is the object y up?.
		///
		/// \return	A pointer to the root scene node that have been inserted in the scene graph.
		/// 		You can modify all transformations associated to this node.
		/// 		The object is assumed to be Z up once loaded and inserted into the scene graph.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Ogre::SceneNode * loadMesh(const ::std::string & fileName, Config::Real scaleFactor=1.0, bool yUp = true);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Ogre::SceneNode * GeometryLoader::loadScene(const ::std::string & fileName,
		/// 	bool yUp = true)
		///
		/// \brief	Loads a scene file.
		///
		/// \author	Fabrice Lamarche, University of Rennes 1
		/// \date	03/12/2011
		///
		/// \param	fileName	Filename of the file.
		/// \param  scaleFactor Scale factor appiled to this geometry
		/// \param	yUp			Is the object y up?.
		///
		/// \return	A pointer to the root scene node that have been inserted in the scene graph.
		/// 		You can modify all transformations associated to this node.
		/// 		The object is assumed to be Z up once loaded and inserted into the scene graph.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Ogre::SceneNode * loadScene(const ::std::string & fileName, Config::Real scaleFactor=1.0, bool yUp = true);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Ogre::SceneNode * GeometryLoader::load(const ::std::string & fileName,
		/// 	bool yUp = true)
		///
		/// \brief	Loads a graphics file, either a ".mesh" or a ".scene" file.
		///
		/// \author	Fabrice Lamarche, University of Rennes 1
		/// \date	03/12/2011
		///
		/// \param	fileName	Filename of the file.
		/// \param  scaleFactor Scale factor appiled to this geometry
		/// \param	yUp			Is the object y up?.
		///
		/// \return	A pointer to the root scene node that have been inserted in the scene graph.
		/// 		You can modify all transformations associated to this node.
		/// 		The object is assumed to be Z up once loaded and inserted into the scene graph.
		/// 		In case of error, a NULL pointer is returned.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Ogre::SceneNode * load(const ::std::string & fileName, Config::Real scaleFactor=1.0, bool yUp = true);
	};
}

#endif