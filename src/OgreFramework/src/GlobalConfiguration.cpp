#include <stdafx.h>
#include <OgreFramework/GlobalConfiguration.h>

namespace OgreFramework
{
	Ogre::SceneManager * GlobalConfiguration::s_sceneManager = NULL ;
	OgreFramework::GeometryLoader * GlobalConfiguration::s_geometryLoader = NULL ;
	GameElements::ConfigurationLoader * GlobalConfiguration::s_configurationLoader = NULL ;
	System::Controller * GlobalConfiguration::s_controller = NULL ;
	GameElements::Map * GlobalConfiguration::s_currentMap = NULL ;
	FMOD::System * GlobalConfiguration::s_system = NULL ;
	::std::map<::std::string, FMOD::Sound*> GlobalConfiguration::s_sounds ;
	OgreBites::SdkTrayManager* GlobalConfiguration::s_trayManager = NULL ;

	static void checkSoundInitError(FMOD_RESULT result)
	{
		if(result!=FMOD_OK)
		{
			::std::cout<<"Error initializing fmod..."<<::std::endl ;
			char c ;
			::std::cin>>c; 
		}
	}

	void GlobalConfiguration::playSound(::std::string const & fileName) 
	{
		// Search for a free channel
		for(int cpt=0 ; cpt<256 ; ++cpt)
		{
			FMOD::Channel * channel ; 
			s_system->getChannel(cpt, &channel) ;
			bool playing ;
			channel->isPlaying(&playing) ;
			if(!playing) { channel->stop() ; }
		}
		// Search for sound
		auto it = s_sounds.find(fileName) ;
		FMOD::Sound * sound ; 
		if(it!=s_sounds.end())
		{
			sound = it->second ;
		}
		else
		{
			FMOD_RESULT result = OgreFramework::GlobalConfiguration::getSoundSystem()->createSound(fileName.c_str(), FMOD_DEFAULT, 0, &sound) ;
			s_sounds.insert(::std::make_pair(fileName, sound)) ;
		}
		FMOD::Channel *channel ;
		OgreFramework::GlobalConfiguration::getSoundSystem()->playSound(FMOD_CHANNEL_FREE, sound, true, &channel) ;
		channel->setVolume(1.0) ;
		channel->setPaused(false) ;
	}


	bool GlobalConfiguration::initSound()
	{
		FMOD_RESULT result;
		unsigned int version;
		int numdrivers;
		FMOD_SPEAKERMODE speakermode;
		FMOD_CAPS caps;
		char name[256];
		/*
		Create a System object and initialize.
		*/
		result = FMOD::System_Create(&s_system);
		checkSoundInitError(result);
		result = s_system->getVersion(&version);
		checkSoundInitError(result);
		if (version < FMOD_VERSION)
		{
			printf("Error! You are using an old version of FMOD %08x. This program requires %08x\n",
				version, FMOD_VERSION);
			return 0;
		}
		result = s_system->getNumDrivers(&numdrivers);
		checkSoundInitError(result);
		if (numdrivers == 0)
		{
			result = s_system->setOutput(FMOD_OUTPUTTYPE_NOSOUND);
			checkSoundInitError(result);
		}
		else
		{
			result = s_system->getDriverCaps(0, &caps, 0, /*0, */&speakermode);
			checkSoundInitError(result);
			/*
			Set the user selected speaker mode.
			*/
			result = s_system->setSpeakerMode(speakermode);
			checkSoundInitError(result);
			if (caps & FMOD_CAPS_HARDWARE_EMULATED)
			{
				/*
				The user has the 'Acceleration' slider set to off! This is really bad
				for latency! You might want to warn the user about this.
				*/
				result = s_system->setDSPBufferSize(1024, 10);
				checkSoundInitError(result);
			}
			result = s_system->getDriverInfo(0, name, 256, 0);
			checkSoundInitError(result);
			if (strstr(name, "SigmaTel"))
			{
				/*
				Sigmatel sound devices crackle for some reason if the format is PCM 16bit.
				PCM floating point output seems to solve it.
				*/
				result = s_system->setSoftwareFormat(48000, FMOD_SOUND_FORMAT_PCMFLOAT, 0,0,
					FMOD_DSP_RESAMPLER_LINEAR);
				checkSoundInitError(result);
			}
		}

		result = s_system->init(100, FMOD_INIT_NORMAL, 0);
		if (result == FMOD_ERR_OUTPUT_CREATEBUFFER)
		{
			/*
			Ok, the speaker mode selected isn't supported by this soundcard. Switch it
			back to stereo...
			*/
			result = s_system->setSpeakerMode(FMOD_SPEAKERMODE_STEREO);
			checkSoundInitError(result);
			/*
			... and re-init.
			*/
			result = s_system->init(100, FMOD_INIT_NORMAL, 0);
		}
		s_system->setSoftwareChannels(256) ;
		checkSoundInitError(result);
		return true ;
		::std::cout<<"Initialized fmod"<<::std::endl ;
	}


	void GlobalConfiguration::setup(const ::std::string & configurationFile, Ogre::SceneManager * sceneManager, OgreBites::SdkTrayManager* trayManager) 
	{
		setSceneManager(sceneManager) ; // Setups the scene manager and the geometry loader
		loadConfiguration(configurationFile) ; // Loads application configuration file
		initSound() ;
		s_controller = new System::Controller ;
		s_trayManager = trayManager ;
	}

	void GlobalConfiguration::loadConfiguration(const ::std::string & configurationFile) 
	{
		s_configurationLoader = new GameElements::ConfigurationLoader(configurationFile, s_sceneManager) ;
	}

	void GlobalConfiguration::setSceneManager( Ogre::SceneManager * sceneManager )
	{
		s_sceneManager = sceneManager ;
		s_geometryLoader = new OgreFramework::GeometryLoader(s_sceneManager) ;
	}

	Ogre::SceneManager * GlobalConfiguration::getSceneManager()
	{
		return s_sceneManager ;
	}

	OgreFramework::GeometryLoader * GlobalConfiguration::getGeometryLoader()
	{
		return s_geometryLoader ;
	}

	System::Controller * GlobalConfiguration::getController()
	{
		return s_controller ;
	}

	GameElements::ConfigurationLoader * GlobalConfiguration::getConfigurationLoader()
	{
		return s_configurationLoader ;
	}

	GameElements::Map * GlobalConfiguration::getCurrentMap()
	{
		return s_currentMap ;
	}

	void GlobalConfiguration::setCurrentMap( std::string const & mapName )
	{
		// We hide the current map
		if(s_currentMap!=NULL) { s_currentMap->show(false) ; }
		// We set the new map
		s_currentMap = s_configurationLoader->getMap(mapName) ;
		if(s_currentMap!=NULL) { s_currentMap->show(true) ; }
	}

	FMOD::System * GlobalConfiguration::getSoundSystem()
	{
		return s_system ;
	}

	OgreBites::SdkTrayManager* GlobalConfiguration::getSdkTrayManager()
	{
		return s_trayManager ;
	}

}
