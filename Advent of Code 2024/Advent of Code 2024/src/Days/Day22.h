#pragma once
#include "DaysCommon.h"

uint64_t secretNumber = 123;

inline uint64_t mix(const uint64_t val)
{
	secretNumber ^= val;
	return secretNumber;
}

inline uint64_t prune(const uint64_t val)
{
	secretNumber = val % 16777216;
	return secretNumber;
}

inline uint64_t GetNextNumber()
{
	mix(secretNumber * 64);
	prune(secretNumber);

	mix(secretNumber / 32);
	prune(secretNumber);

	mix(secretNumber * 2048);
	prune(secretNumber);

	return secretNumber;
}

void SolveDay22Part1()
{
	std::ifstream file("data/Day 22/Data.txt");
	if (!file || !file.is_open())
	{
		std::cout << "The solution is within your heart (DATA NOT FOUND!)." << std::endl;
		return;
	}

	uint64_t result = 0;

	std::string line;
	while (std::getline(file, line))
	{
		std::istringstream iss(line);
		iss >> secretNumber;
		for (uint32_t i = 0; i < 2000; i++)
			GetNextNumber();

		result += secretNumber;
	}

	std::cout << "The solution is " << result << "!" << std::endl;
}

///////////////////////////////////////////////////////////////////////////
///
///////////////////////////////////////////////////////////////////////////

using MarketTable = std::unordered_map<int8_t, std::unordered_map<int8_t, std::unordered_map<int8_t, std::unordered_map<int8_t, uint8_t>>>>;

bool IsSequenceInTable(MarketTable& table, const std::array<int8_t, 4>& seq)
{
	const int8_t aVal = seq[0];
	const int8_t bVal = seq[1];
	const int8_t cVal = seq[2];
	const int8_t dVal = seq[3];

	return	table.find(aVal) != table.end() &&
		table[aVal].find(bVal) != table[aVal].end() &&
		table[aVal][bVal].find(cVal) != table[aVal][bVal].end() &&
		table[aVal][bVal][cVal].find(dVal) != table[aVal][bVal][cVal].end();
}

void SetSequenceToTable(MarketTable& table, const std::array<int8_t, 4>& seq, uint8_t val)
{
	const int8_t aVal = seq[0];
	const int8_t bVal = seq[1];
	const int8_t cVal = seq[2];
	const int8_t dVal = seq[3];

	table[aVal][bVal][cVal][dVal] = val;
}

MarketTable GetSequencesFromNumber(const uint64_t num)
{
	MarketTable result;
	secretNumber = num;
	int8_t prevNum = num % 10;

	std::array<int8_t, 4> lastSeq;
	for (uint32_t i = 0; i < 2000; i++)
	{
		for (uint8_t j = lastSeq.size() - 1; j > 0; j--)
			lastSeq[j] = lastSeq[j - 1];

		int32_t num = GetNextNumber() % 10;
		lastSeq[0] = num - prevNum;
		prevNum = num;

		if (i >= 4 && !IsSequenceInTable(result, lastSeq))
			SetSequenceToTable(result, lastSeq, num);
	}

	return result;
}


uint32_t GetValueFromTables(std::vector<MarketTable>& tableList,
	const int8_t aVal, const int8_t bVal, const int8_t cVal, const int8_t dVal)
{
	uint32_t result = 0;
	for (MarketTable& table : tableList)
		result += table[aVal][bVal][cVal][dVal];

	return result;
}

uint32_t GetMostBananas(std::vector<MarketTable>& tables)
{
	uint32_t maxValue = 0;
	for (int8_t a = -9; a < 10; a++)
	{
		for (int8_t b = -9; b < 10; b++)
		{
			for (int8_t c = -9; c < 10; c++)
			{
				for (int8_t d = -9; d < 10; d++)
				{
					maxValue = std::max(maxValue, GetValueFromTables(tables, a, b, c, d));
				}
			}
		}
	}

	return maxValue;
}

void SolveDay22Part2()
{
	std::ifstream file("data/Day 22/Data.txt");
	if (!file || !file.is_open())
	{
		std::cout << "The solution is within your heart (DATA NOT FOUND!)." << std::endl;
		return;
	}

	std::vector<MarketTable> seqTable;

	std::string line;
	while (std::getline(file, line))
	{
		std::istringstream iss(line);
		iss >> secretNumber;
		std::cout << secretNumber << std::endl;
		seqTable.push_back(GetSequencesFromNumber(secretNumber));
	}

	std::cout << "Computing..." << std::endl;
	uint32_t result = GetMostBananas(seqTable);
	std::cout << "The solution is " << result << "!" << std::endl;
}