#pragma once
#include "DaysCommon.h"


bool IsComputablePart1(const uint64_t result, const uint64_t currVal, const std::vector<uint64_t>& addends, const size_t idx)
{
	if (currVal > result)
		return false;

	if (idx == addends.size())
	{
		return currVal == result;
	}

	const uint64_t mulVal = currVal * addends[idx];
	if (IsComputablePart1(result, mulVal, addends, idx + 1))
		return true;

	const uint64_t addVal = currVal + addends[idx];
	if (IsComputablePart1(result, addVal, addends, idx + 1))
		return true;

	return false;
}

///////////////////////////////////////////////////////////////////////////
///
///////////////////////////////////////////////////////////////////////////

void SolveDay7Part1()
{
	std::ifstream file("data/Day 7/Data.txt");
	if (!file || !file.is_open())
	{
		std::cout << "The solution is within your heart (DATA NOT FOUND!)." << std::endl;
		return;
	}

	uint64_t result = 0;

	std::string line;
	while (std::getline(file, line))
	{
		std::istringstream ss(line);
		uint64_t target; ss >> target;

		size_t colon_pos = line.find(':');
		std::string addendsStr(line.begin() + colon_pos + 1, line.end());

		uint64_t num;
		std::vector<uint64_t> addendList;
		ss = std::istringstream(addendsStr);
		while (ss >> num)
		{
			addendList.push_back(num);
		}

		if (IsComputablePart1(target, addendList[0], addendList, 1))
		{
			result += target;
		}
	}

	std::cout << "The solution is " << result << "!" << std::endl;
}

///////////////////////////////////////////////////////////////////////////
///
///////////////////////////////////////////////////////////////////////////

bool IsComputablePart2(const uint64_t result, const uint64_t currVal, const std::vector<uint64_t>& addends, const size_t idx)
{
	if (currVal > result)
		return false;

	if (idx == addends.size())
	{
		return currVal == result;
	}

	const uint64_t mulVal = currVal * addends[idx];
	if (IsComputablePart2(result, mulVal, addends, idx + 1))
		return true;

	const uint64_t addVal = currVal + addends[idx];
	if (IsComputablePart2(result, addVal, addends, idx + 1))
		return true;

	const std::string lhsStr = std::to_string(currVal);
	const std::string rhsStr = std::to_string(addends[idx]);
	const uint64_t concatVal = std::stoll(lhsStr + rhsStr);
	if (IsComputablePart2(result, concatVal, addends, idx + 1))
		return true;

	return false;
}

///////////////////////////////////////////////////////////////////////////
///
///////////////////////////////////////////////////////////////////////////

void SolveDay7Part2()
{
	std::ifstream file("data/Day 7/Data.txt");
	if (!file || !file.is_open())
	{
		std::cout << "The solution is within your heart (DATA NOT FOUND!)." << std::endl;
		return;
	}

	uint64_t result = 0;

	std::string line;
	while (std::getline(file, line))
	{
		std::istringstream ss(line);
		uint64_t target; ss >> target;

		size_t colon_pos = line.find(':');
		std::string addendsStr(line.begin() + colon_pos + 1, line.end());

		uint64_t num;
		std::vector<uint64_t> addendList;
		ss = std::istringstream(addendsStr);
		while (ss >> num)
		{
			addendList.push_back(num);
		}

		if (IsComputablePart2(target, addendList[0], addendList, 1))
		{
			result += target;
		}
	}

	std::cout << "The solution is " << result << "!" << std::endl;
}