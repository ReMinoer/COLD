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
		double _timeout;
		double _timeoutElapsed;
		double _processDuration;
	public:
		GridPathfinder(Map* map);
		~GridPathfinder();
		bool Initialize(Vector2<Real> start, Vector2<Real> finish);
		bool ComputePath();
		bool isEnd();
		stack<Vector2<Config::Real>> GetPath();
	private:
		void ProcessSurroundingCases();
		Vector2<int> BestNodeOpenlist();
		Vector2<int> BestNodeClosedlist();
	};
}

#endif