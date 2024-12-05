#pragma once
#include "DaysCommon.h"

enum class SafeMethod {
	eNone,
	eAscending,
	eDescending
};

void SolveDay2Part1()
{
	std::ifstream file("data/Day 2/Data.txt");
	if (!file || !file.is_open())
	{
		std::cout << "The solution is within your heart (DATA NOT FOUND!)." << std::endl;
		return;
	}

	uint32_t safeCount = 0;

	std::string line;
	while (std::getline(file, line))
	{
		std::istringstream integerStream(line);

		SafeMethod safeMethod = SafeMethod::eNone;

		int prevNum; integerStream >> prevNum;
		int num;

		bool isSafe = true;
		while (integerStream >> num)
		{
			int diff = std::abs(prevNum - num);
			if (diff > 3 || diff == 0)
			{
				isSafe = false;
				break;
			}

			if (prevNum < num)
			{
				if (safeMethod == SafeMethod::eDescending)
				{
					isSafe = false;
					break;
				}
				safeMethod = SafeMethod::eAscending;
			}
			else
			{
				if (safeMethod == SafeMethod::eAscending)
				{
					isSafe = false;
					break;
				}
				safeMethod = SafeMethod::eDescending;
			}

			prevNum = num;
		}

		if (isSafe)
		{
			safeCount++;
		}
	}

	std::cout << "The solution is " << safeCount << "!" << std::endl;
}

///////////////////////////////////////////////////////////////////////////
////
///////////////////////////////////////////////////////////////////////////

// Dynamic programming solution
bool isSequenceValid(const std::vector<int32_t>& values, const int32_t prevIndex,
	const int32_t currIndex, const bool skip, const SafeMethod method)
{
	if (currIndex == values.size())
	{
		return true;
	}

	int32_t prevValue = values[prevIndex];
	int32_t currValue = values[currIndex];
	bool isNotValid = (method == SafeMethod::eAscending && prevValue <= currValue) ||
		(method == SafeMethod::eDescending && prevValue >= currValue) ||
		std::abs(prevValue - currValue) > 3;
	if (!isNotValid)
	{
		return isSequenceValid(values, currIndex, currIndex + 1, skip, method);
	}
	else if (skip)
	{
		return false;
	}
	else if (isSequenceValid(values, prevIndex, currIndex + 1, true, method))
	{
		return true;
	}
	else
	{
		int32_t lIndex = (prevIndex - 1 >= 0) ? prevIndex - 1 : currIndex;
		int32_t rIndex = (prevIndex - 1 >= 0) ? currIndex : currIndex + 1;

		return isSequenceValid(values, lIndex, rIndex, true, method);
	}
}

///////////////////////////////////////////////////////////////////////////
////
///////////////////////////////////////////////////////////////////////////

void SolveDay2Part2()
{
	std::ifstream file("data/Day 2/Data.txt");
	if (!file || !file.is_open())
	{
		std::cout << "The solution is within your heart (DATA NOT FOUND!)." << std::endl;
		return;
	}

	uint32_t safeCount = 0;

	std::string line;
	while (std::getline(file, line))
	{
		std::istringstream integerStream(line);

		int32_t num;
		std::vector<int32_t> numberList;
		while (integerStream >> num)
		{
			numberList.push_back(num);
		}

		if (isSequenceValid(numberList, 0, 1, false, SafeMethod::eAscending) ||
			isSequenceValid(numberList, 0, 1, false, SafeMethod::eDescending))
		{
			safeCount++;
		}
	}

	std::cout << "The solution is " << safeCount << "!" << std::endl;
}