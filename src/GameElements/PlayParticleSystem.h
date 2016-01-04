#ifndef _GameElements_PlayParticleSystem_H
#define _GameElements_PlayParticleSystem_H

#include <GameElements/GameObject.h>
#include <Ext/Ogre/NodeManipulation.h>

namespace GameElements
{
		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \class	PlayParticleSystem
		///
		/// \brief	Simulation object that plays a particle system until particle emmission stops.
		///
		/// \author	Fabrice Lamarche, university of Rennes 1
		////////////////////////////////////////////////////////////////////////////////////////////////////
		class PlayParticleSystem : public GameObject
		{
		public:
			typedef ::boost::intrusive_ptr<PlayParticleSystem> Pointer ;

		private:
			bool m_firstStep ;
		public:

			////////////////////////////////////////////////////////////////////////////////////////////////////
			/// \fn	PlayParticleSystem::PlayParticleSystem(Ogre::SceneNode * entity);
			///
			/// \brief	Constructor.
			///
			/// \author	Fabrice Lamarche, university of Rennes 1
			/// \param [in,out]	entity	If non-null, the entity.
			////////////////////////////////////////////////////////////////////////////////////////////////////
			PlayParticleSystem(Ogre::SceneNode * entity);

			////////////////////////////////////////////////////////////////////////////////////////////////////
			/// \fn	virtual void PlayParticleSystem::onCollision (const CollisionMessage &message);
			///
			/// \brief	Executes the collision action (empty in our case).
			///
			/// \author	Fabrice Lamarche, university of Rennes 1
			/// \param	message	The message.
			////////////////////////////////////////////////////////////////////////////////////////////////////
			virtual void onCollision (const CollisionMessage &message);

			////////////////////////////////////////////////////////////////////////////////////////////////////
			/// \fn	virtual void PlayParticleSystem::update (Config::Real const &dt);
			///
			/// \brief	Updates the given dt.
			///
			/// \author	Fabrice Lamarche, university of Rennes 1
			/// \param	dt	The dt.
			////////////////////////////////////////////////////////////////////////////////////////////////////
			virtual void update (Config::Real const &dt);
		};
}

#endif