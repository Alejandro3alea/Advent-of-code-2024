#pragma once
#include "DaysCommon.h"

using MapData = std::vector<std::string>;

const std::array<Point2D, 4> directions = { Point2D(0, -1), Point2D(1, 0), Point2D(0, 1), Point2D(-1, 0) };
const uint8_t playerC = '^';
const uint8_t obstacleC = '#';
const uint8_t traversedC = 'X';

///////////////////////////////////////////////////////////////////////////
///
///////////////////////////////////////////////////////////////////////////

std::set<Point2D> CountXInMapData(const MapData& mapData)
{
	std::set<Point2D> xPositions;
	for (uint32_t y = 0; y < mapData.size(); y++)
	{
		std::string_view str = mapData[y];
		for (uint32_t x = 0; x < str.size(); x++)
		{
			if (str[x] == traversedC)
				xPositions.insert(Point2D(x, y));
		}
	}

	return xPositions;
}

///////////////////////////////////////////////////////////////////////////
///
///////////////////////////////////////////////////////////////////////////

void ProcessPlayerTraversal(MapData& mapData, const Point2D& playerStartPos)
{
	Point2D playerPos = playerStartPos;
	size_t currDir = 0;
	while (playerPos.IsInBoundsOf(mapData))
	{
		SetValue(mapData, playerPos, traversedC);

		const Point2D nextPos = playerPos + directions[currDir];
		if (!nextPos.IsInBoundsOf(mapData))
			break;

		if (const uint8_t nextC = GetValue(mapData, nextPos); nextC == obstacleC)
		{
			currDir++;
			if (currDir >= directions.size())
				currDir = 0;

			continue;
		}

		playerPos = nextPos;
	}
}

///////////////////////////////////////////////////////////////////////////
///
///////////////////////////////////////////////////////////////////////////

void SolveDay6Part1()
{
	std::ifstream file("data/Day 6/Data.txt");
	if (!file || !file.is_open())
	{
		std::cout << "The solution is within your heart (DATA NOT FOUND!)." << std::endl;
		return;
	}

	std::vector<Point2D> obstacles;
	Point2D playerStartPos;
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
				playerStartPos = Point2D(x, y);
				break;
			case obstacleC:
				obstacles.push_back(Point2D(x, y));
			}
		}

		y++;
	}

	ProcessPlayerTraversal(mapData, playerStartPos);
	std::set<Point2D> result = CountXInMapData(mapData);
	std::cout << "The solution is " << result.size() << "!" << std::endl;
}

///////////////////////////////////////////////////////////////////////////
///
///////////////////////////////////////////////////////////////////////////

bool DoesNewObstacleCreateALoop(const Point2D& newObs, const Point2D& playerStartPos, const MapData& mapData)
{
	struct CollisionData
	{
		Point2D pos;
		uint32_t dirIdx;

		bool operator<(const CollisionData& rhs) const
		{
			return pos < rhs.pos || (pos == rhs.pos && dirIdx < rhs.dirIdx);
		}

		bool operator==(const CollisionData& rhs) const
		{
			return pos == rhs.pos && dirIdx == rhs.dirIdx;
		}
	};

	if (newObs == playerStartPos)
		return false;

	std::set<CollisionData> metObstacles;
	size_t currDir = 0;
	Point2D playerPos = playerStartPos;
	while (playerPos.IsInBoundsOf(mapData))
	{
		const Point2D nextPos = playerPos + directions[currDir];
		if (!nextPos.IsInBoundsOf(mapData))
			return false;

		const uint8_t nextC = GetValue(mapData, nextPos);
		if (newObs == nextPos || nextC == obstacleC)
		{
			CollisionData collisionData(nextPos, currDir);
			if (metObstacles.find(collisionData) != metObstacles.end())
				return true;

			metObstacles.insert(collisionData);

			currDir++;
			if (currDir >= directions.size())
				currDir = 0;

			continue;
		}

		playerPos = nextPos;
	}

	return false;
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

	std::vector<Point2D> obstacles;
	Point2D playerStartPos;
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
				playerStartPos = Point2D(x, y);
				break;
			case obstacleC:
				obstacles.push_back(Point2D(x, y));
			}
		}

		y++;
	}

	uint32_t result = 0;
	ProcessPlayerTraversal(mapData, playerStartPos);
	std::set<Point2D> xPositions = CountXInMapData(mapData);
	for (Point2D newObstaclePos : xPositions)
	{
		if (DoesNewObstacleCreateALoop(newObstaclePos, playerStartPos, mapData))
		{
			result++;
		}
	}

	std::cout << "The solution is " << result << "!" << std::endl;
}