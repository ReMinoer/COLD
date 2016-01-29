#include <stdafx.h>
#include "GameElements\GridPathfinder.h"
#include "GameElements\Map.h"

using namespace std;
using namespace Math;
using namespace Config;

namespace GameElements 
{
	GridPathfinder::GridPathfinder(Map* map, int gridStep)
		: _map(map), _success(false), _isEnd(true), _timeout(10), _gridStep(gridStep)
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
		
		_success = false;
		_isEnd = false;
	
		_openlist.clear();
		_closedlist.clear();
		
		for (int i = 0; i < height(); i++)
			for (int j = 0; j < width(); j++)
				_closedGrid[i][j] = false;

		_start = start;
		_finish = finish;
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
				node.parent = Vector2<int>(-1, -1);
				node.parentCost = move.norm();
				node.personalCost = remaining.norm();

				_openlist[point] = node;
			}

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
			
			/*
			for (int i = 0; i < 2; i++)
				for(int j = 0; j < 2; j++)
				{
					Vector2<int> point = _current + Vector2<int>(j, i);
					if (point == toGridCoordinates(_finish))
						_success = true;
				}
				*/

			if (_current == toGridCoordinates(_finish))
				_success = true;

			if (_success)
				break;

			ProcessSurroundingCases();

			clock_t end = clock();
			double elapsed = (double) (end-start);

			_timeoutElapsed += elapsed;
			_processDuration += elapsed;
		}

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

				Vector2<int> diff(j, i);
				
				if (!isValid(_current + diff))
					continue;

				if (_closedGrid[_current[1] + i][_current[0] + j])
					continue;

				Vector2<int> point = _current + diff;
				Vector2<float> worldPoint = toWorldCoordinates(point);

				if (!isValid(point) && getCell(point).m_speedReduction >= 1.0)
					continue;
		
				Vector2<float> move = worldPoint - toWorldCoordinates(_current);
				Vector2<float> remaining = _finish - worldPoint;

				float actionCost = getCell(point).m_speedReduction * 100;

				PathfinderNode node;
				node.parent = _current;
				node.parentCost = _closedlist[_current].parentCost + move.norm();
				node.personalCost = remaining.norm() + actionCost;

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
			path.push(toWorldCoordinates(toGridCoordinates(_finish)));
			current = _finish;
		}
		else
		{
			Vector2<int> bestPoint = BestNodeClosedlist();
			if (bestPoint == Vector2<Real>(-1, -1))
				return path;

			current = toWorldCoordinates(bestPoint);
			path.push(current);
		}
	
		PathfinderNode node = _closedlist[toGridCoordinates(current)];

		while (node.parent != Vector2<int>(-1, -1))
		{
			current = toWorldCoordinates(node.parent);
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
		return _map->width() / _gridStep;
	}

	int GridPathfinder::height() const
	{
		return _map->height() / _gridStep;
	}

	Math::Vector2<Real> GridPathfinder::toWorldCoordinates(Math::Vector2<int> const & gridCoordinates) const
	{
		return _map->toWorldCoordinates(gridCoordinates * _gridStep);
	}

	Math::Vector2<int> GridPathfinder::toGridCoordinates(Math::Vector2<Real> const & worldCoordinates) const
	{
		return _map->toGridCoordinates(worldCoordinates) / _gridStep;
	}

	const Map::GroundCellDescription & GridPathfinder::getCell(Math::Vector2<int> const & gridCoordinates) const
	{
		return _map->getCell(gridCoordinates * _gridStep);
	}

	const Map::GroundCellDescription & GridPathfinder::getCell(Math::Vector2<Config::Real> const & worldCoordinates) const
	{
		return _map->getCell(worldCoordinates);
	}

	bool GridPathfinder::isValid(Math::Vector2<int> const & gridCoordinates) const
	{
		return _map->isValid(gridCoordinates * _gridStep);
	}

	bool GridPathfinder::isValid(Math::Vector2<Config::Real> const & worldCoordinates) const
	{
		return _map->isValid(worldCoordinates);
	}
}