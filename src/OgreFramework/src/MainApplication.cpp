#include <stdafx.h>

#include <OgreFramework/MainApplication.h>

#include <OGRE/OgreRay.h>
#include <OGRE/OgreSceneQuery.h>
#include <OgreFramework/EntityAdapter.h>
#include <Ogre/DotSceneLoader.h>
#include <OgreFramework/PickingSelectionBuffer.h>
#include <OgreFramework/PickingBoundingBox.h>
#include <OgreFramework/GeometryLoader.h>
#include <OgreFramework/GlobalConfiguration.h>
#include <GameElements/ConfigurationLoader.h>
#include <GameElements/NullAgent.h>
#include <GameElements/Bullet.h>
#include <GameElements/StraightBullet.h>
#include <GameElements/BallisticBullet.h>
#include <Ext/Ogre/ComputeBoundingBox.h>
#include <Triggers/BasicCollisionDetector.h>
#include <GameElements/RandomAgent.h>

#include <GameElements/AiAgent.h>
#include<GameElements\RTSPicking.h>
#include <GameElements\SelectionPanel.h>
namespace OgreFramework
{
	MainApplication::MainApplication()
		: m_keyboardState(*KeyboardState::getInstance())
		, m_moneyMax(2000)
		, m_enemyMoney(2000)
	{
		m_buyMenu = GameElements::BuyMenu(m_moneyMax);
		srand(time(NULL));
	}

	MainApplication::~MainApplication()
	{
	}

