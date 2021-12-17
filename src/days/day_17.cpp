#include "day_17.hpp"

#include <iostream>

aoc::day_17::day_17(const aoc::input& input) : day(input)
{
	auto line = m_input.strings().at(0).substr(15);
	size_t next_pos = 0;
	min_x = std::stoi(line, &next_pos);
	line = line.substr(next_pos + 2);
	max_x = std::stoi(line, &next_pos);
	line = line.substr(next_pos + 4);
	min_y = std::stoi(line, &next_pos);
	line = line.substr(next_pos + 2);
	max_y = std::stoi(line);
}

void aoc::day_17::part_one()
{
	int max_height = 0;
	for (int start_vy = 0; start_vy < 1000000; ++start_vy)
	{
		int y = 0;
		int vy = start_vy;
		int curr_max_height = 0;
		while (true)
		{
			y += vy--;
			curr_max_height = std::max(curr_max_height, y);
			if (y <= max_y)
			{
				if (y >= min_y) max_height = std::max(max_height, curr_max_height);
				break;
			}
		}
	}
	std::cout << max_height << std::endl;
}

void aoc::day_17::part_two()
{
	std::vector<int> possible_start_vxs, possible_start_vys;
	possible_start_vxs.reserve(1024);
	possible_start_vys.reserve(1024);
	for (int start_vy = min_y; start_vy < 100000; ++start_vy)
	{
		int y = 0, vy = start_vy;
		while (true)
		{
			y += vy--;
			if (y <= max_y)
			{
				if (y >= min_y) possible_start_vys.emplace_back(start_vy);
				break;
			}
		}
	}
	for (int start_vx = 0; start_vx <= max_x; ++start_vx)
	{
		int x = 0, vx = start_vx;
		while (true)
		{
			x += vx;
			if (vx > 0) --vx;
			if (vx == 0 && x < min_x) break;
			if (x >= min_x)
			{
				if (x <= max_x) possible_start_vxs.emplace_back(start_vx);
				break;
			}
		}
	}
	size_t count = 0;
	for (const auto& start_vy : possible_start_vys)
	{
		for (const auto& start_vx : possible_start_vxs)
		{
			int x = 0, y = 0, vx = start_vx, vy = start_vy;
			while (true)
			{
				x += vx;
				y += vy--;
				if (vx > 0) --vx;
				if (x >= min_x && x <= max_x && y >= min_y && y <= max_y)
				{
					++count;
					break;
				}
				if (x >= max_x || y <= min_y) break;
			}
		}
	}
	std::cout << count << std::endl;
}
