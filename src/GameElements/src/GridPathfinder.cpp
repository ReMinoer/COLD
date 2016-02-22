#include <stdafx.h>
#include "GameElements\GridPathfinder.h"
#include "GameElements\Map.h"

using namespace std;
using namespace Math;
using namespace Config;

namespace GameElements 
{
	GridPathfinder::GridPathfinder(Map* map, int gridStep)
		: _map(map), _succeed(false), _isEnd(true), _timeout(10)
	{
		_closedGrid = new bool*[height()];
		for (int i = 0; i < height(); i++)
			_closedGrid[i] = new bool[width()];
	}

	GridPathfinder::~GridPathfinder()
	{
		for (int i = 0; i < height(); i++)
			delete[] _closedGrid[i];
		delete[] _closedGrid;
	}

	bool GridPathfinder::Initialize(Vector2<Real> start, Vector2<Real> finish)
	{
		if(!isValid(start) || !isValid(finish) || getCell(start).m_speedReduction >= 1.0)
			return false;
		
		_succeed = false;
		_isEnd = false;
	
		_openlist = Openlist();
		_closedlist.clear();
		
		for (int i = 0; i < height(); i++)
			for (int j = 0; j < width(); j++)
				_closedGrid[i][j] = false;

		_start = start;
		_finish = finish;
		_gridFinish = toGridCoordinates(_finish);
		Vector2<int> origin = toGridCoordinates(_start);

		for (int i = 0; i < 2; i++)
			for(int j = 0; j < 2; j++)
			{
				Vector2<int> point = origin + Vector2<int>(j, i);

				if (!isValid(point) && getCell(point).m_speedReduction < 1.0)
					continue;

				Vector2<float> move = _start - toWorldCoordinates(point);
				Vector2<float> remaining = _finish - _start;

				PathfinderNode node;
				node.point = point;
				node.parent = Vector2<int>(-1, -1);
				node.parentCost = move.norm();
				node.personalCost = remaining.norm();
				
				_openlist.push(node);
			}

		_timeoutElapsed = 0;
		_processDuration = 0;

		return true;
	}

	bool GridPathfinder::ComputePath()
	{
		_timeoutElapsed = 0;
		_processDuration = 0;

		while (!_succeed && !_openlist.empty() && _timeoutElapsed < _timeout)
		{
			clock_t start = clock();

			PathfinderNode top;
			do
			{
				top = _openlist.top();
				_openlist.pop();
			}
			while (_closedGrid[top.point[1]][top.point[0]]);

			_closedlist[top.point] = top;
			_closedGrid[top.point[1]][top.point[0]] = true;
			
			if (top.point == _gridFinish)
				_succeed = true;
			else
				ProcessSurroundingCases(top);

			clock_t end = clock();
			double elapsed = (double) (end-start);

			_timeoutElapsed += elapsed;
			_processDuration += elapsed;
		}

		_isEnd = _succeed || _openlist.empty();

		return _succeed;
	}

	void GridPathfinder::ProcessSurroundingCases(PathfinderNode top)
	{
		for (int i = -1; i <= 1; i++)
			for (int j = -1; j <= 1; j++)
			{
				if (i == 0 && j == 0)
					continue;

				Vector2<int> point = top.point + Vector2<int>(j, i);
				
				if (!isValid(point))
					continue;

				if (_closedGrid[point[1]][point[0]])
					continue;

				if (getCell(point).m_speedReduction >= 1.0)
					continue;
		
				Vector2<float> worldPoint = toWorldCoordinates(point);
				Vector2<float> move = worldPoint - toWorldCoordinates(top.point);
				Vector2<float> remaining = _finish - worldPoint;

				PathfinderNode node;
				node.point = point;
				node.parent = top.point;
				node.parentCost = top.parentCost + move.norm() * (1.0 / (1.0 - getCell(point).m_speedReduction));
				node.personalCost = remaining.norm();
				
				_openlist.push(node);
			}
	}

	stack<Vector2<Real>> GridPathfinder::GetPath()
	{
		stack<Vector2<Real>> path;

		if (_closedlist.empty())
			return path;

		PathfinderNode node;

		if (_succeed)
		{
			path.push(_finish);
			node = _closedlist[toGridCoordinates(_finish)];
		}
		else
		{
			Vector2<int> bestPoint = BestPointClosedlist();
			if (bestPoint == Vector2<Real>(-1, -1))
				return path;

			node = _closedlist[bestPoint];
		}

		while (node.parent != Vector2<int>(-1, -1))
		{
			path.push(toWorldCoordinates(node.point));
			node = _closedlist[node.parent];
		}
		
		path.push(toWorldCoordinates(node.point));

		return path;
	}

	Vector2<int> GridPathfinder::BestPointClosedlist()
	{
		Vector2<int> pointMin = Vector2<int>(-1, -1);
		float distanceMin = numeric_limits<float>::max();
	
		for (map<Vector2<int>, PathfinderNode>::const_iterator it = _closedlist.begin(); it != _closedlist.end(); ++it)
		{
			Vector2<int> point = it->first;
			float distance = (_finish - toWorldCoordinates(point)).norm();
			if (distance < distanceMin)
			{
				distanceMin = distance;
				pointMin = it->first;
			}
		}

		return pointMin;
	}
	
	bool GridPathfinder::isEnd()
	{
		return _isEnd;
	}

	int GridPathfinder::width() const
	{
		return _map->width();
	}

	int GridPathfinder::height() const
	{
		return _map->height();
	}

	Math::Vector2<Real> GridPathfinder::toWorldCoordinates(Math::Vector2<int> const & gridCoordinates) const
	{
		return _map->toWorldCoordinates(gridCoordinates);
	}

	Math::Vector2<int> GridPathfinder::toGridCoordinates(Math::Vector2<Real> const & worldCoordinates) const
	{
		return _map->toGridCoordinates(worldCoordinates);
	}

	const Map::GroundCellDescription & GridPathfinder::getCell(Math::Vector2<int> const & gridCoordinates) const
	{
		return _map->getCell(gridCoordinates);
	}

	const Map::GroundCellDescription & GridPathfinder::getCell(Math::Vector2<Config::Real> const & worldCoordinates) const
	{
		return _map->getCell(worldCoordinates);
	}

	bool GridPathfinder::isValid(Math::Vector2<int> const & gridCoordinates) const
	{
		return _map->isValid(gridCoordinates);
	}

	bool GridPathfinder::isValid(Math::Vector2<Config::Real> const & worldCoordinates) const
	{
		return _map->isValid(worldCoordinates);
	}
}