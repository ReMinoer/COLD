#ifndef _GameElements_AiAgent_H
#define _GameElements_AiAgent_H

#include <stack>
#include <GameElements/Agent.h>
#include <GameElements/GridPathfinder.h>
#include <System\MessageEmitter.h>

namespace GameElements 
{
	enum Team {none, red, blue};

	class AiAgent : public Agent
	{
	public:
		struct SelectedAiAgentMessage
		{
			AiAgent & m_selected ;

			SelectedAiAgentMessage(AiAgent & object)
				: m_selected(object)
			{}
		};

		typedef ::boost::intrusive_ptr<AiAgent> Pointer;
	protected:
		GridPathfinder _pathfinder;
		stack<Math::Vector2<Config::Real>> _currentPath;
		Math::Vector2<Config::Real> _velocity;
		Math::Vector2<Config::Real> _nextDestination;
		Team m_team;
	private:
		static DesignPattern::StaticMember<System::MessageEmitter<SelectedAiAgentMessage> > AiAgentEmitter ;
	public:
		AiAgent(const UnitsArchetypes::Archetype * archetype, const WeaponsArchetypes::Archetype * weaponArchetype, Map* map, Team team=none);

		virtual void update(const Config::Real & dt);
		virtual void onCollision (const CollisionMessage & message);
		virtual Math::Vector2<Config::Real> getVelocity() const;

		bool setDestination(Math::Vector2<Config::Real> destination);
		void computePath();
		void getNextDestination();
		void onSelect();
		static System::MessageEmitter<SelectedAiAgentMessage> * getAIMessageEmitter();
	};
}

#endif