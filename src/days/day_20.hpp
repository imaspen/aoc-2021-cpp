#pragma once

#include <bitset>

#include "day.hpp"

namespace aoc
{
	class day_20 : public aoc::day
	{
	public:
		day_20(const input& input);

		virtual void part_one() override;
		virtual void part_two() override;

	private:
		void enhance();

		std::bitset<0x200> m_enhancer;
		std::vector<std::vector<bool>> m_image, m_image_next;
		bool m_inactive_lit;
	};
}
