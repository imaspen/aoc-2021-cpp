#pragma once

#include "day.hpp"

namespace aoc
{
	class day_16 : public aoc::day
	{
	public:
		day_16(const aoc::input& input);

		virtual void part_one() override;
		virtual void part_two() override;

	private:
		struct packet
		{
			int version, type;
			unsigned long long value = 0;
			std::vector<packet> sub_packets;
		};

		packet parse_packet(size_t& pos);
		int get_packet_version_sum(const packet& packet);
		unsigned long long get_packet_value(const packet& packet);

		std::vector<bool> m_bits;
	};
}
