#include "day_24.hpp"

#include <iostream>
#include <regex>

aoc::day_24::day_24(const input& input) : day(input)
{
	for (const auto& line : m_input.strings())
	{
		m_program.emplace(line);
	}
}

void aoc::day_24::part_one()
{
	if (m_input.test)
	{
		for (int i = 0; i < 0x10; ++i)
		{
			computer c(m_program, std::queue<int>({ i }));
			c.run_program();
			std::cout << c.w << c.x << c.y << c.z << std::endl;
		}
	}
	else
	{
		std::array<std::pair<int, int>, 14> pairs({ {
			{10, 12},
			{10, 10},
			{12, 8},
			{11, 4},
			{0, 3},
			{15, 10},
			{13, 6},
			{-12, 13},
			{-15, 8},
			{-15, 1},
			{-4, 7},
			{10, 6},
			{-5, 9},
			{-12, 9}
		} });
		const auto res = calc(0, 0, pairs).second;
		std::cout << res << std::endl;
	}
}

void aoc::day_24::part_two()
{
	if (m_input.test)
	{
		for (int i = 0; i < 0x10; ++i)
		{
			computer c(m_program, std::queue<int>({ i }));
			c.run_program();
			std::cout << c.w << c.x << c.y << c.z << std::endl;
		}
	}
	else
	{
		std::array<std::pair<int, int>, 14> pairs({ {
			{10, 12},
			{10, 10},
			{12, 8},
			{11, 4},
			{0, 3},
			{15, 10},
			{13, 6},
			{-12, 13},
			{-15, 8},
			{-15, 1},
			{-4, 7},
			{10, 6},
			{-5, 9},
			{-12, 9}
		} });
		auto res = calc_little(0, 0, pairs).second;
		std::cout << res << std::endl;
	}
}

aoc::day_24::instruction::instruction(const std::string& instruction)
{
	const std::regex search("(inp|add|mul|div|mod|eql) ([xyzw])(?: ([xyzw]|-?\\d+))?$");
	std::smatch matches;
	std::regex_match(instruction, matches, search);
	const auto& str = matches[1].str();

	if (str == "inp") op = INPUT;
	else if (str == "add") op = ADD;
	else if (str == "mul") op = MULTIPLY;
	else if (str == "div") op = DIVIDE;
	else if (str == "mod") op = MODULO;
	else if (str == "eql") op = EQUALS;

	target = static_cast<reg>(*matches[2].first);

	if (matches[3].matched)
	{
		const auto& first = *matches[3].first;
		if (first >= 'w' && first <= 'z')
		{
			value_type = REG;
			value_reg = static_cast<reg>(first);
		}
		else
		{
			value_type = LITERAL;
			value = std::stoi(matches[3].str());
		}
	}
}

void aoc::day_24::computer::run_program()
{
	while (!program.empty())
	{
		const auto& inst = program.front();

		int* target;
		if (inst.target == X) target = &x;
		else if (inst.target == Y) target = &y;
		else if (inst.target == Z) target = &z;
		else if (inst.target == W) target = &w;
		else throw std::exception();

		int value;
		if (inst.op == INPUT)
		{
			value = input.front();
			input.pop();
		}
		else if (inst.value_type == instruction::REG)
		{
			if (inst.value_reg == X) value = x;
			else if (inst.value_reg == Y) value = y;
			else if (inst.value_reg == Z) value = z;
			else if (inst.value_reg == W) value = w;
			else throw std::exception();
		}
		else if (inst.value_type == instruction::LITERAL) value = inst.value;
		else throw std::exception();

		if (inst.op == INPUT) *target = value;
		else if (inst.op == ADD) *target += value;
		else if (inst.op == MULTIPLY) *target *= value;
		else if (inst.op == DIVIDE) *target /= value;
		else if (inst.op == MODULO) *target %= value;
		else if (inst.op == EQUALS) *target = value == *target;
		else throw std::exception();

		program.pop();
	}
}

// z, num
std::pair<int, size_t> aoc::day_24::calc(int z, size_t i, const std::array<std::pair<int, int>, 14>& pairs)
{
	if (i >= 14)
	{
		return std::make_pair(z == 0 ? 0 : -1, 0);
	}
	const int& a = pairs.at(i).first;
	const int& b = pairs.at(i).second;
	if (a <= 0)
	{
		int w = (z % 26) + a;
		if (w < 1 || w > 9) return std::make_pair(-1, 0);
		const auto res = calc(z / 26, i + 1, pairs);
		if (res.first == -1) return res;
		size_t to_add = w;
		for (size_t j = 0; j < (13 - i); ++j) to_add *= 10ul;
		return std::make_pair(res.first, res.second + to_add);
	}
	else
	{
		for (int w = 9; w > 0; --w)
		{
			int x = (z % 26) + a;
			int nz = z;
			if (x != w)
			{
				nz = z * 26 + w + b;
			}
			const auto res = calc(nz, i + 1, pairs);
			if (res.first == 0)
			{
				size_t to_add = w;
				for (size_t j = 0; j < (13 - i); ++j) to_add *= 10ul;
				return std::make_pair(res.first, res.second + to_add);
			}
		}
		return std::make_pair(-1, 0);
	}
}

std::pair<int, size_t> aoc::day_24::calc_little(int z, size_t i, const std::array<std::pair<int, int>, 14>& pairs)
{
	if (i >= 14)
	{
		return std::make_pair(z == 0 ? 0 : -1, 0);
	}
	const int& a = pairs.at(i).first;
	const int& b = pairs.at(i).second;

	if (a <= 0)
	{
		int w = (z % 26) + a;
		if (w < 1 || w > 9) return std::make_pair(-1, 0);
		const auto res = calc_little(z / 26, i + 1, pairs);
		if (res.first == -1) return res;
		size_t to_add = w;
		for (size_t j = 0; j < (13 - i); ++j) to_add *= 10ul;
		return std::make_pair(res.first, res.second + to_add);
	}
	else
	{
		size_t min = SIZE_T_MAX;
		for (int w = 1; w <= 9; ++w)
		{
			int x = (z % 26) + a;
			int nz = z;
			if (x != w) nz = z * 26 + w + b;
			const auto res = calc_little(nz, i + 1, pairs);
			if (res.first == 0)
			{
				size_t to_add = w;
				for (size_t j = 0; j < (13 - i); ++j) to_add *= 10ul;
				to_add += res.second;
				min = std::min(min, to_add);
			}
		}
		if (min == SIZE_T_MAX) return std::make_pair(-1, 0);
		else return std::make_pair(0, min);
	}
}
