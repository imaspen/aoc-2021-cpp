#include <iostream>
#include <string>

#include "days/day1.cpp"

void print_usage()
{
	std::cout << "Usage: aoc\n";
	std::cout << "\t-t\t\tRun with test input\n";
	std::cout << "\t-d<day>\t\tRequired. Day number (1-25)\n";
	std::cout << "\t-p<part>\tRequired. Part number (1-2)" << std::endl;
}

int main(int argc, const char *argv[])
{
	int day = 0;
	int part = 0;
	bool test = false;

	for (int i = 1; i < argc; ++i)
	{
		if (argv[i][0] != '-')
		{
			std::cout << "Invalid argument: " << argv[i] << std::endl;
			print_usage();
			return 1;
		}

		switch (argv[i][1])
		{
		case 't':
			test = true;
			continue;
		case 'd':
			day = atoi(&argv[i][2]);
			if (day < 1 || day > 25)
			{
				std::cout << "Invalid day passed: " << &argv[i][2] << std::endl;
				print_usage();
				return 1;
			}
			continue;
		case 'p':
			part = atoi(&argv[i][2]);
			if (part < 1 || part > 2)
			{
				std::cout << "Invalid part passed: " << &argv[i][2] << std::endl;
				print_usage();
				return 1;
			}
			continue;
		default:
			std::cout << "Invalid argument: " << argv[i] << std::endl;
			print_usage();
			return 1;
		}
	}

	if (day == 0)
	{
		std::cout << "Day not passed." << std::endl;
		print_usage();
		return 1;
	}

	if (part == 0)
	{
		std::cout << "Part not passed." << std::endl;
		print_usage();
		return 1;
	}

	switch (day)
	{
	case 1:
		part == 1 ? day1part1() : day1part2();
		return 0;
	default:
		std::cout << "Unimplemented." << std::endl;
		return 1;
	}
}
