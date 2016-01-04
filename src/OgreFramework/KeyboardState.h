#ifndef _OgreFramework_KeyboardState_H
#define _OgreFramework_KeyboardState_H

#include <OIS/OISKeyboard.h>
#include <DesignPattern/Singleton.h>

namespace OgreFramework
{
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \class	KeyboardState
	///
	/// \brief	An instance of this class keeps a keyboard state that can be queried at any time. The 
	/// 		application must notify key pressed and released to keep the keyboard state up to date.
	/// 		This class is a Singleton.
	///
	/// \author	Fabrice Lamarche, University of Rennes 1
	/// \date	03/12/2011
	////////////////////////////////////////////////////////////////////////////////////////////////////
	class KeyboardState : public DesignPattern::Singleton<KeyboardState>
	{
	private:
		friend class DesignPattern::Singleton<KeyboardState> ;
		KeyboardState()
		{}

	protected:
		///< Current state of the keyboard
		mutable ::std::map<OIS::KeyCode, bool> m_keyboardState ;

	public:

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	bool KeyboardState::isDown(OIS::KeyCode const & key) const
		///
		/// \brief	Query if 'key' is down.
		///
		/// \author	Fabrice Lamarche, University of Rennes 1
		/// \date	03/12/2011
		///
		/// \param	key	The key.
		///
		/// \return	true if down, false if not.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		bool isDown(OIS::KeyCode const & key) const ;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	bool KeyboardState::isUp(OIS::KeyCode const & key) const
		///
		/// \brief	Query if 'key' is up.
		///
		/// \author	Fabrice Lamarche, University of Rennes 1
		/// \date	03/12/2011
		///
		/// \param	key	The key.
		///
		/// \return	true if up, false if not.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		bool isUp(OIS::KeyCode const & key) const;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	void KeyboardState::notifyKeyPressed(OIS::KeyCode const & key)
		///
		/// \brief	Notifies that a key is pressed.
		///
		/// \author	Fabrice Lamarche, University of Rennes 1
		/// \date	03/12/2011
		///
		/// \param	key	The key.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void notifyKeyPressed(OIS::KeyCode const & key);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	void KeyboardState::notifyKeyReleased(OIS::KeyCode const & key)
		///
		/// \brief	Notifies that a key is released.
		///
		/// \author	Fabrice Lamarche, University of Rennes 1
		/// \date	03/12/2011
		///
		/// \param	key	The key.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void notifyKeyReleased(OIS::KeyCode const & key);
	};
}

#endif