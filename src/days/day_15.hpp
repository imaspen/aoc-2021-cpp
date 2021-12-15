#pragma once

#include <map>
#include <set>
#include <utility>
#include <vector>

#include "day.hpp"

namespace aoc
{
	class day_15 : public aoc::day
	{
	public:
		day_15(const aoc::input& input);

		virtual void part_one() override;
		virtual void part_two() override;

	private:
		typedef std::pair<size_t, size_t> point;

		bool is_done();
		std::vector<std::pair<aoc::day_15::point, int>> get_adjacencies(const point& p, int risk_level, bool big = false);

		std::vector<std::vector<int>> m_risk_levels, m_big_risk_levels;
		std::map<int, std::map<point, std::set<point>>> m_expanded;
		point m_end_point;
	};
}
