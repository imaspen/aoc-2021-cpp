#include "day_15.hpp"

#include <iostream>

aoc::day_15::day_15(const aoc::input& input) : day(input)
{
	m_risk_levels = m_input.digits();
	m_expanded.emplace(0, std::map<point, std::set<point>>({ std::make_pair(point(0, 0), std::set<point>()) }));

	m_big_risk_levels.reserve(m_risk_levels.size() * 5);
	for (const auto& original_row : m_risk_levels)
	{
		m_big_risk_levels.emplace_back();
		auto& row = m_big_risk_levels.back();
		row.reserve(original_row.size() * 5);

		for (int offset = 0; offset < 5; ++offset)
		{
			for (const auto& risk_level : original_row)
			{
				row.emplace_back(risk_level + offset - ((risk_level + offset) > 9 ? 9 : 0));
			}
		}
	}

	for (int offset = 1; offset < 5; ++offset)
	{
		for (size_t y = 0; y < m_risk_levels.size(); ++y)
		{
			const auto& original_row = m_big_risk_levels.at(y);
			m_big_risk_levels.emplace_back();
			auto& row = m_big_risk_levels.back();
			row.reserve(original_row.size());

			for (const auto& risk_level : original_row)
			{
				row.emplace_back(risk_level + offset - ((risk_level + offset) > 9 ? 9 : 0));
			}
		}
	}
}

void aoc::day_15::part_one()
{
	const point target(m_risk_levels.at(0).size() - 1, m_risk_levels.size() - 1);

	std::set<point> Q;
	std::map<point, int> dists;
	for (size_t y = 0; y < m_risk_levels.size(); ++y)
	{
		const auto& row = m_risk_levels.at(y);
		for (size_t x = 0; x < row.size(); ++x)
		{
			Q.emplace(x, y);
			dists.emplace(point(x, y), INT_MAX);
		}
	}
	dists.at(point(0, 0)) = 0;

	while (true)
	{
		point u;
		auto min_dist = INT_MAX;
		for (const auto& p : Q)
		{
			const auto& dist = dists.at(p);
			if (dist <= min_dist)
			{
				u = p;
				min_dist = dist;
			}
		}

		if (u == target)
		{
			std::cout << min_dist << std::endl;
			return;
		}

		Q.erase(u);

		for (const auto& v_d : get_adjacencies(u, min_dist))
		{
			const auto& v = v_d.first;
			const auto& d = v_d.second;
			if (d < dists.at(v)) dists.at(v) = d;
		}
	}
}

void aoc::day_15::part_two()
{
	const point target(m_big_risk_levels.at(0).size() - 1, m_big_risk_levels.size() - 1);

	std::set<point> Q;
	std::map<int, std::set<point>> dists_points;
	std::map<point, int> points_dists;
	dists_points.emplace(0, std::set<point>());
	dists_points.emplace(INT_MAX, std::set<point>());
	for (size_t y = 0; y < m_big_risk_levels.size(); ++y)
	{
		const auto& row = m_big_risk_levels.at(y);
		for (size_t x = 0; x < row.size(); ++x)
		{
			Q.emplace(x, y);
			dists_points.at(INT_MAX).emplace(point(x, y));
			points_dists.emplace(point(x, y), INT_MAX);
		}
	}
	dists_points.at(0).emplace(point(0, 0));
	dists_points.at(INT_MAX).erase(point(0, 0));
	points_dists.at(point(0, 0)) = 0;

	while (true)
	{
		const auto dist_points = dists_points.begin();
		const auto min_dist = dist_points->first;
		const auto u = *dist_points->second.begin();

		if (dists_points.at(min_dist).size() == 1) dists_points.erase(min_dist);
		else dists_points.at(min_dist).erase(u);
		points_dists.erase(u);

		if (u == target)
		{
			std::cout << min_dist << std::endl;
			return;
		}

		Q.erase(u);

		for (const auto& v_d : get_adjacencies(u, min_dist, true))
		{
			const auto& v = v_d.first;
			if (Q.count(v) == 0) continue;
			const auto& d = v_d.second;
			const auto& cd = points_dists.at(v);
			if (d < cd)
			{
				if (dists_points.at(cd).size() == 1)
				{
					dists_points.erase(cd);
				}
				else
				{
					dists_points.at(cd).erase(v);
				}
				if (dists_points.count(d) == 1)
				{
					dists_points.at(d).emplace(v);
				}
				else
				{
					dists_points.emplace(d, std::set({ v }));
				}
				points_dists.at(v) = d;
			}
		}
	}
}

bool aoc::day_15::is_done()
{
	return m_expanded.begin()->second.count(m_end_point) == 1;
}

std::vector<std::pair<aoc::day_15::point, int>> aoc::day_15::get_adjacencies(const point& p, int risk_level, bool big)
{
	std::vector<std::pair<point, int>> results;
	results.reserve(4);
	const auto& x = p.first;
	const auto& y = p.second;
	const auto& risk_levels = big ? m_big_risk_levels : m_risk_levels;
	for (int dx = -1; dx <= 1; dx += 2)
	{
		const auto nx = x + dx;
		if (nx >= risk_levels.at(y).size()) continue;
		const auto np = std::make_pair(nx, y);
		results.emplace_back(np, risk_level + risk_levels.at(y).at(nx));
	}
	for (int dy = -1; dy <= 1; dy += 2)
	{
		const auto ny = y + dy;
		if (ny >= risk_levels.size()) continue;
		const auto np = std::make_pair(x, ny);
		results.emplace_back(np, risk_level + risk_levels.at(ny).at(x));
	}
	return results;
}
