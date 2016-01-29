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
	// BUG : Grid step != 1 don't work !
	class GridPathfinder
	{
	public:

		struct PathfinderNode
		{
			Vector2<int> parent;
			float personalCost;
			float parentCost;
		
			float getCost() const
			{
				return personalCost + parentCost;
			}
		};

		typedef ::boost::intrusive_ptr<GridPathfinder> Pointer;
	private:
		Map* _map;
		map<Vector2<int>, PathfinderNode> _openlist;
		bool** _closedGrid;
		map<Vector2<int>, PathfinderNode> _closedlist;
		bool _success;
		bool _isEnd;
		Vector2<Real> _start;
		Vector2<Real> _finish;
		Vector2<int> _current;
		int _gridStep;
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
		void ProcessSurroundingCases();
		Vector2<int> BestNodeOpenlist();
		Vector2<int> BestNodeClosedlist();
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