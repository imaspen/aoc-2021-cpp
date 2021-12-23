#include "day_22.hpp"

#include <iostream>

aoc::day_22::day_22(const input& input) : day(input)
{
	const auto lines = m_input.strings();
	for (auto line : lines)
	{
		const auto on = line.at(1) == 'n';
		line = line.substr(on ? 5 : 6);
		size_t next_pos;
		const auto x_1 = std::stoi(line, &next_pos);
		line = line.substr(next_pos + 2);
		const auto x_2 = std::stoi(line, &next_pos);
		line = line.substr(next_pos + 3);
		const auto y_1 = std::stoi(line, &next_pos);
		line = line.substr(next_pos + 2);
		const auto y_2 = std::stoi(line, &next_pos);
		line = line.substr(next_pos + 3);
		const auto z_1 = std::stoi(line, &next_pos);
		line = line.substr(next_pos + 2);
		const auto z_2 = std::stoi(line, &next_pos);
		m_startup_instructions.emplace(
			on,
			point(std::min(x_1, x_2), std::min(y_1, y_2), std::min(z_1, z_2)),
			point(std::max(x_1, x_2), std::max(y_1, y_2), std::max(z_1, z_2))
		);
	}
}

void aoc::day_22::part_one()
{
	while (m_startup_instructions.size() > 0)
	{
		const auto& instruction = m_startup_instructions.front();

		for (int z = instruction.p1.z; z <= instruction.p2.z; ++z)
		{
			if (z > 50 || z < -50) continue;
			for (int y = instruction.p1.y; y <= instruction.p2.y; ++y)
			{
				if (y > 50 || y < -50) continue;
				for (int x = instruction.p1.x; x <= instruction.p2.x; ++x)
				{
					if (x > 50 || x < -50) continue;
					if (instruction.on) m_active_points.emplace(x, y, z);
					else m_active_points.erase(point(x, y, z));
				}
			}
		}

		m_startup_instructions.pop();
	}
	std::cout << m_active_points.size() << std::endl;
}

void aoc::day_22::part_two()
{
	std::vector<cuboid> cuboids, cuboids_next;
	cuboids.reserve(1024 * 1024);
	cuboids_next.reserve(1024 * 1024);

	while (m_startup_instructions.size() > 0)
	{
		cuboids_next.clear();
		const auto& instruction = m_startup_instructions.front();

		const auto new_cuboid = cuboid(instruction.p1, instruction.p2);

		for (auto& cuboid : cuboids)
		{
			cuboid.subtract_and_emplace(new_cuboid, cuboids_next);
		}

		if (instruction.on) cuboids_next.emplace_back(new_cuboid);
		cuboids.swap(cuboids_next);

		m_startup_instructions.pop();
	}

	unsigned long long area = 0;
	for (const auto& cuboid : cuboids) area += cuboid.area();

	std::cout << area << std::endl;
}

void aoc::day_22::cuboid::subtract_and_emplace(const cuboid& rhs, std::vector<cuboid>& cuboids)
{
	if (p2.x < rhs.p1.x || p2.y < rhs.p1.y || p2.z < rhs.p1.z)
	{
		// lhs max < rhs min
		cuboids.emplace_back(*this);
	}
	else if (p1.x > rhs.p2.x || p1.y > rhs.p2.y || p1.z > rhs.p2.z)
	{
		// lhs min > rhs max
		cuboids.emplace_back(*this);
	}
	else
	{
		if (rhs.p1.x > p1.x)
		{
			// has left edge
			cuboids.emplace_back(point(p1.x, p1.y, p1.z), point(rhs.p1.x - 1, p2.y, p2.z));
		}
		if (rhs.p2.x < p2.x)
		{
			// has right edge
			cuboids.emplace_back(point(rhs.p2.x + 1, p1.y, p1.z), point(p2.x, p2.y, p2.z));
		}
		const auto p1_x = std::max(p1.x, rhs.p1.x);
		const auto p2_x = std::min(p2.x, rhs.p2.x);
		if (rhs.p1.y > p1.y)
		{
			// has bottom edge
			cuboids.emplace_back(point(p1_x, p1.y, p1.z), point(p2_x, rhs.p1.y - 1, p2.z));
		}
		if (rhs.p2.y < p2.y)
		{
			// has top edge
			cuboids.emplace_back(point(p1_x, rhs.p2.y + 1, p1.z), point(p2_x, p2.y, p2.z));
		}
		const auto p1_y = std::max(p1.y, rhs.p1.y);
		const auto p2_y = std::min(p2.y, rhs.p2.y);
		if (rhs.p1.z > p1.z)
		{
			// has front edge
			cuboids.emplace_back(point(p1_x, p1_y, p1.z), point(p2_x, p2_y, rhs.p1.z - 1));
		}
		if (rhs.p2.z < p2.z)
		{
			// has back edge
			cuboids.emplace_back(point(p1_x, p1_y, rhs.p2.z + 1), point(p2_x, p2_y, p2.z));
		}
	}
}
