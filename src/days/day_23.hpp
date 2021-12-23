#pragma once

#include <array>
#include <map>
#include <set>

#include "day.hpp"

namespace aoc
{
	class day_23 : public aoc::day
	{
	public:
		day_23(const input& input);

		virtual void part_one() override;
		virtual void part_two() override;

	private:
		enum type
		{
			EMPTY = '.',
			AMBER = 'A',
			BRONZE = 'B',
			COPPER = 'C',
			DESERT = 'D',
		};

		template<size_t RoomDepth>
		struct state
		{
			static constexpr inline std::array<size_t, 7> stopping_points{ 0, 1, 3, 5, 7, 9, 10 };

			std::array<type, 11> hall{ EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY };
			// the rooms, 0 = top space, 1 = bottom space
			std::array<std::array<type, RoomDepth>, 4> rooms;

			bool operator==(const state<RoomDepth>& rhs) const;
			bool operator<(const state<RoomDepth>& rhs) const;
		};

		template<size_t RoomDepth>
		struct node
		{
			node(const state<RoomDepth>& state, const size_t& energy_used);

			state<RoomDepth> state;
			size_t energy_used;

			size_t h, f;
			bool operator<(const node& rhs) const;
		};

		template<size_t RoomDepth>
		void emplace_new_nodes(const node<RoomDepth>& current_node, std::set<node<RoomDepth>>& nodes, std::map<state<RoomDepth>, node<RoomDepth>>& known_states);

		state<2> m_goal_state, m_start_state;
		state<4> m_p2_goal_state, m_p2_start_state;

		static inline std::map<type, size_t> m_type_to_move_cost{
			std::make_pair(type::AMBER, 1),
			std::make_pair(type::BRONZE, 10),
			std::make_pair(type::COPPER, 100),
			std::make_pair(type::DESERT, 1000)
		};
		static inline std::map<type, size_t> m_type_to_home_pos{
			std::make_pair(type::AMBER, 2),
			std::make_pair(type::BRONZE, 4),
			std::make_pair(type::COPPER, 6),
			std::make_pair(type::DESERT, 8)
		};
		static inline std::map<size_t, type> m_home_room_to_type{
			std::make_pair(0, type::AMBER),
			std::make_pair(1, type::BRONZE),
			std::make_pair(2, type::COPPER),
			std::make_pair(3, type::DESERT)
		};
		static inline std::map<type, size_t> m_type_to_home_room{
			std::make_pair(type::AMBER, 0),
			std::make_pair(type::BRONZE, 1),
			std::make_pair(type::COPPER, 2),
			std::make_pair(type::DESERT, 3)
		};
	};
}
