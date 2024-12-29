#pragma once
#include "DaysCommon.h"

using InstructionMap = std::unordered_map<uint8_t, std::unordered_map<uint8_t, std::string>>;

using InstructionData = std::unordered_map<uint8_t, InstructionMap>;

using InstructionPositions = std::unordered_map<uint8_t, Point2D>;

InstructionPositions GetNumericPositions()
{
	InstructionPositions numericPositions = {
		{ '7', Point2D() },
		{ '8', Point2D(1, 0) },
		{ '9', Point2D(2, 0) },
		{ '4', Point2D(0, 1) },
		{ '5', Point2D(1, 1) },
		{ '6', Point2D(2, 1) },
		{ '1', Point2D(0, 2) },
		{ '2', Point2D(1, 2) },
		{ '3', Point2D(2, 2) },
		{ '0', Point2D(1, 3) },
		{ 'A', Point2D(2, 3) },
	};

	return numericPositions;
}

std::string DirectionsToStr(const std::vector<Point2D>& directions)
{
	std::string result;
	for (const Point2D& dir : directions)
	{
		const uint8_t hChar = dir.x < 0 ? '<' : '>';
		const uint8_t vChar = dir.y < 0 ? '^' : 'v';
		const uint8_t hMax = std::abs(dir.x);
		const uint8_t vMax = std::abs(dir.y);

		for (uint8_t i = 0; i < hMax; i++)
			result.push_back(hChar);
		for (uint8_t i = 0; i < vMax; i++)
			result.push_back(vChar);

		result.push_back('A');
	}

	return result;
}

InstructionMap GetDirectionalPositions()
{
	/*InstructionPositions directionalPositions = {
		{ '<', Point2D() },
		{ 'v', Point2D(0, 1) },
		{ '^', Point2D(1, 1) },
		{ '>', Point2D(2, 0) },
		{ 'A', Point2D(2, 1) }
	};*/
	InstructionMap directionalMap;
	directionalMap['^']['^'] = "";
	directionalMap['^']['<'] = "v<";
	directionalMap['^']['v'] = "v";
	directionalMap['^']['>'] = "v>";
	directionalMap['^']['A'] = ">";

	directionalMap['<']['^'] = ">^";
	directionalMap['<']['<'] = "";
	directionalMap['<']['v'] = ">";
	directionalMap['<']['>'] = ">>";
	directionalMap['<']['A'] = ">>^";

	directionalMap['v']['^'] = "^";
	directionalMap['v']['<'] = "<";
	directionalMap['v']['v'] = "";
	directionalMap['v']['>'] = ">";
	directionalMap['v']['A'] = ">^";

	directionalMap['>']['^'] = "<^";
	directionalMap['>']['<'] = "<<";
	directionalMap['>']['v'] = "<";
	directionalMap['>']['>'] = "";
	directionalMap['>']['A'] = "^";

	directionalMap['A']['^'] = "<";
	directionalMap['A']['<'] = "v<<";
	directionalMap['A']['v'] = "<v";
	directionalMap['A']['>'] = "v";
	directionalMap['A']['A'] = "";

	return directionalMap;
}

bool IsValueInTable(const uint8_t from, const uint8_t to, const uint32_t itCount, InstructionData& dpTable)
{
	return dpTable.find(itCount) != dpTable.end() &&
		dpTable[itCount].find(from) != dpTable[itCount].end() &&
		dpTable[itCount][from].find(to) != dpTable[itCount][from].end();
}

std::string GetSequence(const uint8_t from, const uint8_t to, const uint32_t itCount, InstructionMap& dirPos, InstructionData& dpTable)
{
	if (IsValueInTable(from, to, itCount, dpTable))
		return dpTable[itCount][from][to];

	if (itCount == 0)
		return dirPos[from][to] + 'A';

	std::string result;
	uint8_t currC = 'A';
	std::string currSeq = dirPos[from][to];
	for (const uint8_t& c : currSeq)
	{
		result += GetSequence(currC, c, itCount - 1, dirPos, dpTable);
		currC = c;
	}
	dpTable[itCount][from][to] = result;

	return result;
}

void SolveDay21Part1()
{
	std::ifstream file("data/Day 21/Data.txt");
	if (!file || !file.is_open())
	{
		std::cout << "The solution is within your heart (DATA NOT FOUND!)." << std::endl;
		return;
	}

	InstructionPositions numPos = GetNumericPositions();
	InstructionMap dirPos = GetDirectionalPositions();
	InstructionData dpTable;

	uint32_t recursionCount = 1;

	uint64_t result = 0;
	std::string line;
	while (std::getline(file, line))
	{
		uint64_t val;
		std::istringstream iss(line);
		iss >> val;
		
		uint8_t currChar = 'A';
		std::vector<Point2D> directions;
		for (const uint8_t c : line)
		{
			Point2D currDir = numPos[c] - numPos[currChar];
			directions.push_back(currDir);
			currChar = c;
		}

		currChar = 'A';
		for (recursionCount = 0; recursionCount < 3; recursionCount++)
		{
			std::string currResult;
			std::string numCommands = DirectionsToStr(directions);
			if (recursionCount == 0)
				currResult = numCommands;
			else
			{
				for (const uint8_t& c : numCommands)
				{
					currResult += GetSequence(currChar, c, recursionCount - 1, dirPos, dpTable);
					currChar = c;
				}
			}

			std::cout << currResult << std::endl;
			uint64_t strSize = currResult.size();
			std::cout << strSize << " * " << val << " = " << strSize * val << std::endl;
			result += strSize * val;
		}

	}

	std::cout << "The solution is " << result << "!" << std::endl;
}

///////////////////////////////////////////////////////////////////////////
///
///////////////////////////////////////////////////////////////////////////

void SolveDay21Part2()
{
	std::ifstream file("data/Day 21/Data.txt");
	if (!file || !file.is_open())
	{
		std::cout << "The solution is within your heart (DATA NOT FOUND!)." << std::endl;
		return;
	}


	std::string line;
	while (std::getline(file, line))
	{
	}

	uint32_t result = 0;
	std::cout << "The solution is " << result << "!" << std::endl;
}