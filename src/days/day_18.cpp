#include "day_18.hpp"

#include <iostream>
#include <stack>

aoc::day_18::day_18(const aoc::input& input) : day(input)
{
	const auto lines = m_input.strings();
	m_numbers.reserve(lines.size());
	for (auto line : lines)
	{
		m_numbers.emplace_back(parse_line(line));
	}
}

void aoc::day_18::part_one()
{
	std::shared_ptr<snail_number> sum;
	for (const auto& number : m_numbers)
	{
		if (!sum) sum = number;
		else
		{
			auto new_sum = std::make_shared<snail_number>();
			sum->parent_side = LEFT;
			sum->parent_number = new_sum;
			number->parent_side = RIGHT;
			number->parent_number = new_sum;
			new_sum->lhs_type = PAIR;
			new_sum->rhs_type = PAIR;
			new_sum->lhs_pair = sum;
			new_sum->rhs_pair = number;
			sum = new_sum;
		}

		while (sum->try_explode() || sum->try_split(sum));
	}
	std::cout << sum->get_magnitude() << std::endl;
}

void aoc::day_18::part_two()
{
	unsigned long max_magnitude = 0;
	std::shared_ptr<snail_number> sum = std::make_shared<snail_number>();
	sum->lhs_type = PAIR;
	sum->rhs_type = PAIR;

	const auto lines = m_input.strings();

	for (size_t i = 0; i < m_numbers.size(); ++i)
	{
		for (size_t j = 0; j < m_numbers.size(); ++j)
		{
			if (i == j) continue;
			sum->lhs_pair = parse_line(lines.at(i));
			sum->lhs_pair->parent_number = sum;
			sum->lhs_pair->parent_side = LEFT;
			sum->rhs_pair = parse_line(lines.at(j));
			sum->rhs_pair->parent_number = sum;
			sum->rhs_pair->parent_side = RIGHT;

			while (sum->try_explode() || sum->try_split(sum));

			max_magnitude = std::max(max_magnitude, sum->get_magnitude());
		}
	}

	std::cout << max_magnitude << std::endl;
}

bool aoc::day_18::snail_number::try_explode(size_t depth)
{
	if (depth == 4)
	{
		explode_left(lhs_value);
		explode_right(rhs_value);
		if (parent_side == LEFT)
		{
			parent_number->lhs_type = VALUE;
			parent_number->lhs_value = 0;
			parent_number->lhs_pair.reset();
		}
		else
		{
			parent_number->rhs_type = VALUE;
			parent_number->rhs_value = 0;
			parent_number->rhs_pair.reset();
		}
		return true;
	}

	return (lhs_type == PAIR && lhs_pair->try_explode(depth + 1))
		|| (rhs_type == PAIR && rhs_pair->try_explode(depth + 1));
}

void aoc::day_18::snail_number::explode_left(const int val)
{
	if (!parent_number) return;
	if (parent_side == RIGHT)
	{
		if (parent_number->lhs_type == VALUE) parent_number->lhs_value += val;
		else
		{
			auto current = parent_number->lhs_pair;
			while (current->rhs_type == PAIR) current = current->rhs_pair;
			current->rhs_value += val;
		}
	}
	else parent_number->explode_left(val);
}

void aoc::day_18::snail_number::explode_right(const int val)
{
	if (!parent_number) return;
	if (parent_side == LEFT)
	{
		if (parent_number->rhs_type == VALUE) parent_number->rhs_value += val;
		else
		{
			auto current = parent_number->rhs_pair;
			while (current->lhs_type == PAIR) current = current->lhs_pair;
			current->lhs_value += val;
		}
	}
	else parent_number->explode_right(val);
}

bool aoc::day_18::snail_number::try_split(std::shared_ptr<snail_number> shared_this)
{
	if (lhs_type == PAIR && lhs_pair->try_split(lhs_pair)) return true;
	else if (lhs_type == VALUE && lhs_value >= 10)
	{
		const auto value = lhs_value;
		lhs_value = 0;
		lhs_type = PAIR;
		lhs_pair = std::make_shared<snail_number>();
		lhs_pair->parent_number = shared_this;
		lhs_pair->parent_side = LEFT;
		lhs_pair->lhs_type = VALUE;
		lhs_pair->rhs_type = VALUE;
		lhs_pair->lhs_value = value / 2;
		lhs_pair->rhs_value = value / 2 + (value % 2);
		return true;
	}

	if (rhs_type == PAIR) return rhs_pair->try_split(rhs_pair);
	else if (rhs_value >= 10)
	{
		const auto value = rhs_value;
		rhs_value = 0;
		rhs_type = PAIR;
		rhs_pair = std::make_shared<snail_number>();
		rhs_pair->parent_number = shared_this;
		rhs_pair->parent_side = RIGHT;
		rhs_pair->lhs_type = VALUE;
		rhs_pair->rhs_type = VALUE;
		rhs_pair->lhs_value = value / 2;
		rhs_pair->rhs_value = value / 2 + (value % 2);
		return true;
	}

	return false;
}

unsigned long aoc::day_18::snail_number::get_magnitude()
{
	unsigned long left_magnitude = lhs_type == PAIR ? lhs_pair->get_magnitude() : lhs_value;
	unsigned long right_magnitude = rhs_type == PAIR ? rhs_pair->get_magnitude() : rhs_value;
	return left_magnitude * 3 + right_magnitude * 2;
}

void aoc::day_18::snail_number::print()
{
	std::cout << '[';
	if (lhs_type == VALUE) std::cout << lhs_value;
	else lhs_pair->print();
	std::cout << ',';
	if (rhs_type == VALUE) std::cout << rhs_value;
	else rhs_pair->print();
	std::cout << ']';
}

std::shared_ptr<aoc::day_18::snail_number> aoc::day_18::parse_line(std::string line)
{
	std::stack<std::pair<std::shared_ptr<snail_number>, side>> numbers;
	size_t next_pos = 0;
	while (next_pos < line.size())
	{
		line = line.substr(next_pos);
		if (line.at(0) == '[')
		{
			next_pos = 1;
			numbers.emplace(std::make_shared<snail_number>(), LEFT);
		}
		else if (line.at(0) == ']')
		{
			next_pos = 1;
			const auto number = numbers.top().first;
			numbers.pop();
			if (numbers.size() == 0)
			{
				return number;
			}
			else if (numbers.top().second == LEFT)
			{
				numbers.top().first->lhs_type = PAIR;
				numbers.top().first->lhs_pair = number;
			}
			else
			{
				numbers.top().first->rhs_type = PAIR;
				numbers.top().first->rhs_pair = number;
			}
			number->parent_number = numbers.top().first;
			number->parent_side = numbers.top().second;
		}
		else if (line.at(0) == ',')
		{
			next_pos = 1;
			numbers.top().second = RIGHT;
		}
		else
		{
			const auto number = std::stoi(line, &next_pos);
			if (numbers.top().second == LEFT)
			{
				numbers.top().first->lhs_type = VALUE;
				numbers.top().first->lhs_value = number;
			}
			else
			{
				numbers.top().first->rhs_type = VALUE;
				numbers.top().first->rhs_value = number;
			}
		}
	}
	throw std::exception();
}
