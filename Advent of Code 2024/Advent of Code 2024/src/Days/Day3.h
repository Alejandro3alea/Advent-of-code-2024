#pragma once
#include "DaysCommon.h"

enum class NumReadingState
{
	eWorkingWithLeftNum,
	eWorkingWithRightNum,
	eComplete,
	eError,
};

void SolveDay3Part1()
{
	std::ifstream file("data/Day 3/Data.txt");
	if (!file || !file.is_open())
	{
		std::cout << "The solution is within your heart (DATA NOT FOUND!)." << std::endl;
		return;
	}

	uint32_t totalSum = 0;
	std::string line;
	while (std::getline(file, line))
	{
		size_t lineOffset = 0;
		std::vector<size_t> mulIndices;
		size_t mulIndex = line.find("mul(", lineOffset);
		while (mulIndex != std::string::npos)
		{
			mulIndices.push_back(mulIndex);
			lineOffset = mulIndex + 1;
			mulIndex = line.find("mul(", lineOffset);
		}

		for (const size_t index : mulIndices)
		{
			std::string numberL;
			std::string numberR;

			size_t currIndex = index + 4;
			NumReadingState readingState = NumReadingState::eWorkingWithLeftNum;
			while (readingState != NumReadingState::eComplete && readingState != NumReadingState::eError)
			{
				switch (const char c = line[currIndex]; c)
				{
				case ',':
					if (readingState == NumReadingState::eWorkingWithRightNum)
					{
						readingState = NumReadingState::eError;
						break;
					}
					readingState = NumReadingState::eWorkingWithRightNum;
					break;
				case ')':
					if (readingState == NumReadingState::eWorkingWithLeftNum)
					{
						readingState = NumReadingState::eError;
						break;
					}
					readingState = NumReadingState::eComplete;
					break;
				default:
					if (c < '0' || c > '9')
					{
						readingState = NumReadingState::eError;
						break;
					}
					if (readingState == NumReadingState::eWorkingWithLeftNum)
					{
						numberL.push_back(c);
					}
					else
					{
						numberR.push_back(c);
					}
				}

				currIndex++;
			}

			if (readingState == NumReadingState::eComplete)
			{
				totalSum += std::atoi(numberL.c_str()) * std::atoi(numberR.c_str());
			}
		}
	}

	std::cout << "The solution is " << totalSum << "!" << std::endl;
}

///////////////////////////////////////////////////////////////////////////
///
///////////////////////////////////////////////////////////////////////////

void SolveDay3Part2()
{
	std::ifstream file("data/Day 3/Data.txt");
	if (!file || !file.is_open())
	{
		std::cout << "The solution is within your heart (DATA NOT FOUND!)." << std::endl;
		return;
	}

	auto findAllIndicesInLineOf = [](const std::string& line, const std::string& substring) -> std::vector<size_t> {
		size_t lineOffset = 0;
		std::vector<size_t> indices;
		size_t currIndex = line.find(substring, lineOffset);
		while (currIndex != std::string::npos)
		{
			indices.push_back(currIndex);
			lineOffset = currIndex + 1;
			currIndex = line.find(substring, lineOffset);
		}

		return indices;
	};


	bool endsWithDisable = false;
	uint32_t totalSum = 0;
	std::string line;
	while (std::getline(file, line))
	{
		std::vector<size_t> mulIndices = findAllIndicesInLineOf(line, "mul(");
		std::vector<size_t> enableIndices = findAllIndicesInLineOf(line, "do()");
		std::vector<size_t> disableIndices = findAllIndicesInLineOf(line, "don't()");

		if (endsWithDisable)
		{
			auto nextEnable = std::lower_bound(enableIndices.begin(), enableIndices.end(), 0);
			const size_t endOfDisable = nextEnable != enableIndices.end() ? *nextEnable : std::numeric_limits<size_t>::max();
			auto endOfDisabledMul = std::lower_bound(mulIndices.begin(), mulIndices.end(), endOfDisable);

			mulIndices.erase(mulIndices.begin(), endOfDisabledMul);
		}
		for (const size_t disableIndex : disableIndices)
		{
			auto nextEnable = std::lower_bound(enableIndices.begin(), enableIndices.end(), disableIndex);
			const size_t endOfDisable = nextEnable != enableIndices.end() ? *nextEnable : std::numeric_limits<size_t>::max();

			auto startOfDisabledMul = std::lower_bound(mulIndices.begin(), mulIndices.end(), disableIndex);
			auto endOfDisabledMul = std::lower_bound(mulIndices.begin(), mulIndices.end(), endOfDisable);

			mulIndices.erase(startOfDisabledMul, endOfDisabledMul);
		}
		endsWithDisable = disableIndices[disableIndices.size() - 1] > enableIndices[enableIndices.size() - 1];

		for (const size_t index : mulIndices)
		{
			std::string numberL;
			std::string numberR;

			size_t currIndex = index + 4;
			NumReadingState readingState = NumReadingState::eWorkingWithLeftNum;
			while (readingState != NumReadingState::eComplete && readingState != NumReadingState::eError)
			{
				switch (const char c = line[currIndex]; c)
				{
				case ',':
					if (readingState == NumReadingState::eWorkingWithRightNum)
					{
						readingState = NumReadingState::eError;
						break;
					}
					readingState = NumReadingState::eWorkingWithRightNum;
					break;
				case ')':
					if (readingState == NumReadingState::eWorkingWithLeftNum)
					{
						readingState = NumReadingState::eError;
						break;
					}
					readingState = NumReadingState::eComplete;
					break;
				default:
					if (c < '0' || c > '9')
					{
						readingState = NumReadingState::eError;
						break;
					}
					if (readingState == NumReadingState::eWorkingWithLeftNum)
					{
						numberL.push_back(c);
					}
					else
					{
						numberR.push_back(c);
					}
				}

				currIndex++;
			}

			if (readingState == NumReadingState::eComplete)
			{
				totalSum += std::atoi(numberL.c_str()) * std::atoi(numberR.c_str());
			}
		}
	}

	std::cout << "The solution is " << totalSum << "!" << std::endl;
}