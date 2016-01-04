#include <stdafx.h>

#include <Ogre/DotSceneLoader.h>
#include <OgreFramework/GeometryLoader.h>
#include <OGRE/OgreSceneManager.h>
#include <OGRE/OgreEntity.h>

namespace OgreFramework
{


	GeometryLoader::GeometryLoader( Ogre::SceneManager * sceneManager ) 
		: m_sceneManager(sceneManager), m_sceneLoader(new Ogre::DotSceneLoader)
	{

	}

	GeometryLoader::~GeometryLoader()
	{
		delete m_sceneLoader ;
	}
	Ogre::SceneNode * GeometryLoader::loadMesh( const ::std::string & fileName, Config::Real scaleFactor, bool yUp /*= true*/ )
	{
		Ogre::Entity * entity = m_sceneManager->createEntity(fileName) ;
		Ogre::SceneNode * objectRoot = getRootSceneNode()->createChildSceneNode() ;
		Ogre::SceneNode * objectRootSub = objectRoot->createChildSceneNode(Ogre::Vector3::ZERO, Ogre::Quaternion(yUp?Ogre::Radian(Ogre::Degree(90)):Ogre::Radian(0), Ogre::Vector3::UNIT_X)) ;
		Ogre::SceneNode * correctY = objectRootSub->createChildSceneNode() ;
		correctY->setScale(Ogre::Vector3(scaleFactor, scaleFactor, scaleFactor)) ;
		correctY->attachObject(entity) ;
		return objectRoot ;
	}

	Ogre::SceneNode * GeometryLoader::loadScene( const ::std::string & fileName, Config::Real scaleFactor, bool yUp /*= true*/ )
	{
		static int count=0 ;
		std::ostringstream oss ;
		oss<<"scene"<<count ;
		std::string prefix = oss.str(); 

		Ogre::SceneNode * objectRoot = getRootSceneNode()->createChildSceneNode() ;
		Ogre::SceneNode * objectRootSub = objectRoot ->createChildSceneNode(Ogre::Vector3::ZERO, Ogre::Quaternion(yUp?Ogre::Radian(Ogre::Degree(90)):Ogre::Radian(0), Ogre::Vector3::UNIT_X)) ;
		Ogre::SceneNode * correctY = objectRootSub->createChildSceneNode() ;
		correctY->setScale(Ogre::Vector3(scaleFactor, scaleFactor, scaleFactor)) ;
		m_sceneLoader->parseDotScene(fileName, Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, m_sceneManager, correctY, prefix);
		++count ;
		return objectRoot ;
	}

	Ogre::SceneNode * GeometryLoader::getRootSceneNode()
	{
		return m_sceneManager->getRootSceneNode() ;
	}

	Ogre::SceneNode * GeometryLoader::load( const ::std::string & fileName, Config::Real scaleFactor/*=1.0*/, bool yUp /*= true*/ )
	{
		if(Ext::std::endsWith(fileName, ".mesh")) { return loadMesh(fileName, scaleFactor, yUp) ; }
		if(Ext::std::endsWith(fileName, ".scene")) { return loadScene(fileName, scaleFactor, yUp) ; }
		return NULL ;
	}
}