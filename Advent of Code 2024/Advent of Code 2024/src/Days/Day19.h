#pragma once
#include "DaysCommon.h"

bool IsDesignMatchable(const std::string& design, const std::vector<std::string>& patterns)
{
	const size_t strSize = design.size();
	std::vector<bool> matches(strSize + 1, false);
	matches[0] = true;

	for (uint32_t i = 0; i < strSize; i++)
	{
		if (!matches[i])
			continue;

		for (const std::string& pat : patterns)
		{
			std::string val = design.substr(i, pat.size());
			if (pat.size() + i <= strSize && pat == val)
			{
				matches[i + pat.size()] = true;
			}
		}
	}

	return matches[strSize];
}

std::vector<std::string> ParsePatterns(const std::string& str)
{
	std::vector<std::string> result;

	std::regex delimiter("[, ]+");
	std::sregex_token_iterator it(str.begin(), str.end(), delimiter, -1);
	std::sregex_token_iterator end;

	while (it != end) 
	{
		result.push_back(*it);
		++it;
	}
	return result;
}

void SolveDay19Part1()
{
	std::ifstream file("data/Day 19/Data.txt");
	if (!file || !file.is_open())
	{
		std::cout << "The solution is within your heart (DATA NOT FOUND!)." << std::endl;
		return;
	}

	std::string line;
	std::getline(file, line);
	std::vector<std::string> patterns = ParsePatterns(line);

	uint32_t result = 0;
	while (std::getline(file, line))
	{
		if (!line.empty() && IsDesignMatchable(line, patterns))
			result++;
	}

	std::cout << "The solution is " << result << "!" << std::endl;
}

///////////////////////////////////////////////////////////////////////////
///
///////////////////////////////////////////////////////////////////////////

uint64_t GetDesignMatches(const std::string& design, const std::vector<std::string>& patterns, std::unordered_map<std::string, uint64_t>& matches)
{
	if (matches.find(design) != matches.end())
		return matches[design];

	uint64_t result = 0;
	if (design.empty())
		result = 1;
	else
	{
		for (const std::string& pat : patterns)
			if (design.starts_with(pat))
				result += GetDesignMatches(design.substr(pat.size()), patterns, matches);
	}

	matches[design] = result;
	return result;
}

void SolveDay19Part2()
{
	std::ifstream file("data/Day 19/Data.txt");
	if (!file || !file.is_open())
	{
		std::cout << "The solution is within your heart (DATA NOT FOUND!)." << std::endl;
		return;
	}

	std::string line;
	std::getline(file, line);
	std::vector<std::string> patterns = ParsePatterns(line);

	uint64_t result = 0;
	std::unordered_map<std::string, uint64_t> matches;
	while (std::getline(file, line))
	{
		if (!line.empty())
			result += GetDesignMatches(line, patterns, matches);
	}

	std::cout << "The solution is " << result << "!" << std::endl;
}