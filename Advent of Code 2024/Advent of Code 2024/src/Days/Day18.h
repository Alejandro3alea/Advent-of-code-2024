#pragma once
#include "DaysCommon.h"

struct AStarNode
{
	Point2D coords;
	float g;
	float h;

	AStarNode(const Point2D& pos, const Point2D& end, const float gVal = 0.0f) : coords(pos), g(gVal)
	{
		SetHCost(end);
	}

	// Distance from starting node
	void SetGCost(const float val) { g = val; }

	// Heuristic (distance from end node)
	void SetHCost(const Point2D& end) { h = coords.Dist(end); }

	// Total cost
	float GetFCost() const { return g + h; }


	bool operator<(const AStarNode& rhs) const { return GetFCost() > rhs.GetFCost(); }
};

std::vector<Point2D> GetPathFrom(const Matrix<Point2D>& parents, Point2D endPos)
{
	std::vector<Point2D> points;
	Point2D& currParent = endPos;
	while (currParent != Point2D(-1, -1))
	{
		points.push_back(currParent);
		currParent = parents[currParent];
	}

	std::reverse(points.begin(), points.end());
	return points;
}

std::vector<Point2D> ComputeAStar(const Matrix<uint8_t>& grid, const Point2D& start, const Point2D& end)
{
	const std::array<Point2D, 4> directions = { Point2D(0, -1), Point2D(-1, 0), Point2D(0, 1), Point2D(1, 0) };

	Matrix<uint8_t> explored(grid.size(), grid.row_size(), 0);
	Matrix<float> gCosts(grid.size(), grid.row_size(), std::numeric_limits<float>::max());
	Matrix<Point2D> parents(grid.size(), grid.row_size(), Point2D(-1, -1));

	std::priority_queue<AStarNode> open;
	open.push(AStarNode(start, end));
	gCosts[start] = 0;
	while (!open.empty())
	{
		const AStarNode currNode = open.top();
		if (currNode.coords == end)
			return GetPathFrom(parents, end);

		explored[currNode.coords] = 1;
		open.pop();

		for (const Point2D& dir : directions)
		{
			const Point2D newPos = currNode.coords + dir;
			if (!newPos.IsInBoundsOf(grid) || grid[newPos] == '#' || explored[newPos])
				continue;

			const float dirCost = currNode.g + 1.0f;
			if (gCosts[newPos] > dirCost)
			{
				gCosts[newPos] = dirCost;
				parents[newPos] = currNode.coords;
				open.push(AStarNode(newPos, end, dirCost));
			}
		}
	}

	return {};
}

void SolveDay18Part1()
{
	std::ifstream file("data/Day 18/Data.txt");
	if (!file || !file.is_open())
	{
		std::cout << "The solution is within your heart (DATA NOT FOUND!)." << std::endl;
		return;
	}

	Matrix<uint8_t> grid(71, 71, '.');

	uint32_t byteCount = 1024;
	std::string line;
	while (std::getline(file, line) && byteCount > 0)
	{
		std::istringstream iss(line);
		Point2D byteBlock;
		iss >> byteBlock.x;
		iss.ignore();
		iss >> byteBlock.y;
		grid[byteBlock] = '#';

		byteCount--;
	}


	const Point2D start(0, 0);
	const Point2D end(70, 70);
	std::vector<Point2D> result = ComputeAStar(grid, start, end);

	for (const Point2D& pos : result)
	{
		grid[pos] = 'O';
	}
	std::cout << grid << std::endl;

	std::cout << "The solution is " << result.size() - 1 << "!" << std::endl;
}

///////////////////////////////////////////////////////////////////////////
///
///////////////////////////////////////////////////////////////////////////

void SolveDay18Part2()
{
	std::ifstream file("data/Day 18/Data.txt");
	if (!file || !file.is_open())
	{
		std::cout << "The solution is within your heart (DATA NOT FOUND!)." << std::endl;
		return;
	}

	Matrix<uint8_t> grid(71, 71, '.');

	const Point2D start(0, 0);
	const Point2D end(70, 70);
	Point2D result;
	std::string line;
	while (std::getline(file, line))
	{
		std::istringstream iss(line);
		iss >> result.x;
		iss.ignore();
		iss >> result.y;
		grid[result] = '#';

		if (ComputeAStar(grid, start, end).empty())
			break;
	}

	std::cout << "The solution is " << result << "!" << std::endl;
}