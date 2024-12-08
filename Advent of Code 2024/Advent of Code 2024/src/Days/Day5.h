#pragma once
#include "DaysCommon.h"

using PageNodeOrders = std::map<uint32_t, bool>;
using PageOrders = std::map<uint32_t, PageNodeOrders>;

bool IsPageSorted(const std::vector<uint32_t>& vec, const PageOrders& orders)
{
	for (uint32_t i = 0; i < vec.size(); i++)
	{
		for (uint32_t j = i + 1; j < vec.size(); j++)
		{
			if (orders.find(vec[i])->second.find(vec[j])->second)
				return false;
		}
	}

	return true;
}

void SolveDay5Part1()
{
	std::ifstream file("data/Day 5/Data.txt");
	if (!file || !file.is_open())
	{
		std::cout << "The solution is within your heart (DATA NOT FOUND!)." << std::endl;
		return;
	}

	PageOrders pageOrders;
	std::string line;
	while (std::getline(file, line))
	{
		const size_t linePos = line.find('|');

		if (linePos == std::string::npos)
			break;

		uint32_t lNum = std::stoi(line.substr(0, linePos));
		uint32_t rNum = std::stoi(line.substr(linePos + 1));

		pageOrders[lNum][rNum] = false;
		pageOrders[rNum][lNum] = true;
	}


	auto findAllNumberaInLineSeparatedBy = [](const std::string& line, const char c) -> std::vector<uint32_t> {
		std::vector<uint32_t> values;
		std::stringstream ss(line);
		std::string currValue;
		while (std::getline(ss, currValue, c))
		{
			values.push_back(std::stoi(currValue));
		}
		return values;
	};

	uint32_t totalSum = 0;
	while (std::getline(file, line))
	{
		std::vector<uint32_t> values = findAllNumberaInLineSeparatedBy(line, ',');
		if (IsPageSorted(values, pageOrders))
			totalSum += values[values.size() / 2];
	}


	std::cout << "The solution is " << totalSum << "!" << std::endl;
}

///////////////////////////////////////////////////////////////////////////
///
///////////////////////////////////////////////////////////////////////////

void SolveDay5Part2()
{
	std::ifstream file("data/Day 5/Data.txt");
	if (!file || !file.is_open())
	{
		std::cout << "The solution is within your heart (DATA NOT FOUND!)." << std::endl;
		return;
	}

	PageOrders pageOrders;
	std::string line;
	while (std::getline(file, line))
	{
		const size_t linePos = line.find('|');

		if (linePos == std::string::npos)
			break;

		uint32_t lNum = std::stoi(line.substr(0, linePos));
		uint32_t rNum = std::stoi(line.substr(linePos + 1));

		pageOrders[lNum][rNum] = false;
		pageOrders[rNum][lNum] = true;
	}


	auto findAllNumberaInLineSeparatedBy = [](const std::string& line, const char c) -> std::vector<uint32_t> {
		std::vector<uint32_t> values;
		std::stringstream ss(line);
		std::string currValue;
		while (std::getline(ss, currValue, c))
		{
			values.push_back(std::stoi(currValue));
		}
		return values;
		};

	uint32_t totalSum = 0;
	while (std::getline(file, line))
	{
		std::vector<uint32_t> values = findAllNumberaInLineSeparatedBy(line, ',');
		if (!IsPageSorted(values, pageOrders))
		{
			std::sort(values.begin(), values.end(), [&pageOrders](const uint32_t lhs, const uint32_t rhs) {
				return pageOrders[rhs][lhs];
				});

			totalSum += values[values.size() / 2];
		}
	}

	std::cout << "The solution is " << totalSum << "!" << std::endl;
}
