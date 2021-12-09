#include "day_09.hpp"

#include <algorithm>
#include <iostream>

aoc::day_09::day_09(const aoc::input& input) : aoc::day(input)
{
	const auto lines = m_input.strings();
	for (const auto& line : lines)
	{
		row row;
		for (const auto& c : line) row.emplace_back(c - '0');
		m_floor.emplace_back(row);
	}
}

void aoc::day_09::part_one()
{
	unsigned int sum = 0;
	for (size_t y = 0; y < m_floor.size(); ++y)
	{
		const auto& row = m_floor.at(y);
		for (size_t x = 0; x < row.size(); ++x)
		{
			if (is_low_point(x, y)) sum += 1 + row.at(x);
		}
	}
	std::cout << sum << std::endl;
}

void aoc::day_09::part_two()
{
	std::set<point> low_points;
	for (size_t y = 0; y < m_floor.size(); ++y)
	{
		const auto& row = m_floor.at(y);
		for (size_t x = 0; x < row.size(); ++x)
		{
			if (is_low_point(x, y)) low_points.emplace(x, y);
		}
	}

	std::vector<size_t> basin_sizes;
	for (const auto& point : low_points)
	{
		std::set<aoc::day_09::point> basin;
		expand_basin(point, basin);
		basin_sizes.emplace_back(basin.size());
	}
	std::sort(basin_sizes.begin(), basin_sizes.end(), std::greater<int>());
	std::cout << basin_sizes.at(0) * basin_sizes.at(1) * basin_sizes.at(2) << std::endl;
}

bool aoc::day_09::is_low_point(size_t x, size_t y)
{
	const auto height = m_floor.at(y).at(x);
	if (x > 0 && m_floor.at(y).at(x - 1) <= height) return false;
	if (x + 1 < m_floor.at(y).size() && m_floor.at(y).at(x + 1) <= height) return false;
	if (y > 0 && m_floor.at(y - 1).at(x) <= height) return false;
	if (y + 1 < m_floor.size() && m_floor.at(y + 1).at(x) <= height) return false;
	return true;
}

void aoc::day_09::expand_basin(aoc::day_09::point point, std::set<aoc::day_09::point>& basin)
{
	if (point.second >= m_floor.size()) return;
	if (point.first >= m_floor.at(point.second).size()) return;
	if (basin.count(point) == 1) return;

	const auto height = m_floor.at(point.second).at(point.first);

	if (height == 9) return;

	basin.insert(point);

	expand_basin({ point.first + 1, point.second }, basin);
	expand_basin({ point.first - 1, point.second }, basin);
	expand_basin({ point.first, point.second + 1 }, basin);
	expand_basin({ point.first, point.second - 1 }, basin);
}
