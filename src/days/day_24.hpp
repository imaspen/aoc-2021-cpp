#pragma once

#include <array>
#include <stack>
#include <queue>

#include "day.hpp"

namespace aoc
{
	class day_24 : public aoc::day
	{
	public:
		day_24(const input& input);

		virtual void part_one() override;
		virtual void part_two() override;

	private:
		enum opcode
		{
			INPUT,
			ADD,
			MULTIPLY,
			DIVIDE,
			MODULO,
			EQUALS,
		};
		enum reg
		{
			X = 'x',
			Y = 'y',
			Z = 'z',
			W = 'w',
		};
		struct instruction
		{
			instruction(const std::string& instruction);
			opcode op;
			reg target;
			enum { REG, LITERAL } value_type = LITERAL;
			union
			{
				reg value_reg;
				int value = 0;
			};
		};
		struct computer
		{
			computer(const std::queue<instruction>& program, const std::queue<int>& input) : program(program), input(input) {};
			std::queue<instruction> program;
			std::queue<int> input;
			int x = 0, y = 0, z = 0, w = 0;

			void run_program();
		};

		std::pair<int, size_t> calc(int z, size_t i, const std::array<std::pair<int, int>, 14>& pairs);
		std::pair<int, size_t> calc_little(int z, size_t i, const std::array<std::pair<int, int>, 14>& pairs);

		std::queue<instruction> m_program;
	};
}
