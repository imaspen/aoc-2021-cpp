#pragma once

#include <string>
#include <tuple>
#include <vector>

namespace aoc
{
	class file_not_found_exception : public std::exception
	{
	public:
		file_not_found_exception(const std::string& path) : path(path) {};
		const std::string path;
	};

	class input
	{
	public:
		input(bool test, int day);

		std::vector<std::string> strings(const bool raw = false) const;

		std::vector<int> ints() const;

		std::vector<int> csv_ints() const;

		std::vector<std::vector<int>> digits() const;

		std::vector<std::tuple<std::string, std::string>> string_string_tuples() const;

		std::vector<std::tuple<std::string, int>> string_int_tuples() const;

		std::vector<std::vector<bool>> bits() const;

	private:
		std::vector<std::string> m_lines;
		std::vector<std::string> m_lines_raw;
	};
};
