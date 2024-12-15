#pragma once
#include "DaysCommon.h"

#define EMPTY_SPACE -1

void SolveDay9Part1()
{
	std::ifstream file("data/Day 9/Data.txt");
	if (!file || !file.is_open())
	{
		std::cout << "The solution is within your heart (DATA NOT FOUND!)." << std::endl;
		return;
	}

	std::string line;
	std::getline(file, line);
	if ((line.size() / 2) > std::numeric_limits<int16_t>::max())
	{
		std::cout << "The solution is within your heart (SAMPLE SIZE IS TOO BIG!)." << std::endl;
		return;
	}

	bool isEmptySpace = false;
	int16_t currIdx = 0;
	std::vector<int16_t> disk;
	for (const uint8_t count : line)
	{
		int16_t currVal = EMPTY_SPACE;
		if (!isEmptySpace)
		{
			currVal = currIdx;
			currIdx++;
		}

		disk.insert(disk.end(), count - '0', currVal);
		isEmptySpace = !isEmptySpace;
	}

	auto printDisk = [](const std::vector<int16_t>& disk) -> void {
		for (const int16_t& val : disk)
		{
			if (val == EMPTY_SPACE)
			{
				std::cout << ".";
			}
			else
			{
				std::cout << val;
			}
		}

		std::cout << std::endl;
	};


	auto findFirstEmptySpaceOf = [](const std::vector<int16_t>& disk) -> size_t {
		auto it = std::find(disk.begin(), disk.end(), EMPTY_SPACE);
		if (it != disk.end())
			return std::distance(disk.begin(), it);

		return std::numeric_limits<size_t>::max();
	};


	size_t diskRightIdx = disk.size() - 1;
	size_t firstEmptySpace = findFirstEmptySpaceOf(disk);
	while (diskRightIdx > firstEmptySpace)
	{
		const int16_t& val = disk[diskRightIdx];
		if (val != EMPTY_SPACE)
		{
			disk[firstEmptySpace] = val;
			disk[diskRightIdx] = EMPTY_SPACE;
			firstEmptySpace = findFirstEmptySpaceOf(disk);
		}

		diskRightIdx--;
	}


	auto getChecksum = [](const std::vector<int16_t>& disk) -> uint64_t {
		uint64_t result = 0u;
		for (int64_t idx = 1; idx < disk.size(); idx++)
		{
			const int64_t& currVal = disk[idx];
			if (currVal == EMPTY_SPACE)
				return result;

			result += idx * currVal;
		}

		return result;
	};

	uint64_t result = getChecksum(disk);
	std::cout << "The solution is " << result << "!" << std::endl;
}

///////////////////////////////////////////////////////////////////////////
///
///////////////////////////////////////////////////////////////////////////

void SolveDay9Part2()
{
	std::ifstream file("data/Day 9/Data.txt");
	if (!file || !file.is_open())
	{
		std::cout << "The solution is within your heart (DATA NOT FOUND!)." << std::endl;
		return;
	}

	std::string line;
	std::getline(file, line);
	if ((line.size() / 2) > std::numeric_limits<int16_t>::max())
	{
		std::cout << "The solution is within your heart (SAMPLE SIZE IS TOO BIG!)." << std::endl;
		return;
	}

	bool isEmptySpace = false;
	int16_t currIdx = 0;
	using DiskBlockData = std::pair<int16_t, uint8_t>;
	std::vector<DiskBlockData> disk; // 1st val = idx, 2nd val = count
	for (const uint8_t count : line)
	{
		int16_t currVal = EMPTY_SPACE;
		if (!isEmptySpace)
		{
			currVal = currIdx;
			currIdx++;
		}

		disk.push_back({ currVal, count - '0' });
		isEmptySpace = !isEmptySpace;
	}

	auto printDisk = [](const std::vector<DiskBlockData>& disk) -> void {
		for (const DiskBlockData& val : disk)
		{
			if (val.first == EMPTY_SPACE)
			{
				for (uint8_t i = 0; i < val.second; i++)
					std::cout << ".";
			}
			else
			{
				for (uint8_t i = 0; i < val.second; i++)
					std::cout << val.first;
			}
		}

		std::cout << std::endl;
		};


	auto findFirstPossibleEmptySpaceOf = [](const std::vector<DiskBlockData>& disk, const uint8_t count) -> size_t {
		for (size_t i = 0; i < disk.size(); i++)
		{
			const DiskBlockData& data = disk[i];
			if (data.first == EMPTY_SPACE && data.second >= count)
				return i;
		}

		return std::numeric_limits<size_t>::max();
	};

	// We could concatenate same indices on the go to optimize memory, but it's not on the scope of this problem
	auto moveValueInDisk = [](std::vector<DiskBlockData>& disk, const size_t valueIdx, const size_t emptyIdx) -> void {
		DiskBlockData& emptyData = disk[emptyIdx];
		DiskBlockData& valueData = disk[valueIdx];

		if (emptyData.second == valueData.second)
		{
			emptyData.first = valueData.first;
			valueData.first = EMPTY_SPACE;
		}
		else // emptyData.second > valueData.second
		{
			emptyData.second -= valueData.second;
			const int16_t idx = valueData.first;
			const int8_t count = valueData.second;
			valueData.first = EMPTY_SPACE;
			disk.insert(disk.begin() + emptyIdx, { idx, count });
		}
	};

	for (size_t diskRightIdx = disk.size() - 1; diskRightIdx > 0; diskRightIdx--)
	{
		const DiskBlockData& val = disk[diskRightIdx];
		if (val.first == EMPTY_SPACE)
			continue;

		size_t firstEmptySpace = findFirstPossibleEmptySpaceOf(disk, disk[diskRightIdx].second);
		if (firstEmptySpace > diskRightIdx)
			continue;

		moveValueInDisk(disk, diskRightIdx, firstEmptySpace);
	}


	auto getChecksum = [](const std::vector<DiskBlockData>& disk) -> uint64_t {
		uint64_t result = 0u;
		uint64_t idx = 0u;
		for (const DiskBlockData& data : disk)
		{
			uint64_t currVal = data.first;
			if (currVal == EMPTY_SPACE)
			{
				idx += data.second;
				continue;
			}

			for (uint8_t i = 0; i < data.second; i++, idx++)
				result += idx * currVal;
		}

		return result;
		};

	uint64_t result = getChecksum(disk);
	std::cout << "The solution is " << result << "!" << std::endl;
}