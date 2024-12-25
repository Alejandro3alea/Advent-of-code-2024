#pragma once
#include "DaysCommon.h"

std::map<uint8_t, Point2D> directions = { {'^', Point2D(0, -1) }, {'<', Point2D(-1, 0) },
										  {'v', Point2D(0, 1) }, {'>', Point2D(1, 0) }, };


size_t GetTotalGPSCounter(const Matrix<uint8_t>& wh)
{
	size_t count = 0;

	for (uint32_t y = 0; y < wh.size(); y++)
	{
		for (uint32_t x = 0; x < wh.row_size(); x++)
		{
			const uint8_t& c = wh[y][x];
			if (c == 'O' || c == '[')
			{
				count += 100 * y + x;
			}
		}
	}

	return count;
}

bool MovePart1(Matrix<uint8_t>& wh, const Point2D& pos, const uint8_t dir, const uint8_t prevChar)
{
	const Point2D newPos = pos + directions[dir];
	uint8_t& c = wh[newPos];
	switch (bool res; c)
	{
	case '.':
		c = prevChar;
		return true;

	case 'O':
		res = MovePart1(wh, newPos, dir, c);
		c = res ? prevChar : c;
		return res;

	default: // Unknown character or wall
		return false;
	}
}

void SolveDay15Part1()
{
	std::ifstream file("data/Day 15/Data.txt");
	if (!file || !file.is_open())
	{
		std::cout << "The solution is within your heart (DATA NOT FOUND!)." << std::endl;
		return;
	}

	Matrix<uint8_t> warehouse;

	std::string line;
	while (std::getline(file, line))
	{
		if (line.empty())
			break;

		warehouse.push_row({ line.begin(), line.end() });
	}

	Point2D playerPos = warehouse.find_first_of('@');
	while (std::getline(file, line))
	{
		for (const uint8_t c : line)
		{
			if (MovePart1(warehouse, playerPos, c, '@'))
			{
				warehouse[playerPos] = '.';
				playerPos += directions[c];
			}
		}
	}

	uint32_t result = GetTotalGPSCounter(warehouse);
	std::cout << "The solution is " << result << "!" << std::endl;
}

///////////////////////////////////////////////////////////////////////////
///
///////////////////////////////////////////////////////////////////////////

bool CheckMovePart2(Matrix<uint8_t>& wh, const Point2D& pos, const uint8_t dir, const bool isHorizDir)
{
	const Point2D newPos = pos + directions[dir];
	uint8_t& c = wh[newPos];
		switch (c)
	{
	case '.':
		return true;

	case '[':
		return CheckMovePart2(wh, newPos, dir, isHorizDir) && (isHorizDir || CheckMovePart2(wh, newPos + Point2D(1, 0), dir, isHorizDir));

	case ']':
		return CheckMovePart2(wh, newPos, dir, isHorizDir) && (isHorizDir || CheckMovePart2(wh, newPos + Point2D(-1, 0), dir, isHorizDir));

	default: // Unknown character or wall
		return false;
	}
}

void MovePart2(Matrix<uint8_t>& wh, const Point2D& pos, const uint8_t dir, const uint8_t prevChar, const bool isHorizDir);

void MoveNeighbour(Matrix<uint8_t>& wh, const Point2D& pos, const uint8_t dir, const uint8_t prevChar)
{
	const Point2D newPos = pos + directions[dir];
	uint8_t& c = wh[newPos];
	switch (c)
	{
	case '.':
		c = prevChar;
		break;

	case '[':
		MovePart2(wh, newPos, dir, c, false);
		c = prevChar;
		break;

	case ']':
		MovePart2(wh, newPos, dir, c, false);
		c = prevChar;
		break;
	}
}

void MovePart2(Matrix<uint8_t>& wh, const Point2D& pos, const uint8_t dir, const uint8_t prevChar, const bool isHorizDir)
{
	const Point2D newPos = pos + directions[dir];
	const Point2D newLPos = newPos + Point2D(-1, 0);
	const Point2D newRPos = newPos + Point2D( 1, 0);
	uint8_t& c = wh[newPos];
	switch (c)
	{
	case '.':
		c = prevChar;
		break;

	case '[':
		MovePart2(wh, newPos, dir, c, isHorizDir);
		if (!isHorizDir)
		{
			MoveNeighbour(wh, pos + Point2D(1, 0), dir, '.');
		}
		c = prevChar;
		break;

	case ']':
		MovePart2(wh, newPos, dir, c, isHorizDir);
		if (!isHorizDir)
		{
			MoveNeighbour(wh, pos + Point2D(-1, 0), dir, '.');
		}
		c = prevChar;
		break;
	}
}

void SolveDay15Part2()
{
	std::ifstream file("data/Day 15/Data.txt");
	if (!file || !file.is_open())
	{
		std::cout << "The solution is within your heart (DATA NOT FOUND!)." << std::endl;
		return;
	}

	Matrix<uint8_t> warehouse;

	size_t y = 0;
	std::string line;
	while (std::getline(file, line))
	{
		if (line.empty())
			break;

		warehouse.push_row();
		for (const uint8_t& c : line)
		{
			switch (c)
			{
			case '#':
				warehouse[y].push_back('#');
				warehouse[y].push_back('#');
				break;
			case 'O':
				warehouse[y].push_back('[');
				warehouse[y].push_back(']');
				break;
			case '.':
				warehouse[y].push_back('.');
				warehouse[y].push_back('.');
				break;
			case '@':
				warehouse[y].push_back('@');
				warehouse[y].push_back('.');
				break;
			}
		}

		y++;
	}


	// std::cout << "Initial state:" << std::endl;
	// std::cout << warehouse << std::endl;

	Point2D playerPos = warehouse.find_first_of('@');
	while (std::getline(file, line))
	{
		for (const uint8_t c : line)
		{
			const bool isHorizontalDir = c == '<' || c == '>';
			if (CheckMovePart2(warehouse, playerPos, c, isHorizontalDir))
			{
				MovePart2(warehouse, playerPos, c, '@', isHorizontalDir);
				warehouse[playerPos] = '.';
				playerPos += directions[c];
			}

			// std::cout << "Move " << c << ":" << std::endl;
			// std::cout << warehouse << std::endl;
		}
	}

	std::cout << warehouse << std::endl;

	uint32_t result = GetTotalGPSCounter(warehouse);
	std::cout << "The solution is " << result << "!" << std::endl;
}