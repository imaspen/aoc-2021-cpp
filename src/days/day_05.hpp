#pragma once

#include "day.hpp"

namespace aoc
{
	class day_05 : public aoc::day
	{
	public:
		day_05(const aoc::input& m_input);

		virtual void part_one() override;
		virtual void part_two() override;

	private:
		struct point
		{
			size_t x, y;
		};
		struct vent
		{
			point p1, p2;
		};

		void print_field();

		typedef std::vector<std::vector<unsigned int>> field;

		field m_field, m_field_no_diagonals;
	};
}
