#pragma once
#include "DaysCommon.h"

std::array<Point2D, 4> directions = { Point2D(0, -1), Point2D(-1, 0), Point2D(0, 1), Point2D(1, 0) };

int64_t BreadthFirstSearch(const Matrix<uint8_t>& lab, const Point2D& pos, const size_t dir, const Point2D& endPos)
{
	Matrix<int64_t> costs(lab.row_size(), lab.size(), -1);
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

	const int64_t result = BreadthFirstSearch(labyrinth, playerPos, startDir, endPos);
	std::cout << "The solution is " << result << "!" << std::endl;
}

///////////////////////////////////////////////////////////////////////////
///
///////////////////////////////////////////////////////////////////////////


int64_t BreadthFirstSearchPart2(const Matrix<uint8_t>& lab, const Point2D& pos, const size_t dir, const Point2D& endPos, Matrix<std::set<int64_t>>& outCosts)
{
	Matrix<int64_t> costs(lab.row_size(), lab.size(), -1);

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
				outCosts[newPos].insert(newCost);
				queue.emplace(newPos, newDir, newCost);
			}
		}
	}

	return costs[endPos];
}

uint64_t GetBestPossibleTiles(const Matrix<std::set<int64_t>>& costs, const Point2D& startPos, const Point2D& endPos, Matrix<uint8_t>& lab, const int64_t endCost)
{
	std::queue<std::tuple<Point2D, size_t, int64_t>> queue;
	std::set<Point2D> visited;

	// Assuming the end is always on the top-right corner
	queue.emplace(endPos, 1, endCost);
	queue.emplace(endPos, 2, endCost);

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
			for (const int64_t savedCost : costs[newPos])
			{
				if ((savedCost == newCost || savedCost == newCost - 1000) && !visited.contains(newPos))
				{
					result++;
					queue.emplace(newPos, newDir, newCost);
					visited.emplace(newPos);
					lab[newPos] = 'O';
					break;
				}
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

	Matrix<std::set<int64_t>> costs(labyrinth.row_size(), labyrinth.size());
	int64_t endCost = BreadthFirstSearchPart2(labyrinth, playerPos, startDir, endPos, costs);
	uint64_t result = GetBestPossibleTiles(costs, playerPos, endPos, labyrinth, endCost);

	std::cout << labyrinth << std::endl; 
	std::cout << "The solution is " << result << "!" << std::endl;
}