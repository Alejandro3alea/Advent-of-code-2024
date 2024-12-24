#pragma once
#include "DaysCommon.h"

void SolveDay15Part1()
{
	std::ifstream file("data/Day 15/Data.txt");
	if (!file || !file.is_open())
	{
		std::cout << "The solution is within your heart (DATA NOT FOUND!)." << std::endl;
		return;
	}

	uint32_t result = 0;
	Matrix<uint8_t> warehouse;

	std::string line;
	while (std::getline(file, line))
	{
		if (line.empty())
			break;

		warehouse.push_row({ line.begin(), line.end() });
	}

	std::string line;
	while (std::getline(file, line))
	{
		if (line.empty())
			break;

		warehouse.push_row({ line.begin(), line.end() });
	}

	//std::cout << warehouse << std::endl;
	std::cout << "The solution is " << result << "!" << std::endl;
}

///////////////////////////////////////////////////////////////////////////
///
///////////////////////////////////////////////////////////////////////////

void SolveDay15Part2()
{
	std::ifstream file("data/Day 15/Data.txt");
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