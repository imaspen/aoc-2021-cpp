#pragma once

#include <array>
#include <set>
#include <string>
#include <vector>

namespace aoc
{
	class board
	{
	public:
		board(std::array<std::array<unsigned long, 5>, 5> rows) : rows(rows) {};
		board(const std::vector<std::string>& strings);

		std::array<std::array<unsigned long, 5>, 5> rows;

		unsigned long is_won(const std::set<unsigned long>& called) const;
		unsigned long board_score(const std::set<unsigned long>& called) const;

	};
}
