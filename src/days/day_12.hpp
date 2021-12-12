#pragma once

#include <array>

#include "day.hpp"

namespace aoc
{
	class day_12 : public aoc::day
	{
	public:
		day_12(const aoc::input& input);

		virtual void part_one() override;
		virtual void part_two() override;

	private:
		struct cave
		{
			char id;
			bool large;
			std::string label;
			std::vector<char> linked_caves;
		};

		std::array<cave, CHAR_MAX> m_caves;
	};
}
