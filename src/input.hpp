#pragma once

#include <string>
#include <vector>

namespace aoc
{
	class file_not_found_exception : public std::exception
	{
	public:
		file_not_found_exception(const std::string &path) : path(path){};
		const std::string path;
	};

	class input
	{
	public:
		input(bool test, int day);

		std::vector<std::string> lines_as_strings() { return m_lines; }

		std::vector<int> lines_as_ints();

	private:
		std::vector<std::string> m_lines;
	};
};
