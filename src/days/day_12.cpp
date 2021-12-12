#include "day_12.hpp"

#include <iostream>
#include <stack>

aoc::day_12::day_12(const aoc::input& input) : day(input)
{
	for (const auto& line : m_input.strings())
	{
		const auto delim_pos = line.find("-");
		const auto label_1 = line.substr(0, delim_pos);
		const auto label_2 = line.substr(delim_pos + 1);
		const auto id_1 = label_1 == "start" ? '0' : (label_1 == "end" ? '1' : label_1.at(0));
		const auto id_2 = label_2 == "start" ? '0' : (label_2 == "end" ? '1' : label_2.at(0));
		const auto large_1 = id_1 >= 'A' && id_1 <= 'Z';
		const auto large_2 = id_2 >= 'A' && id_2 <= 'Z';

		auto& cave_1 = m_caves.at(id_1);
		auto& cave_2 = m_caves.at(id_2);

		cave_1.id = id_1;
		cave_1.label = label_1;
		cave_1.large = large_1;

		cave_1.linked_caves.emplace_back(id_2);
		cave_2.linked_caves.emplace_back(id_1);

		cave_2.id = id_2;
		cave_2.label = label_2;
		cave_2.large = large_2;
	}
}

void aoc::day_12::part_one()
{
	std::vector<std::string> paths;
	std::stack<std::string> queue({ std::string{ m_caves.at('0').id } });

	while (!queue.empty())
	{
		const auto path = queue.top();
		queue.pop();

		for (const auto& cave : m_caves.at(path.back()).linked_caves)
		{
			if (cave == '1')
			{
				paths.emplace_back(path + '1');
			}
			else if (m_caves.at(cave).large || path.find(cave) == std::string::npos)
			{
				queue.emplace(path + cave);
			}
		}
	}

	std::cout << paths.size() << std::endl;
}

void aoc::day_12::part_two()
{
	std::vector<std::string> paths;
	std::stack<std::pair<std::string, bool>> queue({ std::make_pair(std::string{ m_caves.at('0').id }, false) });

	while (!queue.empty())
	{
		const auto path_double_visit = queue.top();
		const auto& path = path_double_visit.first;
		const auto& double_visit = path_double_visit.second;
		queue.pop();

		for (const auto& cave : m_caves.at(path.back()).linked_caves)
		{
			if (cave == '0')
			{
				continue;
			}
			if (cave == '1')
			{
				paths.emplace_back(path + '1');
			}
			else if (m_caves.at(cave).large)
			{
				queue.emplace(std::make_pair(path + cave, double_visit));
			}
			else if (path.find(cave) == std::string::npos)
			{
				queue.emplace(std::make_pair(path + cave, double_visit));
			}
			else if (!double_visit)
			{
				queue.emplace(std::make_pair(path + cave, true));
			}
		}
	}

	std::cout << paths.size() << std::endl;
}
