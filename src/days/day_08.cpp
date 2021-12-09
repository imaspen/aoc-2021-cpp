#include "day_08.hpp"

#include <iostream>
#include <map>
#include <vector>

aoc::day_08::day_08(const aoc::input& input) : aoc::day(input)
{
	for (auto line : m_input.strings())
	{
		size_t next_pos = 0, i = 0;
		signal_patterns signal_patterns;
		output_digits output_digits;
		do
		{
			line = line.substr(next_pos);
			if (line.at(0) == '|')
			{
				next_pos = 2;
			}
			else
			{
				next_pos = line.find(' ');
				const auto str = line.substr(0, next_pos);
				for (const auto& c : str)
				{
					if (i < 10)
					{
						signal_patterns[i][c - 'a'] = true;
					}
					else
					{
						output_digits[i - 10][c - 'a'] = true;
					}
				}
				++next_pos;
				++i;
			}
		} while (next_pos != 0);
		m_entries.emplace_back(std::make_pair(signal_patterns, output_digits));
	}
}

void aoc::day_08::part_one()
{
	size_t count = 0;
	for (const auto& signals_outputs : m_entries)
	{
		for (const auto& output : signals_outputs.second)
		{
			const auto c = output.count();
			if (c == 2 || c == 3 || c == 4 || c == 7) ++count;
		}
	}
	std::cout << count << std::endl;
}

void aoc::day_08::part_two()
{
	unsigned int sum = 0;
	for (const auto& signals_outputs : m_entries)
	{
		std::array<signal, 10> digit_signal;
		std::vector<signal> unknown_signals, remaining_unknown_signals;

		// we can identify 1, 4, 7, and 8 through their unique number of active segments
		for (const auto& signal : signals_outputs.first)
		{
			const auto count = signal.count();
			if (count == 2) digit_signal.at(1) = signal;
			else if (count == 3) digit_signal.at(7) = signal;
			else if (count == 4) digit_signal.at(4) = signal;
			else if (count == 7) digit_signal.at(8) = signal;
			else unknown_signals.emplace_back(signal);
		}

		// 9 uses all the same segments as 4
		for (const auto& unknown_signal : unknown_signals)
		{
			if ((unknown_signal & digit_signal.at(4)) == digit_signal.at(4)) digit_signal.at(9) = unknown_signal;
			else remaining_unknown_signals.emplace_back(unknown_signal);
		}

		unknown_signals.swap(remaining_unknown_signals);
		remaining_unknown_signals.clear();

		// 0 and 3 use the same segments as 7, but have different active segment counts
		for (const auto& unknown_signal : unknown_signals)
		{
			if ((unknown_signal & digit_signal.at(7)) == digit_signal.at(7))
			{
				const auto count = unknown_signal.count();
				if (count == 5) digit_signal.at(3) = unknown_signal;
				else if (count == 6) digit_signal.at(0) = unknown_signal;
				// something's gone wrong
				else throw std::exception();
			}
			else remaining_unknown_signals.emplace_back(unknown_signal);
		}

		unknown_signals.swap(remaining_unknown_signals);
		remaining_unknown_signals.clear();

		// 6 is the only remaining number with 6 active segments
		for (const auto& unknown_signal : unknown_signals)
		{
			if (unknown_signal.count() == 6) digit_signal.at(6) = unknown_signal;
			else remaining_unknown_signals.emplace_back(unknown_signal);
		}

		unknown_signals.swap(remaining_unknown_signals);
		remaining_unknown_signals.clear();

		// 5 | 7 == 9, 2 | 7 != 9
		for (const auto& unknown_signal : unknown_signals)
		{
			if ((unknown_signal | digit_signal.at(7)) == digit_signal.at(9)) digit_signal.at(5) = unknown_signal;
			else digit_signal.at(2) = unknown_signal;
		}

		unsigned int display = 0;
		unsigned int i = 1000;
		for (const auto& signal : signals_outputs.second)
		{
			for (size_t x = 0; x < digit_signal.size(); ++x)
			{
				if (digit_signal.at(x) == signal)
				{
					display += i * x;
					break;
				}
			}
			i /= 10;
		}
		sum += display;
	}

	std::cout << sum << std::endl;
}
