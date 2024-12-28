#pragma once
#include "DaysCommon.h"

const std::array<Point2D, 4> directions = { Point2D(0, 1), Point2D(-1, 0),
											Point2D(0, -1), Point2D(1, 0) };

std::set<Point2D> GetTrailheads(const Matrix<int8_t>& map, const int8_t prevNum, const Point2D& pos)
{
	if (!pos.IsInBoundsOf(map))
		return std::set<Point2D>();
	
	const uint8_t c = map[pos];
	if (c != prevNum + 1)
		return std::set<Point2D>();

	if (c == '9')
		return std::set<Point2D>({ pos });

	std::set<Point2D> result;
	for (uint8_t i = 0; i < directions.size(); i++)
	{
		std::set<Point2D> dirRes = GetTrailheads(map, c, pos + directions[i]);
		result.insert(dirRes.begin(), dirRes.end());
	}
	return result;
}

void SolveDay10Part1()
{
	std::ifstream file("data/Day 10/Data.txt");
	if (!file || !file.is_open())
	{
		std::cout << "The solution is within your heart (DATA NOT FOUND!)." << std::endl;
		return;
	}


	Matrix<int8_t> topographicMap;
	std::string line;
	while (std::getline(file, line))
	{
		topographicMap.push_row({ line.begin(), line.end() });
	}

	uint32_t result = 0;
	for (size_t y = 0; y < topographicMap.size(); y++)
	{
		auto& row = topographicMap[y];
		for (size_t x = 0; x < row.size(); x++)
		{
			if (row[x] == '0')
			{
				std::set<Point2D> trailheadsFromOrigin = GetTrailheads(	topographicMap, '0' - 1,
																		Point2D(x,y));

				result += trailheadsFromOrigin.size();
			}
		}
	}

	std::cout << "The solution is " << result << "!" << std::endl;
}

///////////////////////////////////////////////////////////////////////////
///
///////////////////////////////////////////////////////////////////////////

uint32_t GetTrailheadRoutes(const Matrix<int8_t>& map, const int8_t prevNum, const Point2D& pos)
{
	if (!pos.IsInBoundsOf(map))
		return 0;

	const uint8_t c = map[pos];
	if (c != prevNum + 1)
		return 0;

	if (c == '9')
		return 1;

	uint32_t result = 0;
	for (uint8_t i = 0; i < directions.size(); i++)
	{
		result += GetTrailheadRoutes(map, c, pos + directions[i]);
	}

	return result;
}

void SolveDay10Part2()
{
	std::ifstream file("data/Day 10/Data.txt");
	if (!file || !file.is_open())
	{
		std::cout << "The solution is within your heart (DATA NOT FOUND!)." << std::endl;
		return;
	}

	Matrix<int8_t> topographicMap;
	std::string line;
	while (std::getline(file, line))
	{
		topographicMap.push_row({ line.begin(), line.end() });
	}

	uint32_t result = 0;
	for (size_t y = 0; y < topographicMap.size(); y++)
	{
		auto& row = topographicMap[y];
		for (size_t x = 0; x < row.size(); x++)
		{
			if (row[x] == '0')
			{
				result += GetTrailheadRoutes(topographicMap, '0' - 1, Point2D(x, y));
			}
		}
	}

	std::cout << "The solution is " << result << "!" << std::endl;
}