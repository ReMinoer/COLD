#ifndef _OgreFramework_GlobalConfiguration_H
#define _OgreFramework_GlobalConfiguration_H

#include <Ogre/OgreSceneManager.h>
#include <OgreFramework/GeometryLoader.h>
#include <GameElements/ConfigurationLoader.h>
#include <System/Controller.h>
#include <fmod.h>

namespace OgreFramework
{
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \class	GlobalConfiguration
	///
	/// \brief	Global configuration static class. This class contains several methods that give access
	/// 		to main components of the application.
	///
	/// \author	Fabrice Lamarche, university of Rennes 1
	////////////////////////////////////////////////////////////////////////////////////////////////////
	class GlobalConfiguration
	{
	protected:
		/// \brief	The Ogre 3D scene manager.
		static Ogre::SceneManager * s_sceneManager ;
		/// \brief	The geometry loader (handles .scene and .mesh loading).
		static OgreFramework::GeometryLoader * s_geometryLoader ;
		/// \brief	The configuration loader.
		static GameElements::ConfigurationLoader * s_configurationLoader ;
		/// \brief	The controller.
		static System::Controller * s_controller ;
		/// \brief	The current map.
		static GameElements::Map * s_currentMap ;
		/// \brief	The sound system.
		static FMOD::System * s_system;
		/// \brief	The loaded sounds.
		static ::std::map<::std::string, FMOD::Sound*> s_sounds ;
		/// \brief	The tray manager (Ogre GUI).
		static OgreBites::SdkTrayManager* s_trayManager;

		static void setSceneManager(Ogre::SceneManager * sceneManager);
		static void loadConfiguration(const ::std::string & configurationFile) ;
		static bool initSound() ;
	public:

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	static void GlobalConfiguration::setup(const ::std::string & configurationFile,
		/// 	Ogre::SceneManager * sceneManager);
		///
		/// \brief	Setups the global configuration.
		///
		/// \author	Fabrice Lamarche, university of Rennes 1
		/// \param	configurationFile   	The configuration file.
		/// \param [in,out]	sceneManager	The Ogre 3D scene manager.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		static void setup(const ::std::string & configurationFile, Ogre::SceneManager * sceneManager, OgreBites::SdkTrayManager* trayManager) ;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	static OgreBites::SdkTrayManager* GlobalConfiguration::getSdkTrayManager()
		///
		/// \brief	Gets sdk tray manager.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	28/11/2014
		///
		/// \return	null if it fails, else the sdk tray manager.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		static OgreBites::SdkTrayManager* getSdkTrayManager();

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	static Ogre::SceneManager * GlobalConfiguration::getSceneManager();
		///
		/// \brief	Gets the scene manager.
		///
		/// \author	Fabrice Lamarche, university of Rennes 1
		/// \return	null if it fails, else the scene manager.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		static Ogre::SceneManager * getSceneManager() ;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	static OgreFramework::GeometryLoader * GlobalConfiguration::getGeometryLoader();
		///
		/// \brief	Gets the geometry loader.
		///
		/// \author	Fabrice Lamarche, university of Rennes 1
		/// \return	The geometry loader.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		static OgreFramework::GeometryLoader * getGeometryLoader() ;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	static System::Controller * GlobalConfiguration::getController();
		///
		/// \brief	Gets the controller.
		///
		/// \author	Fabrice Lamarche, university of Rennes 1
		/// \return	The controller.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		static System::Controller * getController();

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	static GameElements::ConfigurationLoader * GlobalConfiguration::getConfigurationLoader();
		///
		/// \brief	Gets the configuration loader.
		///
		/// \author	Fabrice Lamarche, university of Rennes 1
		/// \return	The configuration loader.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		static GameElements::ConfigurationLoader * getConfigurationLoader();

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	static void GlobalConfiguration::setCurrentMap(std::string const & mapName);
		///
		/// \brief	Sets the current map.
		///
		/// \author	Fabrice Lamarche, university of Rennes 1
		/// \param	mapName	Name of the map.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		static void setCurrentMap(std::string const & mapName);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	static GameElements::Map * GlobalConfiguration::getCurrentMap();
		///
		/// \brief	Gets the current map.
		///
		/// \author	Fabrice Lamarche, university of Rennes 1
		/// \return	The current map.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		static GameElements::Map * getCurrentMap();

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	static FMOD::System * GlobalConfiguration::getSoundSystem();
		///
		/// \brief	Gets the sound system.
		///
		/// \author	Fabrice Lamarche, university of Rennes 1
		/// \return	The sound system.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		static FMOD::System * getSoundSystem();

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	static void GlobalConfiguration::playSound(::std::string const & fileName);
		///
		/// \brief	Plays a sound, based on its filename.
		///
		/// \author	Fabrice Lamarche, university of Rennes 1
		/// \param	fileName	Filename of the sound.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		static void playSound(::std::string const & fileName) ;
	};
}

#endif