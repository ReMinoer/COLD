
#include "GameElements\GridPathfinder.h"
/*

GridPathfinder::GridPathfinder(Map map)
	: _map(map), _success(false), _isEnd(false), _isReady(true)
{
    _closedGrid = new bool[_map.height()][];
    for (int i = 0; i < _map.height(); i++)
        _closedGrid[i] = new bool[_map.width()];
}

void GridPathfinder::Initialize(Vector2<Config::Real> start, Vector2<Config::Real> finish)
{
    _success = false;
    _isReady = true;
    if (!(IsCaseExist(start) && IsCaseExist(finish) && IsCaseEmpty(start)))
    {
        _isReady = false;
        return;
    }
    _isEnd = false;
	
    _openlist.clear();
    _closedlist.clear();
	
    _closedGrid = new bool[_map.height()][];
    for (int i = 0; i < _map.height(); i++)
        _closedGrid[i] = new bool[_map.width()];

    _start = start;
    _finish = finish;
    _current = _start;

    _closedlist.insert();
    _closedGrid[_current.y][_current.x] = true;

    ProcessSurroundingCases();

    _timeoutElapsed = 0;
	_processDuration = 0;
}

bool GridPathfinder::ComputePath()
{
    if (!_isReady)
        return false;

    _timeoutElapsed = 0;
	_processDuration = 0;

    while (!_openlist.empty() && _timeoutElapsed < _timeout)
    {
		clock_t start = clock();

        _current = BestNodeOpenlist();

		_closedlist[_current] = _openlist[_current];
		_closedGrid[_current.x][_current.y] = true;
		_openlist.Remove(p);

        if (_current == _finish)
            break;

        ProcessSurroundingCases();

		clock_t end = clock();
		double elapsed = (double) (end-start) / CLOCKS_PER_SEC;

		_timeoutElapsed += elapsed;
		_processDuration += elapsed;
    }

    _success = _current == _finish;
    _isEnd = Success || _openlist.empty();

    return _isEnd;
}

vector<Vector2<Config::Real>> GridPathfinder::GetPath()
{
    vector<Vector2<Config::Real>> path;

    if (_closedlist.empty())
        return path;

	Vector2 current = _closedGrid[_finish.y][_finish.x] ? _finish : BestNodeClosedlist();

    if (current == Vector2(-1, -1))
        return path;
	
    PathfinderNode node = _closedlist[current];
    path.push_back(current);

    while (current != _start)
    {
        current = node.Parent;

        node = closedlist[current];
		path.push_back(current);
    }

    std::reverse(route.begin(), route.end());
    return path;
}

void GridPathfinder::ProcessSurroundingCases()
{
	for (int i = -1; i <= 1; i++)
		for (int j = -1; j <= 1; j++)
		{
			if (i == 0 && j = 0)
				continue;

			Vector2<int> point(_current.x + j, _current.y + i);

			if (!_map->isValid(point) && _map->getCell(point).m_speedReduction <= 0)
				continue;

			Vector2<int> move = point - _current;
			Vector2<int> remaining = _finish - point;

			float actionCost = (1 - _map->getCell(point).m_speedReduction) * 5;

			PathfinderNode node;
			node.parent = _current;
			node.cost = _closedlist[_current].cost + move.distance + remaining.distance + actionCost;

			PathfinderNode existingNode = _openlist.find(point);
			if (existingNode != map::end)
			{
				if (node.getCost() < existingNode.getCost())
					_openlist[point] = node;
			}
			else
				_openlist[point] = node;
		}
}

virtual Vector2<int> GridPathfinder::BestNodeOpenlist()
{
    var tmp = new Point(-1, -1);
    float p = float.MaxValue;

    foreach (KeyValuePair<Point, Node> n in Openlist)
    {
        float np = n.Value.Cost;
        if (np < p)
        {
            tmp = n.Key;
            p = np;
        }
    }

    return tmp;
}

virtual Vector2<int> GridPathfinder::BestNodeClosedlist()
{
    var tmp = new Point(-1, -1);
    float d = float.MaxValue;

    foreach (KeyValuePair<Point, Node> n in Closedlist)
    {
        float nd = DistanceTo(n.Key, Finish);
        if (nd < d)
        {
            d = nd;
            tmp = n.Key;
        }
    }

    return tmp;
}
*/
