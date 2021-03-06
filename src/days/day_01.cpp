#include "day_01.hpp"

#include <iostream>

void aoc::day_01::part_one()
{
	const std::vector<int> lines = m_input.ints();

	int last_value = lines.at(0);
	int count = 0;

	for (size_t i = 1; i < lines.size(); ++i)
	{
		const int current_value = lines.at(i);
		if (current_value > last_value)
		{
			++count;
		}
		last_value = current_value;
	}

	std::cout << count << std::endl;
}

void aoc::day_01::part_two()
{
	const std::vector<int> lines = m_input.ints();

	int last_value = lines.at(0) + lines.at(1) + lines.at(2);
	int count = 0;

	for (size_t i = 3; i < lines.size(); ++i)
	{
		const int current_value = lines.at(i) + lines.at(i - 1) + lines.at(i - 2);
		if (current_value > last_value)
		{
			++count;
		}
		last_value = current_value;
	}

	std::cout << count << std::endl;
}
