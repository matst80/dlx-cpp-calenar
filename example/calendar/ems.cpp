#include "Polyomino.hpp"
#include <dlx/AlgorithmDLX.hpp>
#include <emscripten/bind.h>

using namespace emscripten;

std::string get_solutions(unsigned maxSolutions, int dayIndex, int monthIndex, int dayOfWeekIndex)
{
	std::vector<std::vector<unsigned>> area = {
			{1, 1, 1, 1, 1, 1, 0},
			{1, 1, 1, 1, 1, 1, 0},
			{1, 1, 1, 1, 1, 1, 1},
			{1, 1, 1, 1, 1, 1, 1},
			{1, 1, 1, 1, 1, 1, 1},
			{1, 1, 1, 1, 1, 1, 1},
			{1, 1, 1, 1, 1, 1, 1},
			{0, 0, 0, 0, 1, 1, 1},
	};

	area[dayIndex / 7][dayIndex % 7] = 0;
	area[monthIndex / 7][monthIndex % 7] = 0;
	area[dayOfWeekIndex / 7][dayOfWeekIndex % 7] = 0;

	auto options = AlgorithmDLX::Options();
	options.max_solutions = maxSolutions;

	auto calendar_problem = Polyomino(Shape::calendarPieces(), area);
	auto result = AlgorithmDLX(calendar_problem.problem()).search(options);
	std::string output;
	for (const auto &used_rows : result.solutions)
	{
		auto solution = calendar_problem.make_solution(used_rows);
		for (const auto &line : solution)
		{
			output.append(line);
			output.append("\n");
			// output.push_back(line);
			// cout << line << '\n';
		}
		output.append("\n");
	}
	return output;
}

EMSCRIPTEN_BINDINGS(my_module)
{
	function("get_solutions", &get_solutions);
}