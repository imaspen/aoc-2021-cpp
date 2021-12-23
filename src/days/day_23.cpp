#include "day_23.hpp"

#include <iostream>

aoc::day_23::day_23(const input& input) : day(input)
{
	const auto lines = m_input.strings();
	m_start_state.rooms.at(0).at(0) = static_cast<type>(lines.at(2).at(3));
	m_start_state.rooms.at(0).at(1) = static_cast<type>(lines.at(3).at(3));
	m_start_state.rooms.at(1).at(0) = static_cast<type>(lines.at(2).at(5));
	m_start_state.rooms.at(1).at(1) = static_cast<type>(lines.at(3).at(5));
	m_start_state.rooms.at(2).at(0) = static_cast<type>(lines.at(2).at(7));
	m_start_state.rooms.at(2).at(1) = static_cast<type>(lines.at(3).at(7));
	m_start_state.rooms.at(3).at(0) = static_cast<type>(lines.at(2).at(9));
	m_start_state.rooms.at(3).at(1) = static_cast<type>(lines.at(3).at(9));

	m_p2_start_state.rooms.at(0).at(0) = static_cast<type>(lines.at(2).at(3));
	m_p2_start_state.rooms.at(0).at(1) = static_cast<type>('D');
	m_p2_start_state.rooms.at(0).at(2) = static_cast<type>('D');
	m_p2_start_state.rooms.at(0).at(3) = static_cast<type>(lines.at(3).at(3));
	m_p2_start_state.rooms.at(1).at(0) = static_cast<type>(lines.at(2).at(5));
	m_p2_start_state.rooms.at(1).at(1) = static_cast<type>('C');
	m_p2_start_state.rooms.at(1).at(2) = static_cast<type>('B');
	m_p2_start_state.rooms.at(1).at(3) = static_cast<type>(lines.at(3).at(5));
	m_p2_start_state.rooms.at(2).at(0) = static_cast<type>(lines.at(2).at(7));
	m_p2_start_state.rooms.at(2).at(1) = static_cast<type>('B');
	m_p2_start_state.rooms.at(2).at(2) = static_cast<type>('A');
	m_p2_start_state.rooms.at(2).at(3) = static_cast<type>(lines.at(3).at(7));
	m_p2_start_state.rooms.at(3).at(0) = static_cast<type>(lines.at(2).at(9));
	m_p2_start_state.rooms.at(3).at(1) = static_cast<type>('A');
	m_p2_start_state.rooms.at(3).at(2) = static_cast<type>('C');
	m_p2_start_state.rooms.at(3).at(3) = static_cast<type>(lines.at(3).at(9));

	for (size_t i = 0; i < m_goal_state.rooms.size(); ++i)
	{
		auto& room = m_goal_state.rooms.at(i);
		auto& room_type = m_home_room_to_type.at(i);
		for (size_t j = 0; j < room.size(); ++j)
		{
			room.at(j) = room_type;
		}
	}

	for (size_t i = 0; i < m_p2_goal_state.rooms.size(); ++i)
	{
		auto& room = m_p2_goal_state.rooms.at(i);
		auto& room_type = m_home_room_to_type.at(i);
		for (size_t j = 0; j < room.size(); ++j)
		{
			room.at(j) = room_type;
		}
	}
}

void aoc::day_23::part_one()
{
	std::set<node<2>> nodes;
	std::map<state<2>, node<2>> known_states;
	nodes.emplace(m_start_state, 0);
	known_states.emplace(m_start_state, node(m_start_state, 0));

	while (nodes.size() > 0)
	{
		const auto node = *nodes.begin();
		nodes.erase(node);

		if (node.state == m_goal_state)
		{
			std::cout << node.energy_used << std::endl;
			return;
		}

		emplace_new_nodes(node, nodes, known_states);
	}
	// ran out of nodes;
	throw std::exception();
}

void aoc::day_23::part_two()
{
	std::set<node<4>> nodes;
	std::map<state<4>, node<4>> known_states;
	nodes.emplace(m_p2_start_state, 0);
	known_states.emplace(m_p2_start_state, node(m_p2_start_state, 0));

	while (nodes.size() > 0)
	{
		const auto node = *nodes.begin();
		nodes.erase(node);

		if (node.state == m_p2_goal_state)
		{
			std::cout << node.energy_used << std::endl;
			return;
		}

		emplace_new_nodes(node, nodes, known_states);
	}
	// ran out of nodes;
	throw std::exception();
}

template<size_t RoomDepth>
bool aoc::day_23::state<RoomDepth>::operator==(const state<RoomDepth>& rhs) const
{
	return hall == rhs.hall && rooms == rhs.rooms;
}

template<size_t RoomDepth>
bool aoc::day_23::state<RoomDepth>::operator<(const state<RoomDepth>& rhs) const
{
	if (hall != rhs.hall) return hall < rhs.hall;
	else return rooms < rhs.rooms;
}

template<size_t RoomDepth>
aoc::day_23::node<RoomDepth>::node(const aoc::day_23::state<RoomDepth>& state, const size_t& energy_used) : state(state), energy_used(energy_used)
{
	h = 0;
	for (const auto& hall_pos : state.stopping_points)
	{
		const auto& t = state.hall.at(hall_pos);
		if (t == EMPTY) continue;
		h += std::abs(static_cast<int>(hall_pos) - static_cast<int>(m_type_to_home_pos.at(t))) * m_type_to_move_cost.at(t);
	}
	for (size_t i = 0; i < state.rooms.size(); ++i)
	{
		const auto& room = state.rooms.at(i);
		const auto& room_type = m_home_room_to_type.at(i);
		const auto& room_pos = 2 + i * 2;
		for (size_t j = 0; j < room.size(); ++j)
		{
			const auto& t = room.at(j);
			if (t == room_type || t == EMPTY) continue;
			const auto& target_pos = m_type_to_home_pos.at(t);
			h += (1 + j + std::abs(static_cast<int>(room_pos) - static_cast<int>(target_pos))) * m_type_to_move_cost.at(t);
		}
	}
	f = h + energy_used;
}

