#include "day_20.hpp"

#include <iostream>

aoc::day_20::day_20(const input& input) : day(input)
{
	const auto lines = m_input.strings();
	const auto enhancer = lines.at(0);

	m_enhancer = 0;
	for (const auto& c : enhancer)
	{
		m_enhancer >>= 1;
		m_enhancer.set(m_enhancer.size() - 1, c == '#');
	}

	m_image.reserve(lines.size() - 1);
	std::vector<bool> next_row;
	for (auto it = ++lines.begin(); it != lines.end(); ++it)
	{
		next_row.clear();
		next_row.reserve(it->size());
		for (const auto& c : *it)
		{
			next_row.emplace_back(c == '#');
		}
		m_image.emplace_back(next_row);
	}
}

void aoc::day_20::part_one()
{
	for (size_t i = 0; i < 2; ++i) enhance();
	size_t count = 0;
	for (const auto& row : m_image)
	{
		for (const auto& on : row)
		{
			count += on;
		}
	}
	std::cout << count << std::endl;
}

void aoc::day_20::part_two()
{
	for (size_t i = 0; i < 50; ++i) enhance();
	size_t count = 0;
	for (const auto& row : m_image)
	{
		for (const auto& on : row)
		{
			count += on;
		}
	}
	std::cout << count << std::endl;
}

void aoc::day_20::enhance()
{
	m_image_next.clear();
	m_image_next.reserve(m_image.size() + 2);
	size_t row_size = m_image.at(0).size();
	std::vector<bool> next_row;
	for (int y = -1; y <= static_cast<int>(m_image.size()); ++y)
	{
		next_row.clear();
		next_row.reserve(row_size + 2);
		for (int x = -1; x <= static_cast<int>(row_size); ++x)
		{
			size_t sum = 0;
			for (int dy = -1; dy <= 1; ++dy)
			{
				for (int dx = -1; dx <= 1; ++dx)
				{
					size_t ny = y + dy, nx = x + dx;
					sum <<= 1;
					if (ny >= m_image.size() || nx >= row_size) sum += m_inactive_lit;
					else sum += m_image.at(ny).at(nx);
				}
			}
			next_row.emplace_back(m_enhancer.test(sum));
		}
		m_image_next.emplace_back(next_row);
	}
	m_image.swap(m_image_next);
	m_inactive_lit = m_enhancer.test(m_inactive_lit * 0x1ff);
}
