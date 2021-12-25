#pragma once

#include "day.hpp"

namespace aoc
{
	class day_25 : public aoc::day
	{
	public:
		day_25(const input& input);

		virtual void part_one() override;
		virtual void part_two() override;

	private:
		enum direction
		{
			EMPTY = '.',
			EAST = '>',
			SOUTH = 'v',
		};

		std::vector<std::vector<direction>> m_grid, m_grid_next;
	};
}
