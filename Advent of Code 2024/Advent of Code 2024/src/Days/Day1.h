#pragma once
#include "DaysCommon.h"

void SolveDay1Part1()
{
	std::ifstream file("data/Day 1/Data.txt");
	if (!file || !file.is_open())
	{
		std::cout << "The solution is within your heart (DATA NOT FOUND!)." << std::endl;
		return;
	}

	std::multiset<int32_t> leftList;
	std::multiset<int32_t> rightList;

	std::string line;
	while (std::getline(file, line))
	{
		std::istringstream integerStream(line);

		int32_t numL;
		int32_t numR;
		integerStream >> numL;
		integerStream >> numR;

		leftList.insert(numL);
		rightList.insert(numR);
	}

	if (leftList.size() != rightList.size())
	{
		std::cout << "The solution is within your heart (LIST SIZES ARE NOT THE SAME!)." << std::endl;
		return;
	}

	int32_t totalDiff = 0;
	auto itL = leftList.begin();
	auto itR = rightList.begin();
	while (itL != leftList.end()) // Only one comparison since both multisets are the same size.
	{
		totalDiff += std::abs(*itL - *itR);

		itL++;
		itR++;
	}

	std::cout << "The solution is " << totalDiff << "!" << std::endl;
}

///////////////////////////////////////////////////////////////////////////
///
///////////////////////////////////////////////////////////////////////////

void SolveDay1Part2()
{
	std::ifstream file("data/Day 1/Data.txt");
	if (!file || !file.is_open())
	{
		std::cout << "The solution is within your heart (DATA NOT FOUND!)." << std::endl;
		return;
	}

	std::vector<int32_t> leftList;
	std::map<int32_t, uint32_t> similarityMap;

	std::string line;
	while (std::getline(file, line))
	{
		std::istringstream integerStream(line);

		int32_t numL;
		int32_t numR;
		integerStream >> numL;
		integerStream >> numR;

		if (!similarityMap.contains(numR))
		{
			similarityMap[numR] = 0;
		}

		similarityMap[numR]++;
		leftList.push_back(numL);
	}

	uint32_t similarityScore = 0;
	for (int32_t currNum : leftList)
	{
		if (!similarityMap.contains(currNum))
		{
			continue;
		}

		similarityScore += currNum * similarityMap[currNum];
	}

	std::cout << "The solution is " << similarityScore << "!" << std::endl;
}