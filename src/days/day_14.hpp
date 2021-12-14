#pragma once

#include <map>
#include <string>
#include <utility>

#include "day.hpp"

namespace aoc
{
	class day_14 : public aoc::day
	{
	public:
		day_14(const aoc::input& input);

		virtual void part_one() override;
		virtual void part_two() override;

	private:
		void step();
		void smart_step();

		std::map<char, std::map<char, char>> m_mappings;
		std::string m_polymer, m_next_polymer;
		std::map<char, std::map<char, size_t>> m_polymer_pair_counts, m_next_polymer_pair_counts;
	};
}
