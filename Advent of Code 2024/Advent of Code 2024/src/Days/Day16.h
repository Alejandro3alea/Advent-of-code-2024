#pragma once
#include "DaysCommon.h"

std::array<Point2D, 4> directions = { Point2D(0, -1), Point2D(-1, 0), Point2D(0, 1), Point2D(1, 0) };

int64_t BreadthFirstSearch(const Matrix<uint8_t>& lab, const Point2D& pos, const size_t dir, const Point2D& endPos, Matrix<int64_t>& costs)
{
	std::queue<std::tuple<Point2D, size_t, int64_t>> queue;
	queue.emplace(pos, dir, 0);

	while (!queue.empty())
	{
		const auto [pos, dir, cost] = queue.front();
		queue.pop();

		const size_t lDir = (dir + 3) % 4;
		const size_t rDir = (dir + 1) % 4;
		std::array<std::pair<size_t, int64_t>, 3> possibleCombinations =
		{
			std::make_pair(dir, cost + 1),
			std::make_pair(lDir, cost + 1001),
			std::make_pair(rDir, cost + 1001)
		};

		for (const auto& [newDir, newCost] : possibleCombinations)
		{
			const Point2D newPos = pos + directions[newDir];
			const uint8_t& c = lab[newPos];
			if (c == '#') // Assuming it can't go OOB
				continue;

			int64_t& prevCost = costs[newPos];
			if (prevCost == -1 || prevCost > newCost)
			{
				prevCost = newCost;
				queue.emplace(newPos, newDir, newCost);
			}
		}
	}

	return costs[endPos];
}

void SolveDay16Part1()
{
	std::ifstream file("data/Day 16/Data.txt");
	if (!file || !file.is_open())
	{
		std::cout << "The solution is within your heart (DATA NOT FOUND!)." << std::endl;
		return;
	}

	Matrix<uint8_t> labyrinth;

	std::string line;
	while (std::getline(file, line))
	{
		labyrinth.push_row({ line.begin(), line.end() });
	}

	const size_t startDir = 3;
	const Point2D playerPos = labyrinth.find_first_of('S');
	const Point2D endPos = labyrinth.find_first_of('E');

	Matrix<int64_t> costs(labyrinth.row_size(), labyrinth.size(), -1);
	const int64_t result = BreadthFirstSearch(labyrinth, playerPos, startDir, endPos, costs);
	std::cout << "The solution is " << result << "!" << std::endl;
}

///////////////////////////////////////////////////////////////////////////
///
///////////////////////////////////////////////////////////////////////////


uint64_t GetBestPossibleTiles(const Matrix<int64_t>& costs, const Point2D& startPos, const Point2D& endPos, Matrix<uint8_t>& lab)
{
	std::queue<std::tuple<Point2D, size_t, int64_t>> queue;
	std::set<Point2D> visited;

	// Assuming the end is always on the top-right corner
	queue.emplace(endPos, 1, costs[endPos]);
	queue.emplace(endPos, 2, costs[endPos]);

	uint64_t result = 0;
	while (!queue.empty())
	{
		const auto [pos, dir, cost] = queue.front();
		queue.pop();

		const size_t lDir = (dir + 3) % 4;
		const size_t rDir = (dir + 1) % 4;
		std::array<std::pair<size_t, int64_t>, 3> possibleCombinations =
		{
			std::make_pair(dir, cost - 1),
			std::make_pair(lDir, cost - 1001),
			std::make_pair(rDir, cost - 1001)
		};

		for (const auto& [newDir, newCost] : possibleCombinations)
		{
			const Point2D newPos = pos + directions[newDir];
			if ((costs[newPos] == newCost || costs[newPos] == newCost - 1000) && !visited.contains(newPos))
			{
				result++;
				queue.emplace(newPos, newDir, newCost);
				visited.emplace(newPos);
				lab[newPos] = 'O';
			}
		}
	}

	return result + 2; // Start + End
}

void SolveDay16Part2()
{
	std::ifstream file("data/Day 16/Data.txt");
	if (!file || !file.is_open())
	{
		std::cout << "The solution is within your heart (DATA NOT FOUND!)." << std::endl;
		return;
	}

	Matrix<uint8_t> labyrinth; 

	std::string line;
	while (std::getline(file, line))
	{
		labyrinth.push_row({ line.begin(), line.end() });
	}

	const size_t startDir = 3;
	const Point2D playerPos = labyrinth.find_first_of('S');
	const Point2D endPos = labyrinth.find_first_of('E');

	Matrix<int64_t> costs(labyrinth.row_size(), labyrinth.size(), -1);
	BreadthFirstSearch(labyrinth, playerPos, startDir, endPos, costs);
	uint64_t result = GetBestPossibleTiles(costs, playerPos, endPos, labyrinth);

	std::cout << costs[Point2D(115, 53)] << " vs " << costs[Point2D(115, 52)] << " vs " << costs[Point2D(115, 51)] << std::endl;
	std::cout << costs[Point2D(115, 49)] << " vs " << costs[Point2D(115, 50)] << " vs " << costs[Point2D(115, 51)] << std::endl;
	std::cout << costs[Point2D(115, 47)] << " vs " << costs[Point2D(115, 48)] << " vs " << costs[Point2D(115, 49)] << std::endl;
	std::cout << costs[Point2D(115, 44)] << " vs " << costs[Point2D(115, 45)] << " vs " << costs[Point2D(115, 46)] << std::endl;
	std::cout << costs[Point2D(115, 49)] << " vs " << costs[Point2D(115, 50)] << " vs " << costs[Point2D(115, 51)] << std::endl;
	std::cout << labyrinth << std::endl; 
	std::cout << "The solution is " << result << "!" << std::endl;
}