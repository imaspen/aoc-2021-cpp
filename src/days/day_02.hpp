#pragma once

#include "day.hpp"

namespace aoc
{
	class unrecognized_dir_exception : public std::exception
	{
	public:
		unrecognized_dir_exception(std::string dir) : dir(dir){};

		std::string dir;
	};

	class day_02 : public aoc::day
	{
	public:
		using day::day;

		virtual void part_one() override;
		virtual void part_two() override;
	};
}
