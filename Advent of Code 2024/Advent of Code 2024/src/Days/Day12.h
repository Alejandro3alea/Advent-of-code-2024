#pragma once
#include "DaysCommon.h"

struct RegionData
{
	uint64_t area = 0;
	std::set<Point2D> upWalls;
	std::set<Point2D> leftWalls;
	std::set<Point2D> downWalls;
	std::set<Point2D> rightWalls;

	uint64_t GetTotalWalls() { return upWalls.size() + leftWalls.size() +
		downWalls.size() + rightWalls.size(); }
};

void GetAreaAndPerimFromRegion(RegionData& data, const Matrix<uint8_t>& garden,
	std::set<Point2D>& visited, const Point2D& pos, 
	const uint8_t tile, const uint8_t& dirC)
{
	if (!pos.IsInBoundsOf(garden) || garden[pos] != tile)
	{
		switch (dirC)
		{
		case '^':
			data.upWalls.insert(pos);
			return;
		case '<':
			data.leftWalls.insert(pos);
			return;
		case 'v':
			data.downWalls.insert(pos);
			return;
		case '>':
			data.rightWalls.insert(pos);
			return;
		}
	}

	if (visited.contains(pos))
		return;


	visited.insert(pos);
	data.area++;

	GetAreaAndPerimFromRegion(data, garden, visited, pos + Point2D(0, -1), tile, '^');
	GetAreaAndPerimFromRegion(data, garden, visited, pos + Point2D(-1, 0), tile, '<');
	GetAreaAndPerimFromRegion(data, garden, visited, pos + Point2D(0, 1), tile, 'v');
	GetAreaAndPerimFromRegion(data, garden, visited, pos + Point2D(1, 0), tile, '>');
}

void SolveDay12Part1()
{
	std::ifstream file("data/Day 12/Data.txt");
	if (!file || !file.is_open())
	{
		std::cout << "The solution is within your heart (DATA NOT FOUND!)." << std::endl;
		return;
	}

	Matrix<uint8_t> garden;
	std::string line;
	while (std::getline(file, line))
	{
		garden.push_row({ line.begin(), line.end() });
	}

	std::set<Point2D> visited;
	uint64_t result = 0;
	for (uint32_t y = 0; y < garden.size(); y++)
	{
		for (uint32_t x = 0; x < garden.row_size(); x++)
		{
			Point2D pos(x, y);
			if (visited.contains(pos))
				continue;

			RegionData data;
			const uint8_t& c = garden[pos];
			GetAreaAndPerimFromRegion(data, garden, visited, pos, c, ' ');
			result += data.area * data.GetTotalWalls();
		}
	}

	std::cout << "The solution is " << result << "!" << std::endl;
}

///////////////////////////////////////////////////////////////////////////
///
///////////////////////////////////////////////////////////////////////////

uint64_t CountVerticalSides(const std::set<Point2D>& walls)
{
	std::unordered_map<int32_t, std::set<int32_t>> orderedWalls;
	for (const Point2D& pos : walls)
		orderedWalls[pos.x].insert(pos.y);

	uint64_t result = 0;
	for (auto& [x, yPositions] : orderedWalls)
	{
		int32_t prevVal = std::numeric_limits<int32_t>::max();
		for (const int32_t y : yPositions)
		{
			if (prevVal == std::numeric_limits<int32_t>::max())
			{
				prevVal = y;
				continue;
			}
			if (y != prevVal + 1)
				result++;

			prevVal = y;
		}

		result++;
	}

	return result;
}

uint64_t CountHorizontalSides(const std::set<Point2D>& walls)
{
	std::unordered_map<int32_t, std::set<int32_t>> orderedWalls;
	for (const Point2D& pos : walls)
		orderedWalls[pos.y].insert(pos.x);

	uint64_t result = 0;
	for (auto& [y, xPositions] : orderedWalls)
	{
		int32_t prevVal = std::numeric_limits<int32_t>::max();
		for (const int32_t x : xPositions)
		{
			if (prevVal == std::numeric_limits<int32_t>::max())
			{
				prevVal = x;
				continue;
			}
			if (x != prevVal + 1)
				result++;

			prevVal = x;
		}

		result++;
	}

	return result;
}

uint64_t CountSidesInRegion(RegionData& data)
{
	uint64_t result = 0;
	
	return	CountHorizontalSides(data.upWalls) + CountVerticalSides(data.leftWalls) +
			CountHorizontalSides(data.downWalls) + CountVerticalSides(data.rightWalls);
}

void SolveDay12Part2()
{
	std::ifstream file("data/Day 12/Data.txt");
	if (!file || !file.is_open())
	{
		std::cout << "The solution is within your heart (DATA NOT FOUND!)." << std::endl;
		return;
	}

	Matrix<uint8_t> garden;
	std::string line;
	while (std::getline(file, line))
	{
		garden.push_row({ line.begin(), line.end() });
	}

	std::set<Point2D> visited;
	uint64_t result = 0;
	for (uint32_t y = 0; y < garden.size(); y++)
	{
		for (uint32_t x = 0; x < garden.row_size(); x++)
		{
			Point2D pos(x, y);
			if (visited.contains(pos))
				continue;

			RegionData data;
			const uint8_t& c = garden[pos];
			GetAreaAndPerimFromRegion(data, garden, visited, pos, c, ' ');
			result += data.area * CountSidesInRegion(data);
		}
	}

	std::cout << "The solution is " << result << "!" << std::endl;
}