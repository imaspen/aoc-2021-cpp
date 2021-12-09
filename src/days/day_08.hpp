#pragma once

#include <array>
#include <bitset>
#include <utility>
#include <vector>

#include "day.hpp"

namespace aoc
{
	class day_08 : public aoc::day
	{
	public:
		day_08(const aoc::input& input);

		virtual void part_one() override;
		virtual void part_two() override;

	private:
		typedef std::bitset<7> signal;
		typedef std::array<signal, 10> signal_patterns;
		typedef std::array<signal, 4> output_digits;
		typedef std::pair<signal_patterns, output_digits> entry;
		std::vector<entry> m_entries;
	};
}
