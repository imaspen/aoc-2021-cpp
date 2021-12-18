#pragma once

#include <memory>
#include <vector>

#include "day.hpp"

namespace aoc
{
	class day_18 : public aoc::day
	{
	public:
		day_18(const aoc::input& input);

		virtual void part_one() override;
		virtual void part_two() override;

	private:
		enum number_type
		{
			PAIR,
			VALUE,
		};
		enum side
		{
			LEFT,
			RIGHT,
		};
		struct snail_number
		{
			number_type lhs_type, rhs_type;
			std::shared_ptr<snail_number> lhs_pair, rhs_pair, parent_number;
			side parent_side;
			int lhs_value, rhs_value;

			bool try_explode(size_t depth = 0);
			void explode_left(const int val);
			void explode_right(const int val);

			bool try_split(std::shared_ptr<snail_number> shared_this);

			unsigned long get_magnitude();

			void print();
		};

		static std::shared_ptr<snail_number> parse_line(std::string line);

		std::vector<std::shared_ptr<snail_number>> m_numbers;
	};
}
