#include "day_03.hpp"

#include <cmath>
#include <iostream>

void aoc::day_03::part_one()
{
	const auto lines = m_input.bits();
	const auto length = lines.at(0).size();

	std::vector<unsigned int> counts(length);
	for (const auto &line : lines)
	{
		for (size_t i = 0; i < length; ++i)
		{
			counts.at(i) += line.at(i);
		}
	}

	const auto half = lines.size() / 2;

	unsigned long gamma = 0;
	unsigned long epsilon = 0;
	for (const auto &count : counts)
	{
		gamma <<= 1;
		epsilon <<= 1;
		gamma += count > half;
		epsilon += count < half;
	}

	std::cout << gamma * epsilon << std::endl;
}

std::vector<bool> aoc::day_03::get_stat(bool use_mcb = true) const
{
	const auto lines = m_input.bits();

	auto current_lines = lines;
	size_t i = 0;

	while (current_lines.size() > 1)
	{
		unsigned int count = 0;
		for (const auto &line : current_lines)
		{
			count += line.at(i);
		}

		const auto most_common_bit = count >= (current_lines.size() / 2.0f);
		std::vector<std::vector<bool>> next_lines;

		for (const auto &line : current_lines)
		{
			if ((line.at(i) == most_common_bit) == use_mcb)
			{
				next_lines.push_back(line);
			}
		}

		current_lines = next_lines;
		++i;
	}

	return current_lines.at(0);
}

unsigned long aoc::day_03::bits_to_ul(std::vector<bool> bits)
{
	unsigned long value = 0;
	for (const auto &bit : bits)
	{
		value <<= 1;
		value += bit;
	}
	return value;
}

void aoc::day_03::part_two()
{
	const auto oxygen = bits_to_ul(get_stat(true));
	const auto co2 = bits_to_ul(get_stat(false));

	std::cout << oxygen * co2 << std::endl;
}
