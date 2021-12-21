#include "day_21.hpp"

#include <iostream>

aoc::day_21::day_21(const input& input) : day(input)
{
	const auto lines = m_input.strings();
	m_game_state.players.at(0).position = lines.at(0).at(28) - '1';
	m_game_state.players.at(1).position = lines.at(1).at(28) - '1';
}

void aoc::day_21::part_one()
{
	while (true)
	{
		for (size_t i = 0; i < 2; ++i)
		{
			auto& player = m_game_state.players.at(i);
			int roll_sum = 0;
			for (size_t i = 0; i < 3; ++i)
			{
				++m_num_rolls;
				roll_sum += ++m_game_state.die_val;
				m_game_state.die_val %= 100;
			}
			player.position += roll_sum;
			player.position %= 10;
			player.score += player.position + 1;
			if (m_game_state.players.at(i).score >= 1000)
			{
				std::cout << m_num_rolls * m_game_state.players.at((i + 1) % 2).score << std::endl;
				return;
			}
		}
	}
}

void aoc::day_21::part_two()
{
	std::map<int32_t, size_t> hash_counts, hash_counts_next;
	std::map<int32_t, std::array<int32_t, 27>> hash_to_hashes;

	m_game_state.active_player = 1;
	hash_counts_next.emplace(m_game_state.serialize(), 1);
	std::array<size_t, 2> wins({ 0, 0 });

	while (!is_done(hash_counts_next))
	{
		hash_counts = hash_counts_next;
		for (const auto& hash_count : hash_counts)
		{
			const auto& hash = hash_count.first;
			const auto& count = hash_count.second;
			if (count == 0) continue;

			if (hash_to_hashes.count(hash) == 0)
			{
				std::array<int32_t, 27> hashes;
				for (size_t i = 0; i < 3; ++i)
				{
					for (size_t j = 0; j < 3; ++j)
					{
						for (size_t k = 0; k < 3; ++k)
						{
							game_state copy_state = game_state::deserialize(hash);

							copy_state.active_player = !copy_state.active_player;
							auto& player = copy_state.players.at(copy_state.active_player);
							player.position += i + j + k + 3;
							player.position %= 10;
							player.score += player.position + 1;

							hashes.at(i * 9 + j * 3 + k) = copy_state.serialize();
						}
					}
				}
				hash_to_hashes.emplace(hash, hashes);
			}

			const auto& hashes = hash_to_hashes.at(hash);
			hash_counts_next.at(hash) -= count;
			for (const auto& new_hash : hashes)
			{
				const auto state = game_state::deserialize(new_hash);
				if (state.players.at(state.active_player).score >= 21)
				{
					wins.at(state.active_player) += count;
				}
				else
				{
					if (hash_counts_next.count(new_hash) == 0) hash_counts_next.emplace(new_hash, count);
					else hash_counts_next.at(new_hash) += count;
				}
			}
		}
	}

	std::cout << std::max(wins.at(0), wins.at(1)) << std::endl;
}

bool aoc::day_21::is_done(const std::map<int32_t, size_t>& hash_counts)
{
	for (const auto& hash_count : hash_counts)
	{
		if (hash_count.second > 0) return false;
	}
	return true;
}
