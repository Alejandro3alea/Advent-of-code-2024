#pragma once
#include "DaysCommon.h"

struct ButtonData {
    uint64_t buttonAX, buttonAY;
    uint64_t buttonBX, buttonBY;
    uint64_t prizeX, prizeY;
};

struct ButtonKey
{
    int64_t x;
    int64_t y;
    uint32_t stepCount;

    bool operator==(const ButtonKey& rhs) const = default;
};

struct ButtonHash
{
    size_t operator()(const ButtonKey& key) const
    {
        return std::hash<int64_t>()(key.x) ^
            (std::hash<int64_t>()(key.y) << 1) ^
            (std::hash<uint32_t>()(key.stepCount) << 2);
    }
};

uint32_t ComputeMinTokens(const ButtonData& data, const int32_t x, const int32_t y, const uint32_t stepCount,
                          std::unordered_map<ButtonKey, uint32_t, ButtonHash>& dpTable)
{
    if (x < 0 || y < 0)
        return std::numeric_limits<uint32_t>::max();

    if (x == 0 && y == 0)
        return stepCount;


    ButtonKey key = { x, y, stepCount };
    if (dpTable.find(key) != dpTable.end())
        return dpTable[key];

    uint32_t result = std::min( ComputeMinTokens(data, x - data.buttonAX, y - data.buttonAY, stepCount + 3, dpTable),
                                ComputeMinTokens(data, x - data.buttonBX, y - data.buttonBY, stepCount + 1, dpTable));

    dpTable[key] = result;
    return result;
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
        const ButtonData& currData = buttonData[i];
        std::unordered_map<ButtonKey, uint32_t, ButtonHash> dpLookupTable;
        uint32_t currRes = ComputeMinTokens(currData, currData.prizeX, currData.prizeY, 0, dpLookupTable);
        if (currRes != std::numeric_limits<uint32_t>::max())
            result += currRes;
    }

	std::cout << "The solution is " << result << "!" << std::endl;
}

///////////////////////////////////////////////////////////////////////////
///
///////////////////////////////////////////////////////////////////////////


// Faster way using linear algebra
void SolveDay13Part2()
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

    const int64_t diff = 10000000000000;
    uint64_t result = 0;
    for (size_t i = 0; i < buttonData.size(); ++i)
    {
        const ButtonData& data = buttonData[i];
        const int64_t newPrizeX = data.prizeX + diff;
        const int64_t newPrizeY = data.prizeY + diff;

        // Ax * a + Bx * b = Px
        // Ay * a + By * b = Py

        // Since it's a linear system of equations, we can use Cramer's rule
        const int64_t det = data.buttonAX * data.buttonBY - data.buttonAY * data.buttonBX;
        const int64_t dA = newPrizeX * data.buttonBY - newPrizeY * data.buttonBX;
        const int64_t dB = data.buttonAX * newPrizeY - data.buttonAY * newPrizeX;

        if ((dA % det) != 0 || (dB % det) != 0) // Result is not integral (not possible solution)
            continue;

        const int64_t resA = dA / det;
        const int64_t resB = dB / det;

        if (resA < 0 || resB < 0) // One result is negative (impossible)
            continue;


        result += 3 * resA + resB;
    }

    std::cout << "The solution is " << result << "!" << std::endl;
}