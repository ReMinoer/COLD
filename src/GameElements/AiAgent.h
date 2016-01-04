#ifndef _GameElements_AiAgent_H
#define _GameElements_AiAgent_H

#include <GameElements/Agent.h>

namespace GameElements 
{
	class AiAgent : public Agent
	{
	public:
		typedef ::boost::intrusive_ptr<AiAgent> Pointer;
	protected:
		Math::Vector2<Config::Real> _velocity;
		Math::Vector2<Config::Real> _destination;
	public:
		AiAgent(const UnitsArchetypes::Archetype * archetype, const WeaponsArchetypes::Archetype * weaponArchetype);

		virtual void update(const Config::Real & dt);
		virtual void onCollision (const CollisionMessage & message);
		virtual Math::Vector2<Config::Real> getVelocity() const;

		void setDestination(Math::Vector2<Config::Real> destination);
	};
}

#endif