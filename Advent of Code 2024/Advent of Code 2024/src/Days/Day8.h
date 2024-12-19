#pragma once
#include "DaysCommon.h"

void SolveDay8Part1()
{
	std::ifstream file("data/Day 8/Data.txt");
	if (!file || !file.is_open())
	{
		std::cout << "The solution is within your heart (DATA NOT FOUND!)." << std::endl;
		return;
	}

	uint16_t width = 0;
	uint16_t height = 0;

	std::string line;
	std::map<uint8_t, std::vector<Point2D>> nodeList;
	std::vector< std::vector<bool> > antinodes;
	while (std::getline(file, line))
	{
		width = line.size();
		for (size_t x = 0; x < line.size(); x++)
		{
			const uint8_t c = line[x];
			if (c != '.')
				nodeList[c].push_back(Point2D(x, height));
		}

		antinodes.push_back(std::vector<bool>(false, width));
		height++;
	}


	for (auto currFreq : nodeList)
	{
		const std::vector<Point2D>& positions = currFreq.second;
		for (size_t i = 0; i < positions.size(); i++)
		{
			for (size_t j = i; j < positions.size(); j++)
			{
				const Point2D& lPos = positions[i];
				const Point2D& rPos = positions[j];
				const Point2D dir = rPos - lPos;

				const Point2D newLPos = lPos - dir;
				const Point2D newRPos = rPos + dir;

				if (newLPos.IsInRangeOf(width, height))
				{
					//antinodes[]
				}
			}
		}
	}

	uint32_t result = 0;
	std::cout << "The solution is " << result << "!" << std::endl;
}

///////////////////////////////////////////////////////////////////////////
///
///////////////////////////////////////////////////////////////////////////

void SolveDay8Part2()
{
	std::ifstream file("data/Day 8/Data.txt");
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