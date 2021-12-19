#pragma once

#include <array>
#include <vector>

#include "day.hpp"

namespace aoc
{
	class day_19 : public aoc::day
	{
	public:
		day_19(const aoc::input& input);

		virtual void part_one() override;
		virtual void part_two() override;

	private:
		struct matrix;
		struct vector
		{
			vector() = default;
			vector(const vector& rhs);
			vector(const int& x, const int& y, const int& z) : x(x), y(y), z(z) {};
			int x = 0, y = 0, z = 0;

			vector& operator=(const vector& rhs);
			vector& operator+=(const vector& rhs);
			vector& operator-=(const vector& rhs);
			vector& operator*=(const vector& rhs);
			vector& operator*=(const matrix& rhs);
			bool operator==(const vector& rhs) const { return x == rhs.x && y == rhs.y && z == rhs.z; }
			bool operator!=(const vector& rhs) const { return !(*this == rhs); }
		};
		struct matrix
		{
			matrix() = default;
			matrix(const matrix& rhs);
			matrix(const vector& v1, const vector& v2, const vector& v3) : v1(v1), v2(v2), v3(v3) {};
			vector v1, v2, v3;

			matrix& operator= (const matrix& rhs);
			matrix& operator*= (const matrix& rhs);
			bool operator==(const matrix& rhs) const { return v1 == rhs.v1 && v2 == rhs.v2 && v3 == rhs.v3; }
			bool operator!=(const matrix& rhs) const { return !(*this == rhs); }
		};
		struct distance
		{
			distance(const vector& dist, const vector& a, const vector& b) : dist(dist), a(a), b(b) {};
			vector dist, a, b;
		};
		struct scanner
		{
			int id = 0;
			std::vector<vector> beacons;
			vector pos;
			int rotation = 0;
			bool placed = false;

			std::vector<distance> get_distances(const std::array<matrix, 24>& rotations) const;
		};

		void place_scanners();
		bool is_done();

		std::vector<scanner> m_scanners;

		std::array<matrix, 4> m_x_rotations{
			matrix( // 0 deg
				vector(1,  0,  0), //  1  0  0
				vector(0,  1,  0), //  0  c  s
				vector(0,  0,  1)  //  0 -s  c
			),
			matrix( // 90 deg
				vector(1,  0,  0), //  1  0  0
				vector(0,  0,  1), //  0  c  s
				vector(0, -1,  0)  //  0 -s  c
			),
			matrix( // 180 deg
				vector(1,  0,  0), //  1  0  0
				vector(0, -1,  0), //  0  c  s
				vector(0,  0, -1)  //  0 -s  c
			),
			matrix( // 270 deg
				vector(1,  0,  0), //  1  0  0
				vector(0,  0, -1), //  0  c  s
				vector(0,  1,  0)  //  0 -s  c
			)
		};

		std::array<matrix, 4> m_y_rotations{
			matrix( // 0 deg
				vector(1,  0,  0), //  c  0 -s
				vector(0,  1,  0), //  0  1  0
				vector(0,  0,  1)  //  s  0  c
			),
			matrix( // 90 deg
				vector(0,  0, -1), //  c  0 -s
				vector(0,  1,  0), //  0  1  0
				vector(1,  0,  0)  //  s  0  c
			),
			matrix( // 180 deg
				vector(-1,  0,  0), //  c  0 -s
				vector(0,  1,  0), //  0  1  0
				vector(0,  0, -1)  //  s  0  c
			),
			matrix( // 270 deg
				vector(0,  0,  1), //  c  0 -s
				vector(0,  1,  0), //  0  1  0
				vector(-1,  0,  0) //  s  0  c
			)
		};

		std::array<matrix, 4> m_z_rotations{
			matrix( // 0 deg
				vector(1,  0,  0), //  c  s  0
				vector(0,  1,  0), // -s  c  0
				vector(0,  0,  1) //  0  0  1
			),
			matrix( // 90 deg
				vector(0,  1,  0), //  c  s  0
				vector(-1,  0,  0), // -s  c  0
				vector(0,  0,  1) //  0  0  1
			),
			matrix( // 180 deg
				vector(-1,  0,  0), //  c  s  0
				vector(0, -1,  0), // -s  c  0
				vector(0,  0,  1) //  0  0  1
			),
			matrix( // 270 deg
				vector(0, -1,  0), //  c  s  0
				vector(1,  0,  0), // -s  c  0
				vector(0,  0,  1) //  0  0  1
			)
		};

		std::array<matrix, 24> m_rotations;
	};
}
