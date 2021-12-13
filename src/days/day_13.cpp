#include "day_13.hpp"

#include <iostream>

aoc::day_13::day_13(const aoc::input& input) : day(input)
{
	std::vector<point> points;
	size_t max_x = 0, max_y = 0;
	for (auto line : m_input.strings())
	{
		if (line.at(0) >= '0' && line.at(0) <= '9')
		{
			size_t next_pos;
			size_t x = std::stoul(line, &next_pos);
			size_t y = std::stoul(line.substr(next_pos + 1));
			points.emplace_back(x, y);
		}
		else
		{
			direction d = static_cast<direction>(line.at(11));
			size_t l = std::stoul(line.substr(13));
			if (d == X && l > max_x) max_x = l;
			else if (d == Y && l > max_y) max_y = l;
			m_folds.emplace_back(d, l);
		}
	}

	m_grid.reserve(max_y * 2 + 1);
	for (size_t y = 0; y < max_y * 2 + 1; ++y)
	{
		m_grid.emplace_back(max_x * 2 + 1, false);
	}

	for (const auto& point : points)
	{
		m_grid.at(point.y).at(point.x) = true;
	}
}

void aoc::day_13::part_one()
{
	const auto& fold = m_folds.at(0);

	do_fold(fold);

	size_t count = 0;
	for (const auto& row : m_grid)
	{
		for (const auto& cell : row)
		{
			count += cell;
		}
	}

	std::cout << count << std::endl;
}

void aoc::day_13::part_two()
{
	for (const auto& fold : m_folds) do_fold(fold);

	for (const auto& row : m_grid)
	{
		for (const auto& cell : row)
		{
			std::cout << (cell ? '#' : ' ');
		}
		std::cout << '\n';
	}
	std::cout << std::flush;
}

void aoc::day_13::do_fold(const fold& fold)
{
	m_next_grid.clear();
	if (fold.direction == Y)
	{
		m_next_grid.reserve(fold.line);
		for (size_t y = fold.line; y > 0; --y)
		{
			const auto& row_1 = m_grid.at(fold.line - y);
			const auto& row_2 = m_grid.at(fold.line + y);
			m_next_grid.emplace_back();
			auto& row = m_next_grid.back();
			row.reserve(row_1.size());
			for (size_t x = 0; x < row_1.size(); ++x)
			{
				row.emplace_back(row_1.at(x) || row_2.at(x));
			}
		}
	}
	else
	{
		m_next_grid.reserve(m_grid.size());
		for (const auto& row : m_grid)
		{
			m_next_grid.emplace_back();
			auto& next_row = m_next_grid.back();
			next_row.reserve(fold.line);
			for (size_t x = fold.line; x > 0; --x)
			{
				const auto& cell_1 = row.at(fold.line - x);
				const auto& cell_2 = row.at(fold.line + x);
				next_row.emplace_back(cell_1 || cell_2);
			}
		}
	}
	m_grid.swap(m_next_grid);
}
