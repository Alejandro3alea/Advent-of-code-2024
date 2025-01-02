#pragma once
#include "DaysCommon.h"

std::array<Point2D, 4> directions = { Point2D(0, -1), Point2D(-1, 0), Point2D(0, 1), Point2D(1, 0) };

std::vector<size_t> GetAlternativeDirections(const Matrix<uint8_t>& lab, const Point2D& pos, const size_t dir)
{
	std::vector<size_t> result;
	const size_t oppDir = (dir + 2) % directions.size();
	for (uint32_t i = 0; i < directions.size(); i++)
	{
		if (i != dir && i != oppDir)
		{
			const Point2D newPos = pos + directions[i];
			if (lab[newPos] != '#')
				result.push_back(i);
		}
	}

	return result;
}

// Too unperformant, recurses too much
uint32_t Step(const Matrix<uint8_t>& lab, const Point2D& pos, const size_t dir, 
	const Point2D& endPos, const uint32_t cost, const bool shouldRotate, 
	std::unordered_set<Point2D> visited)
{
	if (pos == endPos)
		return cost;

	const uint8_t& c = lab[pos];
	if (c == '#' || visited.contains(pos))
		return std::numeric_limits<uint32_t>::max();

	visited.insert(pos);

	std::cout << pos << " + " << directions[dir] << std::endl;

	uint32_t bestCost = std::numeric_limits<uint32_t>::max();
	if (shouldRotate)
	{
		auto altDirs = GetAlternativeDirections(lab, pos, dir);
		for (size_t& altDir : altDirs)
		{
			bestCost = std::min(bestCost, Step(lab, pos + directions[altDir], altDir, endPos, cost + 1001, false, visited));
		}
	}

	bestCost = std::min(bestCost, Step(lab, pos + directions[dir], dir, endPos, cost + 1, true, visited));
	
	return bestCost;
}

void SolveDay16Part1()
{
	std::ifstream file("data/Day 16/Data.txt");
	if (!file || !file.is_open())
	{
		std::cout << "The solution is within your heart (DATA NOT FOUND!)." << std::endl;
		return;
	}

	Matrix<uint8_t> labyrinth;

	std::string line;
	while (std::getline(file, line))
	{
		labyrinth.push_row({ line.begin(), line.end() });
	}

	size_t startDir = 3;
	Point2D playerPos = labyrinth.find_first_of('S');
	const Point2D endPos = labyrinth.find_first_of('E');

	

	uint32_t result = Step(labyrinth, playerPos, 3, endPos, 0, true, std::unordered_set<Point2D>());
	std::cout << "The solution is " << result << "!" << std::endl;
}

///////////////////////////////////////////////////////////////////////////
///
///////////////////////////////////////////////////////////////////////////

void SolveDay16Part2()
{
	std::ifstream file("data/Day 16/Data.txt");
	if (!file || !file.is_open())
	{
		std::cout << "The solution is within your heart (DATA NOT FOUND!)." << std::endl;
		return;
	}

	uint32_t result = 0;

	std::string line;
	while (std::getline(file, line))
	{
	}

	std::cout << "The solution is " << result << "!" << std::endl;
}