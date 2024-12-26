#pragma once
#include "DaysCommon.h"

void SolveDayXPart1()
{
	std::ifstream file("data/Day X/Data.txt");
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

///////////////////////////////////////////////////////////////////////////
///
///////////////////////////////////////////////////////////////////////////

void SolveDayXPart2()
{
	std::ifstream file("data/Day X/Data.txt");
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