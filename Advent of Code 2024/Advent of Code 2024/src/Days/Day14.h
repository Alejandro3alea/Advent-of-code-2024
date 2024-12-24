#pragma once
#include "DaysCommon.h"

struct RobotData
{
	Point2D pos;
	Point2D vel;
};

std::vector<RobotData> ParseData(const std::string& robotData)
{
	std::vector<RobotData> result;
	std::regex dataRegex(R"(p=(\d+),(\d+) v=(-?\d+),(-?\d+))");

	auto begin = std::sregex_iterator(robotData.begin(), robotData.end(), dataRegex);
	auto end = std::sregex_iterator();

	for (auto it = begin; it != end; ++it) {
		const std::smatch& match = *it;

		result.push_back({
			Point2D(std::stoul(match[1].str()), std::stoul(match[2].str())), // pos
			Point2D(std::stoul(match[3].str()), std::stoul(match[4].str()))  // vel
			});
	}

	return result;
}


void SolveDay14Part1()
{
	std::ifstream file("data/Day 14/Data.txt");
	if (!file || !file.is_open())
	{
		std::cout << "The solution is within your heart (DATA NOT FOUND!)." << std::endl;
		return;
	}

	std::string robotDataStr;
	std::string line;
	while (std::getline(file, line))
	{
		robotDataStr += line + '\n';
	}

	const Point2D boxSize(101, 103);
	const Point2D boxMidpoint = boxSize / 2;
	std::vector<RobotData> robotData = ParseData(robotDataStr);
	std::array<uint32_t, 4> robotsPerQuadrant = { 0 };

	const int32_t stepCount = 100;
	for (const RobotData& data : robotData)
	{
		Point2D finalPos = data.pos + data.vel * stepCount;
		finalPos %= boxSize;
		if (finalPos.x < 0)
			finalPos.x += boxSize.x;
		if (finalPos.y < 0)
			finalPos.y += boxSize.y;

		// Checks for quadrants
		if (finalPos.x == boxMidpoint.x || finalPos.y == boxMidpoint.y)
			continue;

		uint8_t quadrantIdxX = (finalPos.x < boxMidpoint.x) ? 0 : 1;
		uint8_t quadrantIdxY = (finalPos.y < boxMidpoint.y) ? 0 : 2;
		robotsPerQuadrant[quadrantIdxX + quadrantIdxY]++;
	}

	uint32_t result = 1;
	for (uint8_t i = 0; i < robotsPerQuadrant.size(); i++)
		result *= robotsPerQuadrant[i];

	std::cout << "The solution is " << result << "!" << std::endl;
}

///////////////////////////////////////////////////////////////////////////
///
///////////////////////////////////////////////////////////////////////////

void UpdateRobotData(std::vector<RobotData>& data, const Point2D& boxSize)
{
	for (RobotData& robot : data)
	{
		robot.pos += robot.vel;
		robot.pos %= boxSize;

		if (robot.pos.x < 0)
			robot.pos.x += boxSize.x;
		if (robot.pos.y < 0)
			robot.pos.y += boxSize.y;
	}
}

void SolveDay14Part2()
{
	std::ifstream file("data/Day 14/Data.txt");
	if (!file || !file.is_open())
	{
		std::cout << "The solution is within your heart (DATA NOT FOUND!)." << std::endl;
		return;
	}

	std::string robotDataStr;
	std::string line;
	while (std::getline(file, line))
	{
		robotDataStr += line + '\n';
	}

	const Point2D boxSize(101, 103);
	const Point2D treeBoxSize(14, 8);
	const Point2D boxMidpoint = boxSize / 2;
	
	auto resetMtx = [](Matrix<uint8_t>& out)
	{
		for (uint8_t y = 0; y < out.size(); y++)
		{
			for (uint8_t x = 0; x < out.row_size(); x++)
			{
				out[y][x] = '.';
			}
		}
	};

	auto robotDataToMtx = [resetMtx](const std::vector<RobotData>& data, Matrix<uint8_t>& out)
	{
		resetMtx(out);

		for (const RobotData& currData : data)
		{
			out[currData.pos] = '#';
		}
	};

	auto scanForHorizontalBoxLine = [treeBoxSize](const Matrix<uint8_t>& data) -> bool
	{
		for (uint8_t y = 0; y < data.size(); y++)
		{
			uint16_t currCount = 0;
			for (uint8_t x = 0; x < data.row_size(); x++)
			{
				const uint8_t& val = data[y][x];
				if (val == '#')
				{
					currCount++;
					if (currCount >= treeBoxSize.x)
						return true;
				}
				else
					currCount = 0;
			}
		}

		return false;
	};

	std::vector<RobotData> robotData = ParseData(robotDataStr);

	Matrix<uint8_t> displayMtx(boxSize.x, boxSize.y);
	bool wasTreeFound = false;
	uint32_t result = 0;
	while (!wasTreeFound)
	{
		robotDataToMtx(robotData, displayMtx);
		wasTreeFound = scanForHorizontalBoxLine(displayMtx);

		UpdateRobotData(robotData, boxSize);

		result++;
	}

	std::cout << displayMtx << std::endl;
	std::cout << "The solution is " << result - 1 << "!" << std::endl;
}