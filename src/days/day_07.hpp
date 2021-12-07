#pragma once

#include "day.hpp"

namespace aoc
{
	class day_07 : public aoc::day
	{
	public:
		using day::day;

		virtual void part_one() override;
		virtual void part_two() override;

	private:
		int calculate_fuel_usage(int position);
		int calculate_complex_fuel_usage(int position);

		std::vector<int> m_crabs;
		int m_min_position, m_min_usage;
	};
}
