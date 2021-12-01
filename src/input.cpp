#include "input.hpp"

#include <fstream>
#include <iostream>
#include <string>

constexpr auto format = "inputs/%s%02d.txt";
aoc::input::input(bool test, int day)
{
	const auto testStr = test ? "test/" : "";
	const auto size = std::snprintf(nullptr, 0, format, testStr, day);
	std::string path(size + 1, '\0');
	std::sprintf(&path[0], format, testStr, day);
	std::ifstream file(path);

	if (file.is_open())
	{
		while (file.good())
		{
			std::string line;
			file >> line;
			if (line != "")
			{
				m_lines.emplace_back(line);
			}
		}
		file.close();
	}
	else
	{
		throw aoc::file_not_found_exception(path);
	}
}

std::vector<int> aoc::input::lines_as_ints()
{
	std::vector<int> lines(m_lines.size());
	for (auto i = 0ul; i < lines.size(); ++i)
	{
		lines.at(i) = stoi(m_lines.at(i));
	}
	return lines;
}
