#include "day_10.hpp"

#include <iostream>
#include <map>
#include <stack>

void aoc::day_10::part_one()
{
	const auto lines = m_input.strings();
	const std::map<char, int> values({
		std::make_pair(')', 3),
		std::make_pair(']', 57),
		std::make_pair('}', 1197),
		std::make_pair('>', 25137) });

	unsigned long count = 0;
	for (const auto& line : lines)
	{
		std::stack<char> stack;
		bool success = true;
		for (const auto& c : line)
		{
			switch (c)
			{
			case '(':
			case '[':
			case '{':
			case '<':
				stack.emplace(c);
				continue;
			case ')':
				if (stack.top() != '(')
				{
					success = false;
					count += values.at(c);
				}
				break;
			case ']':
				if (stack.top() != '[')
				{
					success = false;
					count += values.at(c);
				}
				break;
			case '}':
				if (stack.top() != '{')
				{
					success = false;
					count += values.at(c);
				}
				break;
			case '>':
				if (stack.top() != '<')
				{
					success = false;
					count += values.at(c);
				}
				break;
			default:
				throw std::exception();
			}
			if (!success) break;
			stack.pop();
		}
	}

	std::cout << count << std::endl;
}

void aoc::day_10::part_two()
{
	const auto lines = m_input.strings();
	const std::map<char, int> values({
		std::make_pair('(', 1),
		std::make_pair('[', 2),
		std::make_pair('{', 3),
		std::make_pair('<', 4) });

	std::vector<unsigned long> scores;
	for (const auto& line : lines)
	{
		std::stack<char> stack;
		bool success = true;
		for (const auto& c : line)
		{
			switch (c)
			{
			case '(':
			case '[':
			case '{':
			case '<':
				stack.emplace(c);
				continue;
			case ')':
				if (stack.top() != '(') success = false;
				break;
			case ']':
				if (stack.top() != '[') success = false;
				break;
			case '}':
				if (stack.top() != '{') success = false;
				break;
			case '>':
				if (stack.top() != '<') success = false;
				break;
			default:
				throw std::exception();
			}
			if (!success) break;
			stack.pop();
		}
		if (success)
		{
			unsigned long product = 0;
			while (!stack.empty())
			{
				const auto c = stack.top();
				stack.pop();
				product *= 5;
				product += values.at(c);
			}
			scores.emplace_back(product);
		}
	}

	std::sort(scores.begin(), scores.end());
	const auto count = scores.at(scores.size() / 2);

	std::cout << count << std::endl;
}
