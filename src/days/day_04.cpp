#include "day_04.hpp"

#include <iostream>
#include <set>

aoc::day_04::day_04(aoc::input const& input) : aoc::day(input)
{
	const auto lines = m_input.strings(true);
	auto called_line = lines.at(0);
	size_t next_pos = std::string::npos;
	do {
		called_line = called_line.substr(next_pos + 1);
		m_to_call.emplace(std::stoul(called_line, &next_pos));
	} while (next_pos < called_line.size());

	std::vector<std::string> next_lines;
	for (size_t i = 2; i < lines.size(); ++i)
	{
		const auto& line = lines.at(i);
		if (line != "")
		{
			next_lines.emplace_back(line);
		}
		else if (next_lines.size() > 0)
		{
			m_boards.emplace_back(next_lines);
			next_lines = std::vector<std::string>();
		}
	}
}

void aoc::day_04::part_one()
{
	std::set<unsigned long> called;
	while (!m_to_call.empty())
	{
		const auto call = m_to_call.front();
		m_to_call.pop();
		called.emplace(call);

		for (const auto& board : m_boards)
		{
			const auto score = board.is_won(called);
			if (score > 0)
			{
				std::cout << score * call << std::endl;
				return;
			}
		}
	}
}

void aoc::day_04::part_two()
{
	std::set<unsigned long> called;
	auto boards = m_boards;
	while (!m_to_call.empty())
	{
		const auto call = m_to_call.front();
		m_to_call.pop();
		called.emplace(call);

		// for (const auto& board : boards)
		for (size_t i = 0; i < boards.size(); ++i)
		{
			const auto& board = boards.at(i);
			const auto score = board.is_won(called);
			if (score > 0)
			{
				if (boards.size() > 1)
				{
					boards.erase(boards.begin() + i);
				}
				else
				{
					std::cout << score * call << std::endl;
					return;
				}
			}
		}
	}
}
