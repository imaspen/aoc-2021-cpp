#pragma once

#include <utility>

#include "day.hpp"

namespace aoc
{
	class day_13 : public aoc::day
	{
	public:
		day_13(const aoc::input& input);

		virtual void part_one() override;
		virtual void part_two() override;

	private:
		enum direction
		{
			X = 'x',
			Y = 'y',
		};
		struct point
		{
			point(size_t x, size_t y) : x(x), y(y) {};
			size_t x, y;
		};
		struct fold
		{
			fold(direction d, size_t l) : direction(d), line(l) {};
			direction direction;
			size_t line;
		};

		void do_fold(const fold& fold);

		std::vector<std::vector<bool>> m_grid, m_next_grid;
		std::vector<fold> m_folds;
	};
}
