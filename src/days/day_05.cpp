#include "day_05.hpp"

#include <algorithm>
#include <iostream>

aoc::day_05::day_05(const aoc::input& input) : day(input)
{
	const auto& lines = m_input.strings();
	size_t max_x = 0, max_y = 0;
	std::vector<vent> vents;
	for (const auto& line : lines)
	{
		const auto i = line.find(" -> ");
		const auto p1_str = line.substr(0, i);
		const auto p2_str = line.substr(i + 4);

		size_t next = 0;
		const auto p1_x = std::stoul(p1_str, &next);
		const auto p1_y = std::stoul(p1_str.substr(next + 1));
		const auto p2_x = std::stoul(p2_str, &next);
		const auto p2_y = std::stoul(p2_str.substr(next + 1));

		max_x = std::max(max_x, p1_x);
		max_x = std::max(max_x, p2_x);
		max_y = std::max(max_y, p1_y);
		max_y = std::max(max_y, p2_y);

		vents.push_back({ .p1 = {.x = p1_x, .y = p1_y}, .p2 = {.x = p2_x, .y = p2_y} });
	}

	for (size_t y = 0; y <= max_y; ++y)
	{
		m_field.emplace_back(max_x + 1);
		m_field_no_diagonals.emplace_back(max_x + 1);
	}

	for (const auto& vent : vents)
	{
		if (vent.p1.x == vent.p2.x && vent.p1.y != vent.p2.y)
		{
			// vertical line
			const auto x = vent.p1.x;
			for (size_t y = std::min(vent.p1.y, vent.p2.y); y <= std::max(vent.p1.y, vent.p2.y); ++y)
			{
				m_field.at(y).at(x)++;
				m_field_no_diagonals.at(y).at(x)++;
			}
		}
		else if (vent.p1.x != vent.p2.x && vent.p1.y == vent.p2.y)
		{
			// horizontal line
			const auto y = vent.p1.y;
			for (size_t x = std::min(vent.p1.x, vent.p2.x); x <= std::max(vent.p1.x, vent.p2.x); ++x)
			{
				m_field.at(y).at(x)++;
				m_field_no_diagonals.at(y).at(x)++;
			}
		}
		else
		{
			// diagonal line
			const auto p1 = vent.p1.y < vent.p2.y ? vent.p1 : vent.p2;
			const auto p2 = vent.p1.y < vent.p2.y ? vent.p2 : vent.p1;
			if (p1.x < p2.x)
			{
				// diagonal right
				for (size_t x = p1.x, y = p1.y; y <= p2.y; ++x, ++y)
				{
					m_field.at(y).at(x)++;
				}
			}
			else
			{
				// diagonal left
				for (size_t x = p1.x, y = p1.y; y <= p2.y; --x, ++y)
				{
					m_field.at(y).at(x)++;
				}
			}
		}
	}
}

void aoc::day_05::print_field()
{
	for (const auto& row : m_field)
	{
		for (const auto& point : row)
		{
			std::cout << point;
		}
		std::cout << '\n';
	}
	std::cout << std::endl;
}

void aoc::day_05::part_one()
{
	size_t count = 0;
	for (const auto& row : m_field_no_diagonals)
	{
		for (const auto& point : row)
		{
			if (point > 1)
			{
				++count;
			}
		}
	}
	std::cout << count << std::endl;
}

void aoc::day_05::part_two()
{
	size_t count = 0;
	for (const auto& row : m_field)
	{
		for (const auto& point : row)
		{
			if (point > 1)
			{
				++count;
			}
		}
	}
	std::cout << count << std::endl;
}
