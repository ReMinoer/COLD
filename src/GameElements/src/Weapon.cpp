#include <stdafx.h>
#include <GameElements/Weapon.h>
#include <GameElements/StraightBullet.h>
#include <GameElements/BallisticBullet.h>
#include <OgreFramework/GlobalConfiguration.h>
#include <fmod.hpp>

namespace GameElements
{


	void Weapon::createBullet( Math::Vector2<Config::Real> const & origin, Math::Vector2<Config::Real> const & target ) const
	{
		BulletBase * bullet = NULL ;
		if(m_archetype->m_type=="straight")
		{
			Math::Vector2<Config::Real> velocity = (target-origin).normalized()*m_archetype->m_speed ;
			bullet = new GameElements::StraightBullet(OgreFramework::GlobalConfiguration::getGeometryLoader()->load(m_archetype->m_bulletMesh), m_archetype->m_strength, m_archetype->m_armorDamage, origin, velocity, m_archetype->m_range) ;
			OgreFramework::GlobalConfiguration::playSound("../data/sound/laser.mp3");
		}
		else if(m_archetype->m_type=="ballistic")
		{
			Math::Vector2<Config::Real> newTarget = target ;
			if((newTarget-origin).norm()>m_archetype->m_range) // Handles shooting range
			{
				newTarget = origin + (newTarget-origin).normalized()*m_archetype->m_range ;
			}
			bullet = new GameElements::BallisticBullet(OgreFramework::GlobalConfiguration::getGeometryLoader()->load(m_archetype->m_bulletMesh), m_archetype->m_strength, m_archetype->m_armorDamage, origin, m_archetype->m_speed, newTarget, m_archetype->m_extent) ;
			//OgreFramework::GlobalConfiguration::playSound("../data/sound/riffle-fire.ogg");

			////int channels ;
			////OgreFramework::GlobalConfiguration::getSoundSystem()->getChannelsPlaying(&channels) ;
			////if(channels<256)
			//{
			//	static int channelNumber = 0 ;
			//	channelNumber =  (channelNumber + 1)%256 ;
			//	FMOD::Sound * sound ; 
			//	FMOD_RESULT result = OgreFramework::GlobalConfiguration::getSoundSystem()->createSound("../data/sound/riffle-fire.ogg", FMOD_DEFAULT, 0, &sound) ;
			//	if(result!=FMOD_OK) { ::std::cout<<"Error loading sound"<<::std::endl ; }
			//	FMOD::Channel *channel ;
			//	result = OgreFramework::GlobalConfiguration::getSoundSystem()->playSound(FMOD_CHANNELINDEX(channelNumber), sound, true, &channel) ;
			//	if(result!=FMOD_OK) { ::std::cout<<"Error playing sound"<<::std::endl ; }
			//	else
			//	{
			//		::std::cout<<"Playing sound..."<<::std::endl ;
			//		channel->setVolume(1.0) ;
			//		channel->setPaused(false) ;
			//	}
			//}
		}
		bullet->addFilter(m_filter.begin(), m_filter.end()) ;
	}

	Weapon::Weapon( const WeaponsArchetypes::Archetype * archetype ) : m_archetype(archetype), m_lastFireDate(::tbb::tick_count::now())
	{

	}

	bool Weapon::fire( Math::Vector2<Config::Real> const & origin, Math::Vector2<Config::Real> const & target )
	{
		if(canFire())
		{
			m_lastFireDate = ::tbb::tick_count::now() ;
			createBullet(origin, target) ;
			return true ;
		}
		return false ;
	}

	bool Weapon::canFire() const
	{
		::tbb::tick_count time = ::tbb::tick_count::now() ;
		return (time-m_lastFireDate).seconds()>=(1.0/m_archetype->m_frequency) ;
	}
}