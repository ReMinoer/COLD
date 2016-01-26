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
		struct UnselectedAiAgentMessage
		{
			AiAgent & m_unselected ;

			UnselectedAiAgentMessage(AiAgent & object)
				: m_unselected(object)
			{}	
		};

		typedef ::boost::intrusive_ptr<AiAgent> Pointer;
	protected:
		GridPathfinder _pathfinder;
		stack<Math::Vector2<Config::Real>> _currentPath;
		Math::Vector2<Config::Real> _velocity;
		Math::Vector2<Config::Real> _nextDestination;
		Team m_team;
		Ogre::SceneManager * m_sceneManager ;
		Ogre::ManualObject * m_circle;
		
	private:
		static DesignPattern::StaticMember<System::MessageEmitter<SelectedAiAgentMessage> > AiAgentEmitter ;
		static DesignPattern::StaticMember<System::MessageEmitter<UnselectedAiAgentMessage> > AiAgentEmitterUnSelect ;
	public:
		AiAgent(const UnitsArchetypes::Archetype * archetype, const WeaponsArchetypes::Archetype * weaponArchetype, Map* map, Ogre::SceneManager * sceneManager, Team team=none);

		virtual void update(const Config::Real & dt);
		virtual void onCollision (const CollisionMessage & message);
		virtual Math::Vector2<Config::Real> getVelocity() const;

		bool setDestination(Math::Vector2<Config::Real> destination);
		void computePath();
		void getNextDestination();
		void onSelect();
		void onUnselect();
		static System::MessageEmitter<SelectedAiAgentMessage> * getAIMessageEmitter();
		static System::MessageEmitter<UnselectedAiAgentMessage> * getAIMessageEmitterUnSelect();
		Team getTeam();
		void drawCircle();
		void attackInRange();
		Ogre::ManualObject * getCircle();
	};
}

#endif