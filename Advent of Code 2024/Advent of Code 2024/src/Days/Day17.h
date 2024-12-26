#pragma once
#include "DaysCommon.h"

// Making registers global to simplify function syntax (sorry, Clean Code)
uint64_t regA, regB, regC;
uint64_t instructionPtr = 0;
std::string outputStr;
std::string targetStr;

using InstructionData = std::pair<uint8_t, uint8_t>; // opcode, operand
std::vector<InstructionData> instructions;

int64_t GetComboOperand(const uint8_t operand)
{
	switch (operand)
	{
	// Literals
	case 0:
		return 0;
	case 1:
		return 1;
	case 2:
		return 2;
	case 3:
		return 3;

	// Registers
	case 4:
		return regA;
	case 5:
		return regB;
	case 6:
		return regC;

	// Invalid operand
	default:
		return -1;
	}
}

#pragma region opcodes
void adv(const uint8_t operand)
{
	regA /= std::pow(2, GetComboOperand(operand));
}

void bxl(const uint8_t operand)
{
	regB ^= operand;
}

void bst(const uint8_t operand)
{
	regB = GetComboOperand(operand) % 8;
}

void jnz(const uint8_t operand)
{
	if (regA != 0)
		instructionPtr = operand;
}

void bxc(const uint8_t operand)
{
	regB ^= regC;
}

void out(const uint8_t operand)
{
	if (!outputStr.empty())
		outputStr += ',';

	outputStr += std::to_string(GetComboOperand(operand) % 8);
}

void bdv(const uint8_t operand)
{
	regB = regA / std::pow(2, GetComboOperand(operand));
}

void cdv(const uint8_t operand)
{
	regC = regA / std::pow(2, GetComboOperand(operand));
}
#pragma endregion

std::array<std::function<void(const uint8_t)>, 8> opcodes = {
	adv,
	bxl,
	bst,
	jnz,
	bxc,
	out,
	bdv,
	cdv
};

void SolveDay17Part1()
{
	std::ifstream file("data/Day 17/Data.txt");
	if (!file || !file.is_open())
	{
		std::cout << "The solution is within your heart (DATA NOT FOUND!)." << std::endl;
		return;
	}


	std::string line;
	while (std::getline(file, line))
	{
		std::istringstream iss(line);
		iss.ignore(line.find(':') + 1);
		if (line.find("Register A:") != std::string::npos)
			iss >> regA;
		else if (line.find("Register B:") != std::string::npos)
			iss >> regB;
		else if (line.find("Register C:") != std::string::npos)
			iss >> regC;
		else if (line.find("Program:") != std::string::npos)
		{
			uint8_t opcode, operand;
			while (iss >> opcode)
			{
				iss.ignore();
				iss >> operand;
				iss.ignore();
				instructions.push_back({ opcode - '0', operand - '0'});
			}
		}
	}

	while (instructionPtr < instructions.size())
	{
		const InstructionData& instruction = instructions[instructionPtr++];
		auto& opcode = opcodes[instruction.first];

		opcode(instruction.second);
	}

	std::cout << "The solution is " << outputStr << "!" << std::endl;
}

///////////////////////////////////////////////////////////////////////////
///
///////////////////////////////////////////////////////////////////////////

bool DoesCommandMatch(const std::string& baseStr, const std::string& subStr)
{
	for (size_t i = 1; i <= subStr.size(); i++)
	{
		if (subStr[subStr.size() - i] != baseStr[baseStr.size() - i])
			return false;
	}

	return true;
}

uint64_t GetRegAValue(const uint64_t val)
{
	for (size_t i = 0; i < 8; i++)
	{
		const uint64_t currVal = val + i;
		regA = currVal;
		instructionPtr = 0;
		outputStr.clear();

		while (instructionPtr < instructions.size())
		{
			const InstructionData& instruction = instructions[instructionPtr++];
			auto& opcode = opcodes[instruction.first];
			opcode(instruction.second);
		}

		if (DoesCommandMatch(targetStr, outputStr))
		{
			if (targetStr.size() == outputStr.size())
				return currVal;

			const uint64_t recRes = GetRegAValue(currVal * 8);
			if (recRes != std::numeric_limits<uint64_t>::max())
				return recRes;
		}
	}

	return std::numeric_limits<uint64_t>::max();
}

void SolveDay17Part2()
{
	std::ifstream file("data/Day 17/Data.txt");
	if (!file || !file.is_open())
	{
		std::cout << "The solution is within your heart (DATA NOT FOUND!)." << std::endl;
		return;
	}

	std::string line;
	while (std::getline(file, line))
	{
		std::istringstream iss(line);
		iss.ignore(line.find(':') + 1);
		if (line.find("Register A:") != std::string::npos)
			iss >> regA;
		else if (line.find("Register B:") != std::string::npos)
			iss >> regB;
		else if (line.find("Register C:") != std::string::npos)
			iss >> regC;
		else if (line.find("Program:") != std::string::npos)
		{
			targetStr = line.substr(std::string("Program: ").size());
			uint8_t opcode, operand;
			while (iss >> opcode)
			{
				iss.ignore();
				iss >> operand;
				iss.ignore();
				instructions.push_back({ opcode - '0', operand - '0' });
			}
		}
	}

	uint64_t result = GetRegAValue(0);

	std::cout << "The solution is " << result << "!" << std::endl;
}
