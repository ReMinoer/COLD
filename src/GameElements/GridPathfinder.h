#ifndef _GameElements_GridPathfinder_H
#define _GameElements_GridPathfinder_H

#include <stack>
#include <map>
#include "Math\Vector2.h"
#include "GameElements\Map.h"

using namespace std;
using namespace Math;
using namespace Config;

namespace GameElements 
{
	class GridPathfinder
	{
	public:

		struct PathfinderNode
		{
			Vector2<int> point;
			Vector2<int> parent;
			float personalCost;
			float parentCost;
		
			float getCost() const
			{
				return personalCost + parentCost;
			}
		};

		class ByCost
		{
			public:
				bool operator()(PathfinderNode a, PathfinderNode b)
				{
					return a.getCost() > b.getCost();
				}
		};

		typedef ::boost::intrusive_ptr<GridPathfinder> Pointer;
		
	private:

		typedef priority_queue<PathfinderNode, vector<PathfinderNode>, ByCost> Openlist;
		typedef map<Vector2<int>, PathfinderNode> Closedlist;

		Map* _map;
		Openlist _openlist;
		bool** _closedGrid;
		Closedlist _closedlist;
		bool _succeed;
		bool _isEnd;
		Vector2<Real> _start;
		Vector2<Real> _finish;
		Vector2<int> _gridFinish;
		double _timeout;
		double _timeoutElapsed;
		double _processDuration;
	public:
		GridPathfinder(Map* map, int gridStep = 1);
		~GridPathfinder();
		bool Initialize(Vector2<Real> start, Vector2<Real> finish);
		bool ComputePath();
		bool isEnd();
		stack<Vector2<Config::Real>> GetPath();
	private:
		void ProcessSurroundingCases(PathfinderNode top);
		Vector2<int> BestPointClosedlist();
		int width() const;
		int height() const;
		Math::Vector2<int> toGridCoordinates(Math::Vector2<Real> const & worldCoordinates) const;
		Math::Vector2<Real> toWorldCoordinates(Math::Vector2<int> const & gridCoordinates) const;
		const Map::GroundCellDescription & getCell(Math::Vector2<int> const & gridCoordinates) const;
		const Map::GroundCellDescription & getCell(Math::Vector2<Config::Real> const & worldCoordinates) const;
		bool isValid(Math::Vector2<int> const & gridCoordinates) const;
		bool isValid(Math::Vector2<Config::Real> const & worldCoordinates) const;
	};
}

#endif