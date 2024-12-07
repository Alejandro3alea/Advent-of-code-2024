#pragma once
#include "DaysCommon.h"

void SolveDay4Part1()
{
	std::ifstream file("data/Day 4/Data.txt");
	if (!file || !file.is_open())
	{
		std::cout << "The solution is within your heart (DATA NOT FOUND!)." << std::endl;
		return;
	}

	uint32_t totalSum = 0;
	std::string line;
	while (std::getline(file, line))
	{
	}

	std::cout << "The solution is " << totalSum << "!" << std::endl;
}

///////////////////////////////////////////////////////////////////////////
///
///////////////////////////////////////////////////////////////////////////
