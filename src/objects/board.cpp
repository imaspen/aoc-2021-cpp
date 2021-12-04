#include "board.hpp"

aoc::board::board(const std::vector<std::string>& strings)
{
	for (size_t y = 0; y < rows.size(); ++y)
	{
		auto& row = rows.at(y);
		auto str = strings.at(y);
		size_t next_pos = 0;
		for (auto& cell : row)
		{
			str = str.substr(next_pos);
			cell = std::stoul(str, &next_pos);
		}
	}
}

unsigned long aoc::board::is_won(const std::set<unsigned long>& called) const
{
	bool is_won;
	for (const auto& row : rows)
	{
		is_won = true;
		for (const auto& cell : row)
		{
			if (called.count(cell) == 0)
			{
				is_won = false;
				break;
			}
		}
		if (is_won)
		{
			break;
		}
	}

	if (is_won)
	{
		return board_score(called);
	}

	for (size_t x = 0; x < rows.at(0).size(); ++x)
	{
		is_won = true;
		for (size_t y = 0; y < rows.size(); ++y)
		{
			if (called.count(rows.at(y).at(x)) == 0)
			{
				is_won = false;
				break;
			}
		}
		if (is_won)
		{
			break;
		}
	}

	if (is_won)
	{
		return board_score(called);
	}

	return 0;
}

unsigned long aoc::board::board_score(const std::set<unsigned long>& called) const
{
	unsigned long total = 0;
	for (const auto& row : rows)
	{
		for (const auto& cell : row)
		{
			if (called.count(cell) == 0)
			{
				total += cell;
			}
		}
	}
	return total;
}