	void MainApplication::createScene(void)
	{
		// Application  global configuration
		GlobalConfiguration::setup("../data/xml/hot_config.xml", m_sceneManager, m_trayManager) ;

		// Creates the instance of collision detector
		new Triggers::SweepAndPrune ;
		//new Triggers::BasicCollisionDetector ;
		
		GlobalConfiguration::setCurrentMap("map01") ;

		// create your scene here :)
		::std::cout<<"Creating scene..."<<::std::flush ;
	
		// 0- Sets the camera style
		//m_cameraManager->setStyle(OgreBites::CS_ORBIT) ; //OgreBites::CS_MANUAL) ;

		// 1- Sets the shadows (shadow volumes)
		// ------------------------------------
		m_sceneManager->setShadowTechnique(Ogre::SHADOWTYPE_NONE) ; // No shadows
		//m_sceneManager->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_MODULATIVE) ; ////Ogre::SHADOWTYPE_STENCIL_ADDITIVE) ;//
		//////m_sceneManager->setShadowDirectionalLightExtrusionDistance(10000000) ;
		//m_sceneManager->setShadowIndexBufferSize(500000) ;
		//m_sceneManager->setShadowColour(::Ogre::ColourValue(.3,.3,.3)) ;
		//////m_sceneManager->setShowDebugShadows(true) ;

		m_camera->setFarClipDistance(Ogre::Real(3000)) ;
		m_camera->setNearClipDistance(Ogre::Real(0.01)) ;
		// 2- Sets fog
		// -----------
		m_sceneManager->setFog(Ogre::FOG_LINEAR, Ogre::ColourValue(Ogre::Real(0.0), Ogre::Real(0.0), Ogre::Real(0.0)), Ogre::Real(0.03), Ogre::Real(2000.0), Ogre::Real(3000.0)) ;

		// 3- Adds lights
		Ogre::Light * light = m_sceneManager->createLight("light1siga") ;
		light->setType(Ogre::Light::LT_DIRECTIONAL) ;
		Ogre::Vector3 direction(-10.0, -10.0, -1.0) ;
		direction.normalise() ;
		light->setDirection(direction) ;
		light->setDiffuseColour(0.5,0.5,0.5) ;
		light->setSpecularColour(0.5, 0.5, 0.5) ;
		m_sceneManager->setAmbientLight(::Ogre::ColourValue(0.5,0.5,0.5)) ;
		m_sceneManager->getRootSceneNode()->attachObject(light) ;

		
		// Gets the root scene node
		Ogre::SceneNode * rootSceneNode = getRootSceneNode() ;
		
		// --------------------------------------
		// Setups the GUI 
		// --------------------------------------

		{
			m_buyMenu.ShowSelectionMenu(m_trayManager) ;
		}
		panel = new GameElements::SelectionPanel(m_trayManager) ;
		
		// Setups the picking
		//m_picking = new PickingBoundingBox(m_sceneManager, m_camera, OIS::MB_Left) ;
		//m_picking = new PickingSelectionBuffer(m_window, m_sceneManager, m_camera, OIS::MB_Left) ;
		m_picking = new GameElements::RTSPicking(m_window, m_sceneManager, m_camera, OIS::MB_Left, OIS::MB_Right, GameElements::AiAgent::getAIMessageEmitter(), GameElements::AiAgent::getAIMessageEmitterUnSelect(), panel) ;

		// Setups the camera control system
		m_cameraManager = new RTSCameraManager(m_sceneManager, m_camera, &m_keyboardState) ;
		
		//camera animation
		Ogre::Real time = 10;
		Ogre::Animation * m_anim = m_sceneManager->createAnimation("animation",time);
		m_anim->setInterpolationMode(Ogre::Animation::IM_SPLINE);
		Ogre::NodeAnimationTrack * trak = m_anim->createNodeTrack(0,m_camera->getParentNode());
		trak->createNodeKeyFrame(0)->setTranslate( Ogre::Vector3(0,0,70) );
		trak->createNodeKeyFrame(time/5)->setTranslate( Ogre::Vector3(-10,-10,70) );
		trak->createNodeKeyFrame(2*time/5)->setTranslate( Ogre::Vector3(10,-10,70) );
		trak->createNodeKeyFrame(3*time/5)->setTranslate( Ogre::Vector3(10,10,70) );
		trak->createNodeKeyFrame(4*time/5)->setTranslate( Ogre::Vector3(-10,10,70) );
		trak->createNodeKeyFrame(time)->setTranslate( Ogre::Vector3(0,0,70) );
		
		mCamAnimState = m_sceneManager->createAnimationState("animation");
		mCamAnimState ->setEnabled(true);
		mCamAnimState ->setLoop(false);

		// ----------------------------------------
		// Creates two entities for testing purpose
		// ----------------------------------------

		/*
		for(int cpt=0 ; cpt<50 ; ++cpt)
		{
			const GameElements::UnitsArchetypes::Archetype * unit = GlobalConfiguration::getConfigurationLoader()->getUnitsArchetypes().get(types[rand()%types.size()]) ;
			const GameElements::WeaponsArchetypes::Archetype * weapon = GlobalConfiguration::getConfigurationLoader()->getWeaponsArchetypes().get(unit->m_weapon) ;
			if(weapon==NULL) { ::std::cout<<"HippoB: bad weapon!" ; char c ; ::std::cin>>c ; }
			GameElements::AiAgent::Pointer m_entityAdapter = new GameElements::AiAgent(unit, weapon, GlobalConfiguration::getCurrentMap()) ;
			//GameElements::RandomAgent::Pointer m_entityAdapter = new GameElements::RandomAgent(unit, weapon) ;
			Vector2<Config::Real> position = GlobalConfiguration::getCurrentMap()->toWorldCoordinates(GlobalConfiguration::getCurrentMap()->findFreeLocation());
			m_entityAdapter->setPosition(position.push(0.0)) ;
			m_entityAdapter->setDestination(Vector2<Config::Real>(-position[0], -position[1]));
		}
		*/
		//m_entityAdapter = new GameElements::NullAgent(configurationLoader.getUnitsArchetypes().get("HippoB"), configurationLoader.getWeaponsArchetypes().get()) ;

		// Test pour vérifier la correspondance carte <-> représentation graphique
		//for(int x=0 ; x<GlobalConfiguration::getCurrentMap()->width() ; x+=10)
		//	for(int y=0 ; y<GlobalConfiguration::getCurrentMap()->height() ; y+=10)
		//	{
		//		if(GlobalConfiguration::getCurrentMap()->getCell(Math::Vector2<int>(x,y)).m_speedReduction!=1.0)
		//		{
		//			unit = GlobalConfiguration::getConfigurationLoader()->getUnitsArchetypes().get("CrocoB") ;
		//			weapon = GlobalConfiguration::getConfigurationLoader()->getWeaponsArchetypes().get(unit->m_weapon) ;
		//			if(weapon==NULL) { ::std::cout<<"CrocoB: bad weapon!" ; char c ; ::std::cin>>c ; }
		//			GameElements::NullAgent::Pointer ptr = new GameElements::NullAgent(unit, weapon) ; // HippoB, CrocoB, MousticB
		//			ptr->setOrientation(0.0,0.0,Math::piDiv4) ;
		//			ptr->setPosition(GlobalConfiguration::getCurrentMap()->toWorldCoordinates(Math::Vector2<int>(x,y)).push(0.0)) ;
		//		}
		//	}
	}

