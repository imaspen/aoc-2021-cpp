#pragma once

#include <array>
#include <map>

#include "day.hpp"

namespace aoc
{
	class day_21 : public aoc::day
	{
	public:
		day_21(const input& input);

		virtual void part_one() override;
		virtual void part_two() override;

	private:
		struct player
		{
			int32_t serialize() const { return position << score_bits | score; }
			static player deserialize(const int32_t& serialized)
			{
				return player{
					.score = static_cast<int>(serialized & score_mask),
					.position = static_cast<int>((serialized >> score_bits) & position_mask)
				};
			}

			int score = 0, position;

			constexpr static inline size_t score_bits = 5, position_bits = 7, player_bits = score_bits + position_bits;

			constexpr static inline int32_t score_mask = (1 << score_bits) - 1;
			constexpr static inline int32_t position_mask = (1 << position_bits) - 1;
		};

		struct game_state
		{
			int32_t serialize() const
			{
				return (active_player
					<< player::player_bits | players.at(0).serialize())
					<< player::player_bits | players.at(1).serialize();
			}
			static game_state deserialize(const int32_t& serialized)
			{
				return game_state{
					.active_player = static_cast<bool>((serialized >> player::player_bits >> player::player_bits) & active_player_mask),
					.players = {
						player::deserialize((serialized >> player::player_bits) & player_mask),
						player::deserialize(serialized & player_mask)
					}
				};
			}

			int die_val = 0;
			bool active_player = 0;
			std::array<player, 2> players;

			constexpr static inline size_t die_val_bits = 4, active_player_bits = 1;

			constexpr static inline int32_t die_val_mask = (1 << die_val_bits) - 1;
			constexpr static inline int32_t active_player_mask = (1 << active_player_bits) - 1;
			constexpr static inline int32_t player_mask = (1 << player::player_bits) - 1;
		};

		static bool is_done(const std::map<int32_t, size_t>& hash_counts);

		game_state m_game_state;

		size_t m_num_rolls = 0;
	};
}
