#include "day_06.hpp"

#include <array>
#include <iostream>

void aoc::day_06::part_one()
{
	std::vector<int> cooldowns = m_input.csv_ints();
	for (size_t i = 0; i < 80; ++i)
	{
		std::vector<int> next_cooldowns;
		for (auto cooldown : cooldowns)
		{
			if (--cooldown < 0)
			{
				next_cooldowns.emplace_back(8);
				next_cooldowns.emplace_back(6);
			}
			else
			{
				next_cooldowns.emplace_back(cooldown);
			}
		}
		cooldowns = next_cooldowns;
	}

	std::cout << cooldowns.size() << std::endl;
}

void aoc::day_06::part_two()
{
	std::vector<int> initial_cooldowns = m_input.csv_ints();
	std::array<unsigned long, 9> cooldowns_count, next_cooldowns_count;

	cooldowns_count.fill(0);
	for (const auto& cooldown : initial_cooldowns)
	{
		cooldowns_count.at(cooldown)++;
	}

	for (size_t i = 0; i < 256; ++i)
	{
		next_cooldowns_count.fill(0);

		for (size_t j = 0; j < 9; ++j)
		{
			if (j == 0)
			{
				next_cooldowns_count.at(6) += cooldowns_count.at(j);
				next_cooldowns_count.at(8) += cooldowns_count.at(j);
			}
			else
			{
				next_cooldowns_count.at(j - 1) += cooldowns_count.at(j);
			}
		}

		cooldowns_count.swap(next_cooldowns_count);
	}

	size_t count = 0;
	for (size_t i = 0; i < 9; ++i)
	{
		count += cooldowns_count.at(i);
	}

	std::cout << count << std::endl;
}
