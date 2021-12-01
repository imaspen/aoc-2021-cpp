#pragma once

#include "day.hpp"

namespace aoc
{
	class day_01 : public aoc::day
	{
	public:
		day_01(aoc::input const &input) : day(input){};

		virtual void part_one() override;
		virtual void part_two() override;
	};
}
