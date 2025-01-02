#pragma once
#include "DaysCommon.h"

using NodeGraphPart1 = std::unordered_map<std::string, std::set<std::string>>;

bool CheckIfNodeIsConnected(NodeGraphPart1& graphs, const std::string& aNode, const std::string& bNode, const std::string& cNode)
{
	return	graphs[aNode].find(cNode) != graphs[aNode].end() &&
		graphs[bNode].find(cNode) != graphs[bNode].end();
}

bool Part1Check(NodeGraphPart1& graphs, const std::string& aNode, const std::string& bNode, const std::string& cNode)
{
	return	CheckIfNodeIsConnected(graphs, aNode, bNode, cNode) &&
			(aNode.starts_with('t') || bNode.starts_with('t') || cNode.starts_with('t'));
}

void SolveDay23Part1()
{
	std::ifstream file("data/Day 23/Data.txt");
	if (!file || !file.is_open())
	{
		std::cout << "The solution is within your heart (DATA NOT FOUND!)." << std::endl;
		return;
	}

	NodeGraphPart1 graphs;

	std::string line;
	while (std::getline(file, line))
	{
		std::stringstream ss(line);
		std::string lVal, rVal;
		std::getline(ss, lVal, '-');
		std::getline(ss, rVal, '-');

		if (lVal < rVal)
			graphs[lVal].insert(rVal);
		else
			graphs[rVal].insert(lVal);
	}

	uint32_t result = 0;
	for (auto& [aNode, connections] : graphs)
	{
		for (const std::string& bNode : connections)
		{
			for (const std::string& cNode : graphs[bNode])
			{
				if (Part1Check(graphs, aNode, bNode, cNode))
					result++;
			}
		}
	}

	std::cout << "The solution is " << result << "!" << std::endl;
}

///////////////////////////////////////////////////////////////////////////
///
///////////////////////////////////////////////////////////////////////////

using NodeGraphPart2 = std::unordered_map<std::string, std::vector<std::string>>;

void GetBiggestConnectionsOf(NodeGraphPart2& graphs, const std::string& node, const uint32_t i,
	std::vector<std::string> connections, std::vector<std::string>& biggestNetwork)
{
	if (i == graphs[node].size())
	{
		if (biggestNetwork.size() < connections.size())
			biggestNetwork = std::move(connections);

		return;
	}

	GetBiggestConnectionsOf(graphs, node, i + 1, connections, biggestNetwork);

	const std::string nextVal = graphs[node][i];
	for (const std::string& n : connections)
		if (std::ranges::find(graphs[nextVal], n) == graphs[nextVal].end())
			return;

	connections.push_back(nextVal);
	GetBiggestConnectionsOf(graphs, node, i + 1, connections, biggestNetwork);
}

std::vector<std::string> GetBiggestConnections(NodeGraphPart2& graphs)
{
	std::vector<std::string> result;
	for (auto& [node, connections] : graphs)
	{
		std::vector<std::string> currConnections = { node };
		GetBiggestConnectionsOf(graphs, node, 0, currConnections, result);
	}

	return result;
}

void PrintString(const std::vector<std::string>& nodes)
{
	for (const std::string& node : nodes)
		std::cout << node << ",";
}

void SolveDay23Part2()
{
	std::ifstream file("data/Day 23/Data.txt");
	if (!file || !file.is_open())
	{
		std::cout << "The solution is within your heart (DATA NOT FOUND!)." << std::endl;
		return;
	}

	NodeGraphPart2 graphs;

	std::string line;
	while (std::getline(file, line))
	{
		std::stringstream ss(line);
		std::string lVal, rVal;
		std::getline(ss, lVal, '-');
		std::getline(ss, rVal, '-');

		graphs[lVal].push_back(rVal);
		graphs[rVal].push_back(lVal);
	}

	std::vector<std::string> nodes = GetBiggestConnections(graphs);
	std::sort(nodes.begin(), nodes.end());

	std::cout << "The solution is: ";
	PrintString(nodes);
}