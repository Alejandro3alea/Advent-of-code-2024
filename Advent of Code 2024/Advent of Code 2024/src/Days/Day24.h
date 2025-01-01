#pragma once
#include "DaysCommon.h"

enum class InstructionType
{
	AND,
	OR,
	XOR
};

using ValueMap = std::unordered_map<std::string, bool>;
using OperationMap = std::map<std::string, std::tuple<InstructionType, std::string, std::string>>;

bool GetValueOf(ValueMap& values, OperationMap& operations, const std::string& currVal)
{
	if (values.find(currVal) != values.end())
		return values[currVal];

	auto it = operations.find(currVal);
	if (it == operations.end()) {
		// This is an error! We have no way to compute 'currVal'.
		throw std::runtime_error("Undefined operation for '" + currVal + "'");
	}

	auto& [op, lhs, rhs] = operations[currVal];
	const bool lhsRes = GetValueOf(values, operations, lhs);
	const bool rhsRes = GetValueOf(values, operations, rhs);
	bool result = false;
	switch (op)
	{
	case InstructionType::AND:
		result = lhsRes && rhsRes;
		break;
	case InstructionType::OR:
		result = lhsRes || rhsRes;
		break;
	case InstructionType::XOR:
		result = lhsRes ^ rhsRes;
		break;
	};

	values[currVal] = result;
	return result;
}

uint64_t GetZValue(ValueMap& values, OperationMap& operations)
{
	std::bitset<64> resultBitset;
	for (auto& currOp : operations)
	{
		const std::string name = currOp.first;
		if (name.starts_with('z'))
		{
			const std::string zValNumStr = name.substr(1, 2);
			const uint64_t zValNum = std::stoi(zValNumStr);
			if (GetValueOf(values, operations, name))
				resultBitset.set(zValNum, true);
		}
	}

	return resultBitset.to_ullong();
}

void SolveDay24Part1()
{
	std::ifstream file("data/Day 24/Data.txt");
	if (!file || !file.is_open())
	{
		std::cout << "The solution is within your heart (DATA NOT FOUND!)." << std::endl;
		return;
	}

	ValueMap values;
	OperationMap operations;

	std::string line;
	while (std::getline(file, line) && !line.empty())
	{
		// x00: 1
		const std::string valName = line.substr(0, 3);
		const bool bitNum = line[5] != '0';
		values[valName] = bitNum;
	}

	while (std::getline(file, line))
	{
		std::stringstream ss(line);
		std::string lhs, opStr, rhs, res;
		InstructionType op;
		ss >> lhs;
		ss >> opStr;
		ss >> rhs;
		ss.ignore(3);
		ss >> res;

		if (opStr == "AND")
			op = InstructionType::AND;
		else if (opStr == "OR")
			op = InstructionType::OR;
		else // XOR
			op = InstructionType::XOR;

		operations[res] = { op, lhs, rhs };
	}

	uint64_t result = GetZValue(values, operations);
	std::cout << "The solution is " << result << "!" << std::endl;
}

///////////////////////////////////////////////////////////////////////////
///
///////////////////////////////////////////////////////////////////////////

void SolveDay24Part2()
{
	std::ifstream file("data/Day 24/Data.txt");
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