template<size_t RoomDepth>
bool aoc::day_23::node<RoomDepth>::operator<(const node<RoomDepth>& rhs) const
{
	if (f != rhs.f) return f < rhs.f;
	if (h != rhs.h) return h < rhs.h;
	else if (energy_used != rhs.energy_used) return energy_used < rhs.energy_used;
	else return state < rhs.state;
}

template<size_t RoomDepth>
void aoc::day_23::emplace_new_nodes(const node<RoomDepth>& current_node, std::set<node<RoomDepth>>& nodes, std::map<state<RoomDepth>, node<RoomDepth>>& known_states)
{
	const auto& state = current_node.state;
	const auto& energy_used = current_node.energy_used;

	// can waiting amphipods go home?
	for (const auto& hall_pos : state.stopping_points)
	{
		const auto& t = state.hall.at(hall_pos);
		if (t == EMPTY) continue;
		const auto& home_room_idx = m_type_to_home_room.at(t);
		const auto& home_room = state.rooms.at(home_room_idx);
		if (home_room.at(0) != EMPTY) continue; // entrance blocked
		if (home_room.at(0) != EMPTY && home_room.at(0) != t) continue; // bottom has wrong type

		bool enterable = true;
		for (size_t i = 0; i < RoomDepth; ++i)
		{
			const auto& cell_type = home_room.at(i);
			if (cell_type != EMPTY && cell_type != t)
			{
				enterable = false;
				break;
			}
		}
		if (!enterable) continue;

		const auto& home_pos = m_type_to_home_pos.at(t);
		if (home_pos > hall_pos) // we need to go right
		{
			bool clear = true;
			for (size_t x = hall_pos + 1; x <= home_pos; ++x)
			{
				if (state.hall.at(x) != EMPTY)
				{
					clear = false;
					break;
				}
			}
			if (!clear) continue;
		}
		else // we need to ge left
		{
			bool clear = true;
			for (size_t x = hall_pos - 1; x >= home_pos; --x)
			{
				if (state.hall.at(x) != EMPTY)
				{
					clear = false;
					break;
				}
			}
			if (!clear) continue;
		}

		int move_cost = std::abs(static_cast<int>(hall_pos) - static_cast<int>(home_pos)) + 1;
		auto next_state = state;
		size_t swap_pos = 0;
		for (size_t i = 1; i < RoomDepth; ++i)
		{
			if (home_room.at(i) != EMPTY) break;
			++swap_pos;
		}
		std::swap(next_state.hall.at(hall_pos), next_state.rooms.at(home_room_idx).at(swap_pos));

		const auto next_energy_used = energy_used + m_type_to_move_cost.at(t) * (move_cost + swap_pos);

		const auto next_node = node(next_state, next_energy_used);

		if (known_states.count(next_state) == 1)
		{
			const auto& state_node = known_states.at(next_state);
			if (state_node.energy_used <= next_energy_used) continue;
			nodes.erase(state_node);
			known_states.at(next_state) = node(next_state, next_energy_used);
		}
		else known_states.emplace(next_state, next_node);
		nodes.emplace(next_state, next_energy_used);
	}

	// can amphipods in rooms leave?
	for (size_t i = 0; i < 4; ++i)
	{
		const auto& room = state.rooms.at(i);
		const auto& room_type = m_home_room_to_type.at(i);
		size_t to_move = RoomDepth;

		for (size_t i = 0; i < RoomDepth; ++i)
		{
			if (room.at(i) != EMPTY)
			{
				to_move = i;
				break;
			}
		}

		if (to_move == RoomDepth) continue;

		if (room.at(to_move) == room_type)
		{
			bool organized = true;
			for (size_t i = to_move; i < RoomDepth; ++i)
			{
				if (room.at(i) != room_type)
				{
					organized = false;
					break;
				}
			}
			if (organized) continue;
		}

		const auto& start_pos = 2 + i * 2;
		for (const auto& target_pos : state.stopping_points)
		{
			bool clear = true;
			for (size_t x = std::min(start_pos, target_pos); x <= std::max(start_pos, target_pos); ++x)
			{
				if (state.hall.at(x) != EMPTY)
				{
					clear = false;
					break;
				}
			}
			if (!clear) continue;

			const int dist = 1 + to_move + std::abs(static_cast<int>(start_pos) - static_cast<int>(target_pos));
			auto next_state = state;
			std::swap(next_state.rooms.at(i).at(to_move), next_state.hall.at(target_pos));

			const auto next_energy_used = energy_used + dist * m_type_to_move_cost.at(next_state.hall.at(target_pos));

			const auto next_node = node(next_state, next_energy_used);

			if (known_states.count(next_state) == 1)
			{
				const auto& state_node = known_states.at(next_state);
				if (state_node.energy_used <= next_energy_used) continue;
				nodes.erase(state_node);
				known_states.at(next_state) = node(next_state, next_energy_used);
			}
			else known_states.emplace(next_state, next_node);
			nodes.emplace(next_state, next_energy_used);
		}
	}
}
