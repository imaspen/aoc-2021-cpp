#include "day_25.hpp"

#include <iostream>

aoc::day_25::day_25(const input& input) : day(input)
{
	std::vector<direction> row;
	for (const auto& line : m_input.strings())
	{
		row.clear();
		row.reserve(line.size());
		for (const auto& c : line) row.emplace_back(static_cast<direction>(c));
		m_grid.emplace_back(row);
	}
	m_grid_next = m_grid;
}

void aoc::day_25::part_one()
{
	size_t steps = 0;
	bool any_moved = true;
	while (any_moved)
	{
		++steps;
		any_moved = false;
		for (size_t y = 0; y < m_grid.size(); ++y)
		{
			const auto& row = m_grid.at(y);
			auto& row_next = m_grid_next.at(y);
			for (size_t x = 0; x < row.size(); ++x)
			{
				const auto& d = row.at(x);
				if (d == EAST)
				{
					const auto nx = (x < row.size() - 1) ? x + 1 : 0;
					if (row.at(nx) == EMPTY)
					{
						row_next.at(nx) = d;
						row_next.at(x) = EMPTY;
						any_moved = true;
					}
				}
			}
		}
		m_grid = m_grid_next;
		for (size_t y = 0; y < m_grid.size(); ++y)
		{
			const auto& row = m_grid.at(y);
			auto& row_next = m_grid_next.at(y);
			for (size_t x = 0; x < row.size(); ++x)
			{
				const auto& d = row.at(x);
				if (d == SOUTH)
				{
					const auto ny = (y < m_grid.size() - 1) ? y + 1 : 0;
					if (m_grid.at(ny).at(x) == EMPTY)
					{
						m_grid_next.at(ny).at(x) = d;
						row_next.at(x) = EMPTY;
						any_moved = true;
					}
				}
			}
		}
		m_grid = m_grid_next;
	}

	std::cout << steps << std::endl;
}

void aoc::day_25::part_two()
{
	std::cout << "Merry Christmas! 🎄" << std::endl;
}