	void MainApplication::update(Ogre::Real dt)
	{
		// Necessary for GUI...
		m_trayManager->adjustTrays() ;
		//dt = ::std::min(dt,0.01f) ;
		static double time = 0 ;
		time += dt ;
		//if(time>4)
		//{
		//	for(float cpt=-3 ; cpt<3 ; cpt+=0.6)
		//	{
		//		//new GameElements::Bullet(GlobalConfiguration::getGeometryLoader()->load("JetEngine.scene"), 2, 0, Math::Vector2<Config::Real>(-6,cpt), Math::Vector2<Config::Real>(0.5+double(rand())/RAND_MAX,0), 12) ;
		//		//new GameElements::Bullet(GlobalConfiguration::getGeometryLoader()->load("JetEngine.scene"), 2, 0, Math::Vector2<Config::Real>(6,cpt), Math::Vector2<Config::Real>(-0.5-+double(rand())/RAND_MAX,0), 12) ;
		//		new GameElements::StraightBullet(GlobalConfiguration::getGeometryLoader()->load("JetEngine.scene"), 2, 0, Math::Vector2<Config::Real>(-6,cpt), Math::Vector2<Config::Real>(0.5+double(rand())/RAND_MAX,0), 12) ;
		//		//new GameElements::StraightBullet(GlobalConfiguration::getGeometryLoader()->load("JetEngine.scene"), 2, 0, Math::Vector2<Config::Real>(6,cpt), Math::Vector2<Config::Real>(-0.5-+double(rand())/RAND_MAX,0), 12) ;
		//		//new GameElements::BallisticBullet(GlobalConfiguration::getGeometryLoader()->load("JetEngine.scene"), 2, 0, Math::Vector2<Config::Real>(-6,cpt), 2+double(rand())/RAND_MAX, Math::Vector2<Config::Real>(4-8*double(rand())/RAND_MAX,4-8*double(rand())/RAND_MAX), 2) ;
		//		new GameElements::BallisticBullet(GlobalConfiguration::getGeometryLoader()->load("JetEngine.scene"), 2, 0, Math::Vector2<Config::Real>(6,cpt), 2+double(rand())/RAND_MAX, Math::Vector2<Config::Real>(4-8*double(rand())/RAND_MAX,4-8*double(rand())/RAND_MAX), 2) ;
		//	}
		//	//new GameElements::Bullet(GlobalConfiguration::getGeometryLoader()->load("JetEngine.scene"), 20, 0, Math::Vector2<Config::Real>(-2,1)*3.0, Math::Vector2<Config::Real>(0.5,0), 4*3.0) ;
		//	//new GameElements::Bullet(GlobalConfiguration::getGeometryLoader()->load("JetEngine.scene"), 20, 0, Math::Vector2<Config::Real>(-2,0)*3.0, Math::Vector2<Config::Real>(0.5,0), 4*3.0) ;
		//	//new GameElements::Bullet(GlobalConfiguration::getGeometryLoader()->load("JetEngine.scene"), 20, 0, Math::Vector2<Config::Real>(2,0)*3.0, Math::Vector2<Config::Real>(-0.5,0), 4*3.0) ;
		//	time = 0 ;
		//}

		//m_trayManager->showAll();
		
		//Ogre::AxisAlignedBox box = Ext::Ogre::computeBoundingBox(m_shipShape) ;
		//::std::cout<<box.getMinimum()<<" / "<<box.getMaximum()<<::std::endl ;

		static Ogre::Real absoluteTime  = 0.0 ;

		absoluteTime += dt ;
		//m_entityAdapter->setPosition(Math::Vector3<Config::Real>((int(absoluteTime*1000)%10000)/2000.0, (int(absoluteTime*1000)%10000)/2000.0, 0.0)) ;
		//m_entityAdapter->setOrientation(0.0,0.0,absoluteTime) ;

		mCamAnimState->addTime(dt);
		if(mCamAnimState->hasEnded())
		{
			mCamAnimState->setEnabled(false);
			m_camera->setPosition(0,0,70);
		}
		// Updates camera manager
		m_cameraManager->update(dt) ;
		// Updates (animation, behavoir & son on) are called here :)
		GlobalConfiguration::getController()->update(dt) ;
		panel->update();
		//static bool explosionFired = false ;
		//if(absoluteTime>10.0 && !explosionFired)
		//{
		//	explosionFired = true ;
		//	// Trying explosion
		//	// create a particle system named explosions using the explosionTemplate
		//	Ogre::ParticleSystem* particleSystem = m_sceneManager->createParticleSystem("explosions2", "explosionTemplate");
		//	particleSystem->setParameter("particle_width", "1") ;
		//	particleSystem->setParameter("particle_height", "1") ;
		//	// fast forward 1 second  to the point where the particle has been emitted
		//	particleSystem->fastForward(1.0);
		//	// attach the particle system to a scene node
		//	getRootSceneNode()->attachObject(particleSystem);
		//}
	}

