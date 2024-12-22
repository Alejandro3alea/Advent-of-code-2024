#pragma once
#include "DaysCommon.h"

struct ButtonData {
    uint32_t buttonAX, buttonAY;
    uint32_t buttonBX, buttonBY;
    uint32_t prizeX, prizeY;
};

uint32_t ComputeMinTokens(const ButtonData& data, const int32_t x, const int32_t y, const uint32_t stepCount)
{
    if (x < 0 || y < 0)
        return std::numeric_limits<uint32_t>::max();

    if (x == 0 && y == 0)
        return stepCount;

    // This is not fast...
    return std::min(ComputeMinTokens(data, x - data.buttonAX, y - data.buttonAY, stepCount + 1),
                    ComputeMinTokens(data, x - data.buttonBX, y - data.buttonBY, stepCount + 1));
}

std::vector<ButtonData> ParseData(const std::string& buttonData) 
{
    std::vector<ButtonData> result;
    std::regex dataRegex(R"(Button A: X\+(\d+), Y\+(\d+)\nButton B: X\+(\d+), Y\+(\d+)\nPrize: X=(\d+), Y=(\d+))");

    auto begin = std::sregex_iterator(buttonData.begin(), buttonData.end(), dataRegex);
    auto end = std::sregex_iterator();

    for (auto it = begin; it != end; ++it) {
        const std::smatch& match = *it;

        result.push_back({
            std::stoul(match[1].str()), // Button A X
            std::stoul(match[2].str()), // Button A Y
            std::stoul(match[3].str()), // Button B X
            std::stoul(match[4].str()), // Button B Y
            std::stoul(match[5].str()), // Prize X
            std::stoul(match[6].str())  // Prize Y
        });
    }

    return result;
}

void SolveDay13Part1()
{
	std::ifstream file("data/Day 13/Data.txt");
	if (!file || !file.is_open())
	{
		std::cout << "The solution is within your heart (DATA NOT FOUND!)." << std::endl;
		return;
	}

	std::string buttonDataStr;
    std::string line;
	while (std::getline(file, line))
	{
        buttonDataStr += line + '\n';
	}

    std::vector<ButtonData> buttonData = ParseData(buttonDataStr);

    uint32_t result = 0;
    for (size_t i = 0; i < buttonData.size(); ++i) 
    {
        std::cout << i << std::endl;
        const ButtonData& currData = buttonData[i];
        result += ComputeMinTokens(currData, currData.prizeX, currData.prizeY, 0);
    }

    // Debug
    /*for (size_t i = 0; i < buttonData.size(); ++i) 
    {
        const ButtonData& currData = buttonData[i];
        std::cout << "Group " << i + 1 << ":\n";
        std::cout << "  Button A: X=" << currData.buttonAX << ", Y=" << currData.buttonAY << "\n";
        std::cout << "  Button B: X=" << currData.buttonBX << ", Y=" << currData.buttonBY << "\n";
        std::cout << "  Prize: X=" << currData.prizeX << ", Y=" << currData.prizeY << "\n";
    }*/

	std::cout << "The solution is " << result << "!" << std::endl;
}

///////////////////////////////////////////////////////////////////////////
///
///////////////////////////////////////////////////////////////////////////

void SolveDay13Part2()
{
	std::ifstream file("data/Day 13/Data.txt");
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