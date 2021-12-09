#pragma once

#include <set>
#include <utility>
#include <vector>

#include "day.hpp"

namespace aoc
{
	class day_09 : public aoc::day
	{
	public:
		day_09(const aoc::input& input);

		virtual void part_one() override;
		virtual void part_two() override;

	private:
		typedef std::pair<size_t, size_t> point;
		typedef std::vector<unsigned int> row;
		typedef std::vector<row> floor;

		bool is_low_point(size_t x, size_t y);
		void expand_basin(aoc::day_09::point point, std::set<aoc::day_09::point>& basin);

		floor m_floor;
	};
}
