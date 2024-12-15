#pragma once
#include "DaysCommon.h"

// Keeping the way I did it at first for reference
void SolveDay11Part1()
{
	std::ifstream file("data/Day 11/Data.txt");
	if (!file || !file.is_open())
	{
		std::cout << "The solution is within your heart (DATA NOT FOUND!)." << std::endl;
		return;
	}

	std::string line;
	std::getline(file, line);

	std::vector<uint64_t> stones;
	std::stringstream ss(line);
	std::string currStone;
	while (std::getline(ss, currStone, ' '))
		stones.push_back(std::stoull(currStone));

	if (stones.empty())
	{
		std::cout << "The solution is within your heart (NO STONES IN DATA!)." << std::endl;
		return;
	}

	auto printStones = [](const std::vector<uint64_t>& stones) {
		for (const uint64_t& currStone : stones)
			std::cout << currStone << " ";

		std::cout << std::endl;
	};

	auto stoneOnBlink = [](const uint64_t& stone, std::vector<uint64_t>& out) {
		if (stone == 0)
			out.push_back(1);
		else if (const std::string stoneStr = std::to_string(stone); stoneStr.size() % 2 == 0)
		{
			const std::string stoneLhs = stoneStr.substr(0, stoneStr.size() / 2);
			const std::string stoneRhs = stoneStr.substr(stoneStr.size() / 2, stoneStr.size());
			out.push_back(std::stoull(stoneLhs));
			out.push_back(std::stoull(stoneRhs));
		}
		else
		{
			out.push_back(stone * 2024);
		}
	};

	const uint16_t blinkCount = 25;
	for (uint16_t i = 0; i < blinkCount; i++)
	{
		std::vector<uint64_t> currResult;
		for (const uint64_t& currStone : stones)
		{
			stoneOnBlink(currStone, currResult);
		}

		stones = currResult;
	}

	size_t result = stones.size();
	std::cout << "The solution is " << result << "!" << std::endl;
}

///////////////////////////////////////////////////////////////////////////
///
///////////////////////////////////////////////////////////////////////////

// Dynamic programming solution
std::map<uint64_t, std::map<uint8_t, uint64_t>> stonesLookupTable;

uint64_t BlinkStone(const uint64_t stone, const uint8_t blinksLeft)
{
	uint64_t totalStones;
	if (stonesLookupTable.find(stone) != stonesLookupTable.end() && stonesLookupTable[stone].find(blinksLeft) != stonesLookupTable[stone].end())
		return stonesLookupTable[stone][blinksLeft];
	else if (blinksLeft == 0)
		totalStones = 1;
	else if (stone == 0)
		totalStones = BlinkStone(1, blinksLeft - 1);
	else if (const std::string stoneStr = std::to_string(stone); stoneStr.size() % 2 == 0)
	{
		const std::string stoneLhs = stoneStr.substr(0, stoneStr.size() / 2);
		const std::string stoneRhs = stoneStr.substr(stoneStr.size() / 2, stoneStr.size());
		totalStones = BlinkStone(std::stoull(stoneLhs), blinksLeft - 1) + BlinkStone(std::stoull(stoneRhs), blinksLeft - 1);
	}
	else
		totalStones = BlinkStone(stone * 2024, blinksLeft - 1);

	stonesLookupTable[stone][blinksLeft] = totalStones;
	return totalStones;
}

///////////////////////////////////////////////////////////////////////////
///
///////////////////////////////////////////////////////////////////////////

void SolveDay11Part2()
{
	std::ifstream file("data/Day 11/Data.txt");
	if (!file || !file.is_open())
	{
		std::cout << "The solution is within your heart (DATA NOT FOUND!)." << std::endl;
		return;
	}

	std::string line;
	std::getline(file, line);


	std::vector<std::string> stones;
	std::stringstream ss(line);
	std::string currStone;
	while (std::getline(ss, currStone, ' '))
		stones.push_back(currStone);

	if (stones.empty())
	{
		std::cout << "The solution is within your heart (NO STONES IN DATA!)." << std::endl;
		return;
	}

	auto printStones = [](const std::vector<uint64_t>& stones) {
		for (const uint64_t& currStone : stones)
			std::cout << currStone << " ";

		std::cout << std::endl;
		};

	size_t result = 0;
	const uint16_t blinkCount = 75;
	for (const std::string& currStone : stones)
		result += BlinkStone(std::stoull(currStone), blinkCount);

	std::cout << "The solution is " << result << "!" << std::endl;
}