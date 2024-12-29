#pragma once
#include "DaysCommon.h"

using KeyCombo = std::array<int16_t, 5>;

KeyCombo GetCombination(const bool isKey, std::ifstream& file)
{
	std::string line;
	KeyCombo result { -1, -1, -1, -1, -1 };
	const uint16_t charToFind = isKey ? '#' : '.';
	for (uint16_t i = 0; i < 6; i++)
	{
		std::getline(file, line);
		for (uint16_t j = 0; j < line.size(); j++)
		{
			if (result[j] != -1)
				continue;

			if (charToFind == line[j])
				result[j] = i;
		}
	}

	std::getline(file, line);
	return result;
}

bool CompareLockAndKey(const KeyCombo& lock, const KeyCombo& key)
{
	for (uint16_t i = 0; i < lock.size(); i++)
		if (key[i] < lock[i])
			return false;

	return true;
}

void PrintCombo(const KeyCombo& lock, const KeyCombo& key)
{
	std::cout << "[" << lock[0] << ", " << lock[1] << ", " << lock[2] << ", " <<
		lock[3] << ", " << lock[4] << "] + [" << key[0] << ", " << key[1] << ", " << 
		key[2] << ", " << key[3] << ", " << key[4] << "]" << std::endl;
}

void SolveDay25Part1()
{
	std::ifstream file("data/Day 25/Data.txt");
	if (!file || !file.is_open())
	{
		std::cout << "The solution is within your heart (DATA NOT FOUND!)." << std::endl;
		return;
	}

	std::vector<KeyCombo> locks;
	std::vector<KeyCombo> keys;

	std::string line;
	while (std::getline(file, line))
	{
		const bool isKey = line[0] == '.';
		std::array<int16_t, 5> combination = GetCombination(isKey, file);
		std::vector<KeyCombo>& container = isKey ? keys : locks;
		container.push_back(combination);
	}

	uint32_t result = 0;
	for (const KeyCombo& lock : locks)
	{
		for (const KeyCombo& key : keys)
		{
			if (CompareLockAndKey(lock, key))
				result++;
		}
	}

	std::cout << "The solution is " << result << "!" << std::endl;
}

///////////////////////////////////////////////////////////////////////////
///
///////////////////////////////////////////////////////////////////////////

void SolveDay25Part2()
{
	std::ifstream file("data/Day 25/Data.txt");
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