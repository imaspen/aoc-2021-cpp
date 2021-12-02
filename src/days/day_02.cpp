#include "day_02.hpp"

#include <iostream>
#include <string>

void aoc::day_02::part_one()
{
	const auto lines = m_input.string_int_tuples();

	int depth = 0;
	int hpos = 0;

	std::string dir;
	int units;
	for (const auto &line : lines)
	{
		std::tie(dir, units) = line;
		if (dir == "forward")
		{
			hpos += units;
		}
		else if (dir == "up")
		{
			depth -= units;
		}
		else if (dir == "down")
		{
			depth += units;
		}
		else
		{
			throw aoc::unrecognized_dir_exception(dir);
		}

		if (depth < 0)
		{
			std::cout << "Depth less than 0" << std::endl;
		}
	}

	std::cout << hpos * depth << std::endl;
}

void aoc::day_02::part_two()
{
	const auto lines = m_input.string_int_tuples();

	int aim = 0;
	int depth = 0;
	int hpos = 0;

	std::string dir;
	int units;
	for (const auto &line : lines)
	{
		std::tie(dir, units) = line;
		if (dir == "forward")
		{
			hpos += units;
			depth += aim * units;
		}
		else if (dir == "up")
		{
			aim -= units;
		}
		else if (dir == "down")
		{
			aim += units;
		}
		else
		{
			throw aoc::unrecognized_dir_exception(dir);
		}

		if (depth < 0)
		{
			std::cout << "Depth less than 0" << std::endl;
		}
	}

	std::cout << hpos * depth << std::endl;
}
