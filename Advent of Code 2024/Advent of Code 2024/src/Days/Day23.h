#pragma once
#include "DaysCommon.h"

using NodeGraph = std::unordered_map<std::string, std::set<std::string>>;

bool CheckIfNodeIsConnected(NodeGraph& graphs, const std::string& aNode, const std::string& bNode, const std::string& cNode)
{
	return	graphs[aNode].find(cNode) != graphs[aNode].end() &&
		graphs[bNode].find(cNode) != graphs[bNode].end();
}

bool Part1Check(NodeGraph& graphs, const std::string& aNode, const std::string& bNode, const std::string& cNode)
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

	NodeGraph graphs;

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

void GetBiggestConnectionsOf(NodeGraph& graphs, const std::string& currVal, std::set<std::string>& connections)
{
	uint32_t result = 0;
	for (const std::string& currNode : graphs[currVal])
	{
		if (connections.find(currNode) == connections.end())
		{
			bool isValid = true;
			for (const std::string& checkNode : connections)
			{
				if (graphs[currNode].find(checkNode) == graphs[currNode].end())
				{
					isValid = false;
					break;
				}
			}
			if (isValid)
			{
				connections.insert(currNode);
				GetBiggestConnectionsOf(graphs, currNode, connections);
			 }
		}
	}
}

std::set<std::string> GetBiggestConnections(NodeGraph& graphs)
{
	std::set<std::string> result;
	for (auto& [node, connections] : graphs)
	{
		std::set<std::string> currConnections;
		GetBiggestConnectionsOf(graphs, node, currConnections);
		if (result.size() < currConnections.size())
			result = std::move(currConnections);
	}

	return result;
}

void PrintString(const std::set<std::string>& nodes)
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

	NodeGraph graphs;

	std::string line;
	while (std::getline(file, line))
	{
		std::stringstream ss(line);
		std::string lVal, rVal;
		std::getline(ss, lVal, '-');
		std::getline(ss, rVal, '-');

		graphs[lVal].insert(rVal);
		graphs[rVal].insert(lVal);
	}

	std::set<std::string> nodes = GetBiggestConnections(graphs);
	std::cout << "The solution is: ";
	PrintString(nodes);
}