#pragma once

#include <queue>
#include <vector>

#include "day.hpp"
#include "../objects/board.hpp"

namespace aoc
{
	class day_04 : public aoc::day
	{
	public:
		day_04(aoc::input const& input);
		virtual ~day_04() = default;

		virtual void part_one() override;
		virtual void part_two() override;

	private:
		std::queue<unsigned long> m_to_call;
		std::vector<aoc::board> m_boards;
	};
}
