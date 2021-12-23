#pragma once

#include <queue>
#include <set>
#include <utility>
#include <vector>

#include "day.hpp"

namespace aoc
{
	class day_22 : public aoc::day
	{
	public:
		day_22(const input& input);

		virtual void part_one() override;
		virtual void part_two() override;

	private:
		struct point
		{
			point(const int& x, const int& y, const int& z) : x(x), y(y), z(z) {};
			int x = 0, y = 0, z = 0;
			bool operator<(const point& rhs) const
			{
				if (x == rhs.x)
				{
					if (y == rhs.y)
					{
						return z < rhs.z;
					}
					return y < rhs.y;
				}
				return x < rhs.x;
			}
		};

		struct instruction
		{
			instruction(const bool& on, const point& p1, const point& p2) : on(on), p1(p1), p2(p2) {};
			bool on;
			point p1, p2;
		};

		struct cuboid
		{
			cuboid(const point& p1, const point& p2) : p1(p1), p2(p2) {};
			point p1, p2;
			bool operator<(const cuboid& rhs) const
			{
				if (p1 < rhs.p1) return true;
				if (rhs.p1 < p1) return false;
				return p2 < rhs.p2;
			}
			void subtract_and_emplace(const cuboid& rhs, std::vector<cuboid>& cuboids);
			unsigned long long area() const {
				return
					(1 + static_cast<unsigned long long>(p2.x - p1.x))
					* (1 + static_cast<unsigned long long>(p2.y - p1.y))
					* (1 + static_cast<unsigned long long>(p2.z - p1.z));
			}
		};

		std::queue<instruction> m_startup_instructions;
		std::set<point> m_active_points;
	};
}
