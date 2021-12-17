#pragma once

#include "day.hpp"

namespace aoc
{
	class day_17 : public aoc::day
	{
	public:
		day_17(const aoc::input& input);

		virtual void part_one() override;
		virtual void part_two() override;

	private:
		int min_x, max_x, min_y, max_y;
	};
}
