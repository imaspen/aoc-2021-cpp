#pragma once

#include <array>

#include "day.hpp"

namespace aoc
{
	class day_11 : public aoc::day
	{
	public:
		day_11(const aoc::input& input);

		virtual void part_one() override;
		virtual void part_two() override;

	private:
		typedef std::pair<size_t, size_t> point;
		typedef std::array<std::array<int, 10>, 10> grid;

		void increment_point(size_t x, size_t y);
		size_t get_flashes();

		grid m_grid;
	};
}
