#include "day_07.hpp"

#include <algorithm>
#include <iostream>

void aoc::day_07::part_one()
{
	m_crabs = m_input.csv_ints();
	std::sort(m_crabs.begin(), m_crabs.end());
	m_min_position = m_crabs.at(m_crabs.size() / 2);
	m_min_usage = calculate_fuel_usage(m_min_position);

	if (calculate_fuel_usage(m_min_position + 1) <= m_min_usage)
	{
		while (true)
		{
			const auto usage = calculate_fuel_usage(m_min_position + 1);
			if (usage > m_min_usage) break;
			m_min_usage = usage;
			++m_min_position;
		}
	}
	if (calculate_fuel_usage(m_min_position - 1) <= m_min_usage)
	{
		while (true)
		{
			const auto usage = calculate_fuel_usage(m_min_position - 1);
			if (usage > m_min_usage) break;
			m_min_usage = usage;
			--m_min_position;
		}
	}

	std::cout << m_min_usage << std::endl;
}

void aoc::day_07::part_two()
{
	m_crabs = m_input.csv_ints();
	std::sort(m_crabs.begin(), m_crabs.end());
	m_min_position = m_crabs.at(m_crabs.size() / 2);
	m_min_usage = calculate_complex_fuel_usage(m_min_position);

	if (calculate_complex_fuel_usage(m_min_position + 1) <= m_min_usage)
	{
		while (true)
		{
			const auto usage = calculate_complex_fuel_usage(m_min_position + 1);
			if (usage > m_min_usage) break;
			m_min_usage = usage;
			++m_min_position;
		}
	}
	if (calculate_complex_fuel_usage(m_min_position - 1) <= m_min_usage)
	{
		while (true)
		{
			const auto usage = calculate_complex_fuel_usage(m_min_position - 1);
			if (usage > m_min_usage) break;
			m_min_usage = usage;
			--m_min_position;
		}
	}

	std::cout << m_min_usage << std::endl;
}

int aoc::day_07::calculate_fuel_usage(int position)
{
	int usage = 0;
	for (const auto& crab : m_crabs)
	{
		usage += std::abs(crab - position);
	}
	return usage;
}

int aoc::day_07::calculate_complex_fuel_usage(int position)
{
	int usage = 0;
	for (const auto& crab : m_crabs)
	{
		const int distance = std::abs(crab - position);
		usage += (distance * (distance + 1)) / 2;
	}
	return usage;
}
