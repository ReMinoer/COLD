#include <stdafx.h>

#include <OgreFramework/KeyboardState.h>

namespace OgreFramework
{


	bool KeyboardState::isDown( OIS::KeyCode const & key ) const
	{
		m_keyboardState.insert(::std::make_pair(key, false)) ;
		return m_keyboardState[key] ;
	}

	bool KeyboardState::isUp( OIS::KeyCode const & key ) const
	{
		m_keyboardState.insert(::std::make_pair(key, false)) ;
		return !m_keyboardState[key] ;
	}

	void KeyboardState::notifyKeyPressed( OIS::KeyCode const & key )
	{
		m_keyboardState[key] = true ;
	}

	void KeyboardState::notifyKeyReleased( OIS::KeyCode const & key )
	{
		m_keyboardState[key] = false ;
	}
}