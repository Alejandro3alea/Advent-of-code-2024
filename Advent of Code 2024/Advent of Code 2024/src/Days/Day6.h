#pragma once
#include "DaysCommon.h"

using MapData = std::vector<std::string>;


void SolveDay6Part1()
{
	std::ifstream file("data/Day 6/Data.txt");
	if (!file || !file.is_open())
	{
		std::cout << "The solution is within your heart (DATA NOT FOUND!)." << std::endl;
		return;
	}

	const std::array<Point2D, 4> directions = { Point2D(0, 1), Point2D(1, 0), Point2D(0, -1), Point2D(-1, 0) };
	const uint8_t playerC = '^';
	const uint8_t obstacleC = '#';

	uint32_t result = 0;

	std::vector<Point2D> obstacles;
	Point2D playerPos;
	MapData mapData;
	uint32_t y = 0;
	std::string line;
	while (std::getline(file, line))
	{
		mapData.push_back(line);
		for (uint32_t x = 0; x < line.size(); x++)
		{
			switch (const uint8_t& c = line[x]; c)
			{
			case playerC:
				playerPos = Point2D(x, y);
				break;
			case obstacleC:
				obstacles.push_back(Point2D(x, y));
			}
		}

		y++;
	}

	size_t currDir = 0;
	while (playerPos.IsInRangeOf(mapData))
	{
		Point2D nextPos = playerPos + directions[currDir];
		if (const uint8_t nextC = GetValue(mapData, nextPos); nextC == obstacleC)
		{
			currDir++;
			if (currDir >= directions.size())
				currDir = 0;
			
			continue;
		}

		SetValue(mapData, playerPos, 'X');
		playerPos = nextPos;
	}

	std::cout << "The solution is " << result << "!" << std::endl;
}

///////////////////////////////////////////////////////////////////////////
///
///////////////////////////////////////////////////////////////////////////

void SolveDay6Part2()
{
	std::ifstream file("data/Day 6/Data.txt");
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