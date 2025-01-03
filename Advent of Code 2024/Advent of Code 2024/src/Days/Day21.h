#pragma once
#include "DaysCommon.h"

using InstructionMap = std::unordered_map<uint8_t, std::unordered_map<uint8_t, std::string>>;
using InstructionData = std::unordered_map<uint8_t, std::unordered_map<uint8_t, std::unordered_map<uint8_t, uint64_t>>>;
using InstructionPositions = std::unordered_map<uint8_t, Point2D>;

InstructionMap GetDirectionalPositions()
{
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

	directionalMap['>']['^'] = "^<";
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

InstructionMap GetAlternativeDirectionalPositions()
{
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
	directionalMap['<']['A'] = ">^>";

	directionalMap['v']['^'] = "^";
	directionalMap['v']['<'] = "<";
	directionalMap['v']['v'] = "";
	directionalMap['v']['>'] = ">";
	directionalMap['v']['A'] = ">^";

	directionalMap['>']['^'] = "^<";
	directionalMap['>']['<'] = "<<";
	directionalMap['>']['v'] = "<";
	directionalMap['>']['>'] = "";
	directionalMap['>']['A'] = "^";

	directionalMap['A']['^'] = "<";
	directionalMap['A']['<'] = "<v<";
	directionalMap['A']['v'] = "<v";
	directionalMap['A']['>'] = "v";
	directionalMap['A']['A'] = "";

	return directionalMap;
}

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

/*
* From: https://www.reddit.com/r/adventofcode/comments/1hja685/2024_day_21_here_are_some_examples_and_hints_for/
Line 4: 379A
v<<A^>>AvA^Av<A<AA^>>AAvA^<A>AAvA^Av<A^>AA<A>Av<<A>A^>AAAvA^<A>A
   <   A > A  v <<   AA >  ^ AA > A  v  AA ^ A   < v  AAA >  ^ A
	   ^   A         <<      ^^   A     >>   A        vvv      A
		   3                      7          9                 A
string length=64
Complexity: 379 x 64 = 24256

Line 4: 379A
v<<A^>>AvA^Av<<A^>>AAv<A<A^>>AAvAA^<A>Av<A^>AA<A>Av<A<A^>>AAA<Av>A^A
   <   A > A   <   AA  v <   AA >>  ^ A  v  AA ^ A  v <   AAA ^  > A
	   ^   A       ^^        <<       A     >>   A        vvv      A
		   3                          7          9                 A
string length=68
Complexity: 379 x 68 = 25772
*/
std::vector<std::string> GetPossibleCombinations(const std::string& str, InstructionPositions& numPos)
{
	std::vector<std::string> possibleCombinations;

	const uint8_t maxComboVal = 0b10000;
	for (uint8_t comboVal = 0; comboVal < maxComboVal; comboVal++)
	{
		bool isValidCombination = true;
		std::string combination;

		uint8_t prevC = 'A';
		for (uint8_t cIdx = 0; cIdx < str.size(); cIdx++)
		{
			const uint8_t& c = str[cIdx];
			if (prevC == c)
			{
				combination.push_back('A');
				continue;
			}

			const Point2D startPos = numPos[prevC];
			const Point2D endPos = numPos[c];
			const Point2D dir = endPos - startPos;

			const uint8_t hChar = dir.x < 0 ? '<' : '>';
			const uint8_t vChar = dir.y < 0 ? '^' : 'v';
			const uint8_t hMax = std::abs(dir.x);
			const uint8_t vMax = std::abs(dir.y);

			// Corner case to avoid hitting OOB
			auto doesGoOOB = [&](bool isCheckStart) {
				return (isCheckStart && startPos.x + dir.x == 0 && startPos.y == 3) || // Either 0 or A go to a left number
					(!isCheckStart && dir.x > 0 && startPos.x == 0 && endPos.y == 3); // Either a left number goes to 0 or A
			};


			std::string currResult;
			bool comboBit = comboVal & 1 << cIdx;
			if (comboBit && !doesGoOOB(true))
			{
				for (uint8_t i = 0; i < hMax; i++)
					currResult.push_back(hChar);
				for (uint8_t i = 0; i < vMax; i++)
					currResult.push_back(vChar);
			}

			// Swapped order
			else if (!comboBit && !doesGoOOB(false))
			{
				for (uint8_t i = 0; i < vMax; i++)
					currResult.push_back(vChar);
				for (uint8_t i = 0; i < hMax; i++)
					currResult.push_back(hChar);
			}

			if (currResult.empty())
			{
				isValidCombination = false;
				break;
			}

			combination += currResult;
			combination.push_back('A');

			prevC = c;
		}

		if (isValidCombination)
			possibleCombinations.push_back(combination);
	}

	return possibleCombinations;
}



InstructionPositions numPos = GetNumericPositions();
InstructionMap dirPos = GetDirectionalPositions();
InstructionMap altDirPos = GetAlternativeDirectionalPositions();

bool IsValueInTable(const uint8_t from, const uint8_t to, const uint32_t itCount, InstructionData& dpTable)
{
	return dpTable.find(itCount) != dpTable.end() &&
		dpTable[itCount].find(from) != dpTable[itCount].end() &&
		dpTable[itCount][from].find(to) != dpTable[itCount][from].end();
}

int64_t GetSequenceCount(const uint8_t from, const uint8_t to, const uint32_t itCount, InstructionMap& dirTable, InstructionData& dpTable)
{
	if (IsValueInTable(from, to, itCount, dpTable))
		return dpTable[itCount][from][to];

	if (itCount == 0)
		return dirTable[from][to].size() + 1;

	int64_t result = 0;
	uint8_t currC = 'A';
	std::string currSeq = dirTable[from][to] + 'A';
	for (const uint8_t& c : currSeq)
	{
		int64_t currVal = GetSequenceCount(currC, c, itCount - 1, dirPos, dpTable);
		int64_t altVal = GetSequenceCount(currC, c, itCount - 1, altDirPos, dpTable);
		result += std::min(currVal, altVal);
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

	InstructionData dpTable;

	uint32_t recursionCount = 2;

	uint64_t result = 0;
	std::string line;
	while (std::getline(file, line))
	{
		uint64_t val;
		std::istringstream iss(line);
		iss >> val;

		uint64_t minMoves = std::numeric_limits<uint64_t>::max();
		std::vector<std::string> combinations = GetPossibleCombinations(line, numPos);
		for (const std::string& numCommands : combinations)
		{
			uint8_t currChar = 'A';
			uint64_t currResult = 0;
			if (recursionCount == 0)
				currResult = numCommands.size();
			else
			{
				for (const uint8_t& c : numCommands)
				{
					currResult += GetSequenceCount(currChar, c, recursionCount - 1, dirPos, dpTable);
					currChar = c;
				}
			}

			minMoves = std::min(minMoves, currResult);
		}

		std::cout << minMoves << " * " << val << " = " << minMoves * val << std::endl;
		result += minMoves * val;
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

	InstructionData dpTable;

	uint32_t recursionCount = 25;

	uint64_t result = 0;
	std::string line;
	while (std::getline(file, line))
	{
		uint64_t val;
		std::istringstream iss(line);
		iss >> val;

		uint64_t minMoves = std::numeric_limits<uint64_t>::max();
		std::vector<std::string> combinations = GetPossibleCombinations(line, numPos);
		for (const std::string& numCommands : combinations)
		{
			uint8_t currChar = 'A';
			uint64_t currResult = 0;
			if (recursionCount == 0)
				currResult = numCommands.size();
			else
			{
				for (const uint8_t& c : numCommands)
				{
					currResult += GetSequenceCount(currChar, c, recursionCount - 1, dirPos, dpTable);
					currChar = c;
				}
			}

			minMoves = std::min(minMoves, currResult);
		}

		std::cout << minMoves << " * " << val << " = " << minMoves * val << std::endl;
		result += minMoves * val;
	}

	std::cout << "The solution is " << result << "!" << std::endl;
}
