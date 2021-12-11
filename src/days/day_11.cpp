#include "day_11.hpp"

#include <iostream>

aoc::day_11::day_11(const aoc::input& input) : day(input)
{
	const auto digits = m_input.digits();
	for (size_t y = 0; y < 10; ++y)
	{
		const auto& digit_line = digits.at(y);
		auto& line = m_grid.at(y);
		for (size_t x = 0; x < 10; ++x)
		{
			line.at(x) = digit_line.at(x);
		}
	}
}


void aoc::day_11::part_one()
{
	size_t count = 0;
	for (size_t step = 0; step < 100; ++step)
	{
		for (size_t y = 0; y < 10; ++y)
		{
			for (size_t x = 0; x < 10; ++x)
			{
				increment_point(x, y);
			}
		}
		count += get_flashes();
	}
	std::cout << count << std::endl;
}

void aoc::day_11::part_two()
{
	size_t step = 0;
	while (true)
	{
		++step;
		for (size_t y = 0; y < 10; ++y)
		{
			for (size_t x = 0; x < 10; ++x)
			{
				increment_point(x, y);
			}
		}
		size_t count = get_flashes();
		if (count == 100) break;
	}
	std::cout << step << std::endl;
}

void aoc::day_11::increment_point(size_t x, size_t y)
{
	if (x >= 10 || y >= 10) return;
	const auto new_val = ++m_grid.at(y).at(x);
	if (new_val == 10)
	{
		for (int dy = -1; dy <= 1; ++dy)
		{
			for (int dx = -1; dx <= 1; ++dx)
			{
				if (dx == 0 && dy == 0) continue;
				increment_point(x + dx, y + dy);
			}
		}
	}
}

size_t aoc::day_11::get_flashes()
{
	size_t count = 0;
	for (auto& line : m_grid)
	{
		for (auto& cell : line)
		{
			if (cell >= 10)
			{
				++count;
				cell = 0;
			}
		}
	}
	return count;
}
