#include <stdafx.h>
#include "GameElements\GridPathfinder.h"
#include "GameElements\Map.h"

using namespace std;
using namespace Math;
using namespace Config;

namespace GameElements 
{
	GridPathfinder::GridPathfinder(Map* map)
		: _map(map), _success(false), _isEnd(false), _timeout(1)
	{
		_closedGrid = new bool*[_map->height()];
		for (int i = 0; i < _map->height(); i++)
			_closedGrid[i] = new bool[_map->width()];
	}

	GridPathfinder::~GridPathfinder()
	{
		for (int i = 0; i < _map->height(); i++)
			delete[] _closedGrid[i];
		delete[] _closedGrid;
	}

	bool GridPathfinder::Initialize(Vector2<Real> start, Vector2<Real> finish)
	{
		GameElements::Map::GroundCellDescription cell = _map->getCell(start);
		if(!_map->isValid(start) || !_map->isValid(finish) || cell.m_speedReduction >= 1.0)
			return false;
		
		_success = false;
		_isEnd = false;
	
		_openlist.clear();
		_closedlist.clear();
		
		for (int i = 0; i < _map->height(); i++)
			for (int j = 0; j < _map->width(); j++)
				_closedGrid[i][j] = false;

		_start = start;
		_finish = finish;
		_current = _map->toGridCoordinates(_start);
		
		Vector2<float> move = _start - _map->toWorldCoordinates(_current);
		Vector2<float> remaining = _finish - _start;

		PathfinderNode node;
		node.parentCost = move.norm();
		node.personalCost = remaining.norm();

		_closedlist[_current] = node;
		_closedGrid[_current[1]][_current[0]] = true;

		ProcessSurroundingCases();

		_timeoutElapsed = 0;
		_processDuration = 0;

		return true;
	}

	bool GridPathfinder::ComputePath()
	{
		_timeoutElapsed = 0;
		_processDuration = 0;

		while (!_openlist.empty() && _timeoutElapsed < _timeout)
		{
			clock_t start = clock();

			_current = BestNodeOpenlist();

			_closedlist[_current] = _openlist[_current];
			_closedGrid[_current[1]][_current[0]] = true;
			_openlist.erase(_current);

			if (_current == _map->toGridCoordinates(_finish))
				break;

			ProcessSurroundingCases();

			clock_t end = clock();
			double elapsed = (double) (end-start) / CLOCKS_PER_SEC;

			_timeoutElapsed += elapsed;
			_processDuration += elapsed;
		}

		_success = _current == _finish;
		_isEnd = _success || _openlist.empty();

		return _isEnd;
	}

	void GridPathfinder::ProcessSurroundingCases()
	{
		for (int i = -1; i <= 1; i++)
			for (int j = -1; j <= 1; j++)
			{
				if (i == 0 && j == 0)
					continue;

				if (_closedGrid[_current[1] + i][_current[0] + j])
					continue;

				Vector2<int> point(_current[0] + j, _current[1] + i);
				Vector2<float> worldPoint = _map->toWorldCoordinates(point);

				if (!_map->isValid(point) && _map->getCell(point).m_speedReduction >= 1.0)
					continue;
		
				Vector2<float> move = worldPoint - _map->toWorldCoordinates(_current);
				Vector2<float> remaining = _finish - worldPoint;

				float actionCost = _map->getCell(point).m_speedReduction * 5;

				PathfinderNode node;
				node.parent = _current;
				node.parentCost = _closedlist[_current].parentCost + move.norm() + actionCost;
				node.personalCost = remaining.norm();

				map<Vector2<int>, PathfinderNode>::const_iterator existingNode = _openlist.find(point);
				if (existingNode != _openlist.end())
				{
					if (node.getCost() < existingNode->second.getCost())
						_openlist[point] = node;
				}
				else
					_openlist[point] = node;
			}
	}

	stack<Vector2<Real>> GridPathfinder::GetPath()
	{
		stack<Vector2<Real>> path;

		if (_closedlist.empty())
			return path;

		Vector2<Real> current;
		if (_isEnd)
		{
			path.push(_finish);
			path.push(_map->toWorldCoordinates(_map->toGridCoordinates(_finish)));
			current = _finish;
		}
		else
		{
			Vector2<int> bestPoint = BestNodeClosedlist();
			if (bestPoint == Vector2<Real>(-1, -1))
				return path;

			current = _map->toWorldCoordinates(bestPoint);
			path.push(current);
		}
	
		PathfinderNode node = _closedlist[_map->toGridCoordinates(current)];

		while (current != _start)
		{
			current = _map->toWorldCoordinates(node.parent);
			node = _closedlist[node.parent];

			path.push(current);
		}

		return path;
	}

	Vector2<int> GridPathfinder::BestNodeOpenlist()
	{
		Vector2<int> pointMin = Vector2<int>(-1, -1);
		float costMin = numeric_limits<float>::max();

		for (std::map<Vector2<int>, PathfinderNode>::const_iterator it = _openlist.begin(); it != _openlist.end(); ++it)
		{
			float cost = it->second.getCost();
			if (cost < costMin)
			{
				costMin = cost;
				pointMin = it->first;
			}
		}

		return pointMin;
	}

	Vector2<int> GridPathfinder::BestNodeClosedlist()
	{
		Vector2<int> pointMin = Vector2<int>(-1, -1);
		float distanceMin = numeric_limits<float>::max();
	
		for (std::map<Vector2<int>, PathfinderNode>::const_iterator it = _closedlist.begin(); it != _closedlist.end(); ++it)
		{
			Vector2<int> point = it->first;
			float distance = (_finish - _map->toWorldCoordinates(point)).norm();
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
}