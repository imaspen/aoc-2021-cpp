#include "day_16.hpp"

#include <iostream>

aoc::day_16::day_16(const aoc::input& input) : day(input)
{
	const auto line = m_input.strings().at(0);
	m_bits.reserve(line.size() * 4);

	for (auto c : line)
	{
		c -= '0';
		if (c > 9) c -= 7;
		for (size_t i = 0; i < 4; ++i)
		{
			m_bits.push_back(c & 8);
			c <<= 1;
		}
	}
}

void aoc::day_16::part_one()
{
	size_t pos = 0;
	std::cout << get_packet_version_sum(parse_packet(pos)) << std::endl;
}

void aoc::day_16::part_two()
{
	size_t pos = 0;
	std::cout << get_packet_value(parse_packet(pos)) << std::endl;
}

aoc::day_16::packet aoc::day_16::parse_packet(size_t& pos)
{
	int packet_version = 0, packet_type = 0;
	for (size_t i = 0; i < 3; ++i)
	{
		packet_version <<= 1;
		packet_version += m_bits.at(pos++);
	}
	for (size_t i = 0; i < 3; ++i)
	{
		packet_type <<= 1;
		packet_type += m_bits.at(pos++);
	}

	if (packet_type == 4)
	{
		bool done = false;
		unsigned long long value = 0;
		while (!done)
		{
			done = !m_bits.at(pos++);
			for (size_t i = 0; i < 4; ++i)
			{
				value <<= 1;
				value += m_bits.at(pos++);
			}
		}
		return { .version = packet_version, .type = packet_type, .value = value };
	}
	else
	{
		const auto& length_type = m_bits.at(pos++);
		size_t length = 0;
		for (size_t i = 0; i < (length_type ? 11 : 15); ++i)
		{
			length <<= 1;
			length += m_bits.at(pos++);
		}

		std::vector<packet> sub_packets;
		if (length_type == 0)
		{
			const auto end_pos = pos + length;
			while (pos < end_pos) sub_packets.push_back(parse_packet(pos));
		}
		else
		{
			for (size_t i = 0; i < length; ++i) sub_packets.push_back(parse_packet(pos));
		}
		return { .version = packet_version, .type = packet_type, .sub_packets = sub_packets };
	}
}

int aoc::day_16::get_packet_version_sum(const packet& packet)
{
	auto value = packet.version;
	for (const auto& sub_packet : packet.sub_packets)
	{
		value += get_packet_version_sum(sub_packet);
	}
	return value;
}

unsigned long long aoc::day_16::get_packet_value(const packet& packet)
{
	if (packet.type == 4) return packet.value; // literal
	else if (packet.type == 0) // sum
	{
		unsigned long long sum = 0;
		for (const auto& sub_packet : packet.sub_packets) sum += get_packet_value(sub_packet);
		return sum;
	}
	else if (packet.type == 1) // product
	{
		unsigned long long product = 1;
		for (const auto& sub_packet : packet.sub_packets) product *= get_packet_value(sub_packet);
		return product;
	}
	else if (packet.type == 2) // min
	{
		unsigned long long min = ULLONG_MAX;
		for (const auto& sub_packet : packet.sub_packets) min = std::min(min, get_packet_value(sub_packet));
		return min;
	}
	else if (packet.type == 3) // max
	{
		unsigned long long max = 0;
		for (const auto& sub_packet : packet.sub_packets) max = std::max(max, get_packet_value(sub_packet));
		return max;
	}
	else if (packet.type == 5) // greater than
	{
		return get_packet_value(packet.sub_packets.at(0)) > get_packet_value(packet.sub_packets.at(1));
	}
	else if (packet.type == 6) // less than
	{
		return get_packet_value(packet.sub_packets.at(0)) < get_packet_value(packet.sub_packets.at(1));
	}
	else if (packet.type == 7) // equal
	{
		return get_packet_value(packet.sub_packets.at(0)) == get_packet_value(packet.sub_packets.at(1));
	}
	else throw std::exception();
}
