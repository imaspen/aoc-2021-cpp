#pragma once

#include "day.hpp"

namespace aoc
{
	class day_03 : public aoc::day
	{
	public:
		using day::day;

		virtual void part_one() override;
		virtual void part_two() override;

	private:
		std::vector<bool> get_stat(bool use_mcb) const;
		static unsigned long bits_to_ul(std::vector<bool> bits);
	};
}