	bool MainApplication::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
	{
		bool result = BaseApplication::mousePressed(arg, id) ;
		m_picking->update(arg, id) ;
		return result ;
	}

	void MainApplication::itemSelected(OgreBites::SelectMenu* menu)
	{
	}

	void MainApplication::buttonHit(OgreBites::Button* button)
	{
		int SelectionIndex = 0;

		::std::vector<::std::string> types ;
		types.push_back("MousticB") ;
		types.push_back("CrocoB") ;
		types.push_back("HippoB") ;

		if (button->getName() == "MousticButton")
			SelectionIndex = 1 ;
		else if (button->getName() == "CrocoButton" )
			SelectionIndex = 2 ;
	    else if (button->getName() == "HippoButton" )
			SelectionIndex = 3 ;

		if (SelectionIndex > 0)
		{
			const GameElements::UnitsArchetypes::Archetype * unit = GlobalConfiguration::getConfigurationLoader()->getUnitsArchetypes().get(types[SelectionIndex - 1]) ;
			m_buyMenu.BuyVehicle(unit) ;
		}
		else // If press button is "Close Menu"
		{
			m_buyMenu.HideSelectionMenu(m_trayManager);
			m_ourVehicleList = m_buyMenu.GetVehicleList();
			vehicleGeneration(m_ourVehicleList);
		}
	}

