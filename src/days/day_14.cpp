#include "day_14.hpp"

#include <iostream>

aoc::day_14::day_14(const aoc::input& input) : day(input)
{
	const auto lines = m_input.strings();

	m_polymer.reserve(65536);
	m_next_polymer.reserve(65536);

	m_polymer = lines.at(0);

	for (size_t i = 1; i < lines.size(); ++i)
	{
		const auto& line = lines.at(i);
		if (m_mappings.count(line.at(0)) == 0) m_mappings.emplace(line.at(0), std::map<char, char>());
		m_mappings.at(line.at(0)).emplace(line.at(1), line.at(6));
	}

	auto last_char = m_polymer.at(0);
	for (auto it = ++m_polymer.begin(); it != m_polymer.end(); ++it)
	{
		if (m_polymer_pair_counts.count(last_char) == 0) m_polymer_pair_counts.emplace(last_char, std::map<char, size_t>());
		if (m_polymer_pair_counts.at(last_char).count(*it) == 0) m_polymer_pair_counts.at(last_char).emplace(*it, 0);
		++m_polymer_pair_counts.at(last_char).at(*it);
		last_char = *it;
	}
}

void aoc::day_14::part_one()
{
	for (size_t i = 0; i < 10; ++i) step();

	std::map<char, size_t> counts;
	for (const auto& c : m_polymer)
	{
		if (counts.count(c) == 0) counts.emplace(c, 1);
		else ++counts.at(c);
	}

	size_t min = SIZE_T_MAX, max = 0;
	for (const auto& char_count : counts)
	{
		const auto& count = char_count.second;
		if (count > max) max = count;
		if (count < min) min = count;
	}

	std::cout << max - min << std::endl;
	std::cout << m_polymer.size() << std::endl;
}

void aoc::day_14::part_two()
{
	for (size_t i = 0; i < 40; ++i) smart_step();

	std::map<char, size_t> counts;
	for (const auto& char_char_counts : m_polymer_pair_counts)
	{
		const auto& c1 = char_char_counts.first;
		const auto& char_counts = char_char_counts.second;
		for (const auto& char_count : char_counts)
		{
			const auto& count = char_count.second;
			if (counts.count(c1) == 0) counts.emplace(c1, 0);
			counts.at(c1) += count;
		}
	}
	if (counts.count(m_polymer.back()) == 0) counts.emplace(m_polymer.back(), 0);
	++counts.at(m_polymer.back());

	size_t min = ULLONG_MAX, max = 0;
	for (const auto& char_count : counts)
	{
		const auto& count = char_count.second;
		if (count > max) max = count;
		if (count < min) min = count;
	}

	std::cout << max - min << std::endl;
}

void aoc::day_14::step()
{
	m_next_polymer.clear();
	char last_char = m_polymer.at(0);
	m_next_polymer.push_back(last_char);
	for (auto it = ++m_polymer.begin(); it != m_polymer.end(); ++it)
	{
		if (m_mappings.at(last_char).count(*it) > 0)
		{
			m_next_polymer.push_back(m_mappings.at(last_char).at(*it));
		}
		m_next_polymer.push_back(*it);
		last_char = *it;
	}
	m_polymer.swap(m_next_polymer);
}

void aoc::day_14::smart_step()
{
	m_next_polymer_pair_counts.clear();

	for (const auto& char_1_char_2_counts : m_polymer_pair_counts)
	{
		const auto& char_1 = char_1_char_2_counts.first;
		const auto& char_2_counts = char_1_char_2_counts.second;
		if (m_next_polymer_pair_counts.count(char_1) == 0) m_next_polymer_pair_counts.emplace(char_1, std::map<char, size_t>());
		auto& entry = m_next_polymer_pair_counts.at(char_1);
		const auto& map_entry = m_mappings.at(char_1);

		for (const auto& char_2_count : char_2_counts)
		{
			const auto& char_2 = char_2_count.first;
			const auto& count = char_2_count.second;

			const auto& insert_char = map_entry.at(char_2);

			if (m_next_polymer_pair_counts.count(insert_char) == 0) m_next_polymer_pair_counts.emplace(insert_char, std::map<char, size_t>());
			auto& insert_entry = m_next_polymer_pair_counts.at(insert_char);

			if (entry.count(insert_char) == 0) entry.emplace(insert_char, 0);
			if (insert_entry.count(char_2) == 0) insert_entry.emplace(char_2, 0);

			entry.at(insert_char) += count;
			insert_entry.at(char_2) += count;
		}
	}

	m_polymer_pair_counts.swap(m_next_polymer_pair_counts);
}
