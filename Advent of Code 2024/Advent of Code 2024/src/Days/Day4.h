#pragma once
#include "DaysCommon.h"


///////////////////////////////////////////////////////////////////////////
///
///////////////////////////////////////////////////////////////////////////

const std::array<uint8_t, 4> xmasLetters = { 'X', 'M', 'A', 'S' };

const std::array<Point2D, 8> directions = { Point2D(-1, -1), Point2D(0, -1), Point2D(1, -1),
										  Point2D(-1,  0),			   Point2D(1,  0),
										  Point2D(-1,  1), Point2D(0,  1), Point2D(1,  1) };

const std::array<Point2D, 4> corners = {	Point2D(-1, -1), Point2D(1, -1),
										Point2D(-1, 1), Point2D(1, 1),};


///////////////////////////////////////////////////////////////////////////
///
///////////////////////////////////////////////////////////////////////////

bool IsInRange(const std::vector<std::string>& letterSoup, const Point2D& pos)
{
	return pos.y >= 0 && pos.y < letterSoup.size() && pos.x >= 0 && pos.x < letterSoup[0].size();
}

///////////////////////////////////////////////////////////////////////////
///
///////////////////////////////////////////////////////////////////////////

uint32_t GetXmasCountFromPos(const std::vector<std::string>& letterSoup, const uint32_t x, const uint32_t y)
{
	uint32_t totalCount = 0;
	for (uint32_t i = 0; i < directions.size(); i++)
	{
		Point2D currPos(x, y);
		bool isValidXmas = true;
		for (uint32_t j = 1; j < xmasLetters.size(); j++)
		{
			currPos += directions[i];
			if (!currPos.IsInRangeOf(letterSoup) || letterSoup[currPos.y][currPos.x] != xmasLetters[j])
			{
				isValidXmas = false;
				break;
			}
		}

		if (isValidXmas)
			totalCount++;
	}

	return totalCount;
}

///////////////////////////////////////////////////////////////////////////
///
///////////////////////////////////////////////////////////////////////////

void SolveDay4Part1()
{
	std::ifstream file("data/Day 4/Data.txt");
	if (!file || !file.is_open())
	{
		std::cout << "The solution is within your heart (DATA NOT FOUND!)." << std::endl;
		return;
	}


	std::vector<std::string> letterSoup;
	std::string line;
	while (std::getline(file, line))
	{
		letterSoup.push_back(line);
	}

	uint32_t totalCount = 0;
	const size_t height = letterSoup.size();
	const size_t width = letterSoup[0].size();
	for (size_t i = 0; i < height; i++)
	{
		for (size_t j = 0; j < width; j++)
		{
			const uint8_t c = letterSoup[i][j];
			if (c == xmasLetters[0])
				totalCount += GetXmasCountFromPos(letterSoup, j, i);
		}
	}

	std::cout << "The solution is " << totalCount << "!" << std::endl;
}

///////////////////////////////////////////////////////////////////////////
///
///////////////////////////////////////////////////////////////////////////

bool IsXShapedMas(const std::vector<std::string>& letterSoup, const uint32_t x, const uint32_t y)
{
	uint8_t mCount = 0;
	uint8_t sCount = 0;
	std::array<uint8_t, 4> cornerLetters;
	for (unsigned i = 0; i < corners.size(); i++)
	{
		Point2D cornerPos(x + corners[i].x, y + corners[i].y);

		if (!cornerPos.IsInRangeOf(letterSoup))
			return false;

		switch (const uint8_t cornerChar = letterSoup[cornerPos.y][cornerPos.x]; cornerChar)
		{
		case 'M':
			mCount++;
			cornerLetters[i] = cornerChar;
			break;
		case 'S':
			sCount++;
			cornerLetters[i] = cornerChar;
			break;
		default:
			return false;
		}
	}

	// Size of both are 2, and it's displayed diagonally
	return mCount == sCount && (cornerLetters[0] == cornerLetters[1] || cornerLetters[0] == cornerLetters[2]);
}

///////////////////////////////////////////////////////////////////////////
///
///////////////////////////////////////////////////////////////////////////

void SolveDay4Part2()
{
	std::ifstream file("data/Day 4/Data.txt");
	if (!file || !file.is_open())
	{
		std::cout << "The solution is within your heart (DATA NOT FOUND!)." << std::endl;
		return;
	}

	std::vector<std::string> letterSoup;
	std::string line;
	while (std::getline(file, line))
	{
		letterSoup.push_back(line);
	}

	uint32_t totalCount = 0;
	const size_t height = letterSoup.size();
	const size_t width = letterSoup[0].size();
	for (size_t i = 0; i < height; i++)
	{
		for (size_t j = 0; j < width; j++)
		{
			const uint8_t c = letterSoup[i][j];
			if (c == 'A' && IsXShapedMas(letterSoup, j, i))
				totalCount++;
		}
	}

	std::cout << "The solution is " << totalCount << "!" << std::endl;
}