	bool MainApplication::keyPressed( const OIS::KeyEvent &arg )
	{
		// Keeps the keyboard state up to date
		m_keyboardState.notifyKeyPressed(arg.key) ;
		// Sends notification to super class
		BaseApplication::keyPressed(arg) ;
		if (arg.key == OIS::KC_SPACE)   //lance animation
		{
			mCamAnimState->setEnabled(!mCamAnimState->getEnabled());
			if(mCamAnimState->getEnabled())
			{
				m_camera->setPosition(Ogre::Vector3(0,0,0));
				mCamAnimState->setTimePosition(0);
			}
			else
			{
				m_camera->setPosition(Ogre::Vector3(0,0,70));
			}
		}
		return true ;
	}

	bool MainApplication::keyReleased( const OIS::KeyEvent &arg )
	{
		// Keeps the keyboard state up to date
		m_keyboardState.notifyKeyReleased(arg.key) ;
		// Sends notification to super class
		BaseApplication::keyReleased(arg) ;
		return true ;
	}

	void MainApplication::vehicleGeneration(::std::vector<::std::string> a_vehicleList)
	{
		// Selection enemy's vehicles
		::std::vector<::std::string> types ;
		types.push_back("HippoR") ;
		types.push_back("CrocoR") ;
		types.push_back("MousticR") ;

		int ennemyUnits =0;
		while ( m_enemyMoney > 0 )
		{
			int vehicleType = (int)std::floorf(rand()%3);
			const GameElements::UnitsArchetypes::Archetype * unit = GlobalConfiguration::getConfigurationLoader()->getUnitsArchetypes().get(types[vehicleType]) ;
			if ( unit->m_cost <= m_enemyMoney )
			{
				m_enemyMoney -= unit->m_cost;
				m_enemyVehicleList.push_back(unit->m_name);
				ennemyUnits++;
			}
		}
		aiManager = new GameElements::AIManager();
		// Generation our vehicles
		for(int i = 0; i < a_vehicleList.size(); i++)
		{
			const GameElements::UnitsArchetypes::Archetype * unit = GlobalConfiguration::getConfigurationLoader()->getUnitsArchetypes().get(a_vehicleList[i]) ;
			const GameElements::WeaponsArchetypes::Archetype * weapon = GlobalConfiguration::getConfigurationLoader()->getWeaponsArchetypes().get(unit->m_weapon) ;
			if(weapon==NULL) { ::std::cout<< a_vehicleList[i] <<" : bad weapon!" ; char c ; ::std::cin>>c ; }
			GameElements::AiAgent* m_entityAdapter = new GameElements::AiAgent(unit, weapon, GlobalConfiguration::getCurrentMap(),m_sceneManager, GameElements::Team::blue) ;
			aiManager->addUnitToOpponentUnits(m_entityAdapter);
			m_entityAdapter->setPosition(GlobalConfiguration::getCurrentMap()->toWorldCoordinates(GlobalConfiguration::getCurrentMap()->findFreeLocation()).push(0.0)) ;
		}

		// Generation enemy's vehicles
		for(int i = 0; i < m_enemyVehicleList.size() ; i++)
		{
			const GameElements::UnitsArchetypes::Archetype * unit = GlobalConfiguration::getConfigurationLoader()->getUnitsArchetypes().get(m_enemyVehicleList[i]) ;
			const GameElements::WeaponsArchetypes::Archetype * weapon = GlobalConfiguration::getConfigurationLoader()->getWeaponsArchetypes().get(unit->m_weapon) ;
			if(weapon==NULL) { ::std::cout<< m_enemyVehicleList[i] <<" : bad weapon!" ; char c ; ::std::cin>>c ; }
			GameElements::AiAgent* m_entityAdapter = new GameElements::AiAgent(unit, weapon, GlobalConfiguration::getCurrentMap(),m_sceneManager, GameElements::Team::red) ;
			aiManager->addUnitToControlledUnits(m_entityAdapter);
			m_entityAdapter->setPosition(GlobalConfiguration::getCurrentMap()->toWorldCoordinates(GlobalConfiguration::getCurrentMap()->findFreeLocation()).push(0.0)) ;
		}

		aiManager->assignAllUnitsTarget();


	}
	
}


