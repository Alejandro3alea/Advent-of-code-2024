#pragma once
#include "DaysCommon.h"

void SolveDay7Part1()
{
	std::ifstream file("data/Day 7/Data.txt");
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

	uint32_t result = 0;

	std::string line;
	while (std::getline(file, line))
	{
	}

	std::cout << "The solution is " << result << "!" << std::endl;
}