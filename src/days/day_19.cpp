#include "day_19.hpp"

#include <iostream>
#include <map>
#include <set>

aoc::day_19::day_19(const input& input) : day(input)
{
	size_t pos = 0;
	for (size_t i = 0; i < 4; ++i)
	{
		for (size_t j = 0; j < 4; ++j)
		{
			for (size_t k = 0; k < 4; ++k)
			{
				matrix to_insert = m_x_rotations.at(i);
				to_insert *= m_y_rotations.at(j);
				to_insert *= m_z_rotations.at(k);
				bool unique = true;
				for (const auto& m : m_rotations)
				{
					if (m == to_insert)
					{
						unique = false;
						break;
					}
				}
				if (unique)m_rotations.at(pos++) = to_insert;
			}
		}
	}

	pos = 0;
	scanner curr{ .id = -1 };
	std::array<int, 3> point;
	for (auto line : m_input.strings())
	{
		if (line.at(1) == '-')
		{
			if (curr.id >= 0) m_scanners.emplace_back(curr);
			curr.id = std::stoi(line.substr(12));
			curr.beacons.clear();
		}
		else
		{
			pos = 0;
			for (size_t i = 0; i < 3; ++i)
			{
				line = line.substr(pos);
				point.at(i) = std::stoi(line, &pos);
				++pos;
			}
			curr.beacons.emplace_back(point.at(0), point.at(1), point.at(2));
		}
	}
	m_scanners.emplace_back(curr);

	m_scanners.at(0).placed = true;
}

void aoc::day_19::part_one()
{
	place_scanners();

	size_t count = 0;
	std::map<int, std::map<int, std::set<int>>> beacons;
	for (const auto& scanner : m_scanners)
	{
		const auto& rotation = m_rotations.at(scanner.rotation);
		const auto& pos = scanner.pos;
		for (auto beacon : scanner.beacons)
		{
			beacon *= rotation;
			beacon += pos;
			if (beacons.count(beacon.x) == 0) beacons.emplace(beacon.x, std::map<int, std::set<int>>());
			if (beacons.at(beacon.x).count(beacon.y) == 0) beacons.at(beacon.x).emplace(beacon.y, std::set<int>());
			count += beacons.at(beacon.x).at(beacon.y).emplace(beacon.z).second;
		}
	}

	std::cout << count << std::endl;
}

void aoc::day_19::part_two()
{
	place_scanners();

	int max = 0;

	for (size_t i = 0; i < m_scanners.size(); ++i)
	{
		for (size_t j = 0; j < m_scanners.size(); ++j)
		{
			if (i == j) continue;
			auto dist = m_scanners.at(i).pos;
			dist -= m_scanners.at(j).pos;
			const int manhattan = std::abs(dist.x) + std::abs(dist.y) + std::abs(dist.z);
			max = std::max(max, manhattan);
		}
	}

	std::cout << max << std::endl;
}

aoc::day_19::vector::vector(const vector& rhs)
{
	x = rhs.x;
	y = rhs.y;
	z = rhs.z;
}

aoc::day_19::vector& aoc::day_19::vector::operator=(const vector& rhs)
{
	if (this == &rhs) return *this;
	x = rhs.x;
	y = rhs.y;
	z = rhs.z;
	return *this;
}

aoc::day_19::vector& aoc::day_19::vector::operator-=(const vector& rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;
	return *this;
}

aoc::day_19::vector& aoc::day_19::vector::operator+=(const vector& rhs)
{
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;
	return *this;
}

aoc::day_19::vector& aoc::day_19::vector::operator*=(const vector& rhs)
{
	x *= rhs.x;
	y *= rhs.y;
	z *= rhs.z;
	return *this;
}

aoc::day_19::vector& aoc::day_19::vector::operator*=(const matrix& rhs)
{
	int nx = x * rhs.v1.x + y * rhs.v2.x + z * rhs.v3.x;
	int ny = x * rhs.v1.y + y * rhs.v2.y + z * rhs.v3.y;
	int nz = x * rhs.v1.z + y * rhs.v2.z + z * rhs.v3.z;
	x = nx;
	y = ny;
	z = nz;
	return *this;
}

aoc::day_19::matrix::matrix(const matrix& rhs)
{
	v1 = rhs.v1;
	v2 = rhs.v2;
	v3 = rhs.v3;
}

aoc::day_19::matrix& aoc::day_19::matrix::operator=(const matrix& rhs)
{
	if (this == &rhs) return *this;
	v1 = rhs.v1;
	v2 = rhs.v2;
	v3 = rhs.v3;
	return *this;
}

aoc::day_19::matrix& aoc::day_19::matrix::operator*=(const matrix& rhs)
{
	v1 *= rhs;
	v2 *= rhs;
	v3 *= rhs;
	return *this;
}

std::vector<aoc::day_19::distance> aoc::day_19::scanner::get_distances(const std::array<matrix, 24>& rotations) const
{
	std::vector<distance> distances;
	const auto n = beacons.size();
	distances.reserve((n * (n + 1)) / 2);
	for (size_t i = 0; i < n; ++i)
	{
		for (size_t j = 0; j < n; ++j)
		{
			if (i == j) continue;
			distances.emplace_back(vector(), beacons.at(i), beacons.at(j));
			distances.back().a *= rotations.at(rotation);
			distances.back().b *= rotations.at(rotation);
			distances.back().dist = distances.back().a;
			distances.back().dist -= distances.back().b;
		}
	}
	return distances;
}

void aoc::day_19::place_scanners()
{
	while (!is_done())
	{
		for (size_t i = 1; i < m_scanners.size(); ++i)
		{
			auto& scanner = m_scanners.at(i);
			if (scanner.placed) continue;

			auto compare_distances = scanner.get_distances(m_rotations);
			for (size_t r = 0; r < m_rotations.size(); ++r)
			{
				const auto& rotation = m_rotations.at(r);
				for (const auto& other_scanner : m_scanners)
				{
					if (!other_scanner.placed) continue;

					size_t count = 0;
					vector match_1_a, match_1_b, match_2_a, match_2_b;
					for (auto distance : compare_distances)
					{
						distance.dist *= rotation;
						for (const auto& ref_distance : other_scanner.get_distances(m_rotations))
						{
							if (distance.dist == ref_distance.dist)
							{
								++count;
								match_1_a = distance.a;
								match_1_a *= rotation;
								match_1_b = distance.b;
								match_1_b *= rotation;
								match_2_a = ref_distance.a;
								match_2_b = ref_distance.b;
							}
						}
					}

					if (count >= 66)
					{
						auto dif = match_2_a;
						dif -= match_1_a;
						scanner.pos = other_scanner.pos;
						scanner.pos += dif;

						scanner.rotation = r;
						scanner.placed = true;
						break;
					}
				}
				if (scanner.placed) break;
			}
		}
	}
}

bool aoc::day_19::is_done()
{
	for (const auto& scanner : m_scanners)
	{
		if (!scanner.placed) return false;
	}
	return true;
}
