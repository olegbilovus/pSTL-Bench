#pragma once

#include <numeric>

#include <benchmark/benchmark.h>

#include "pstl/utils/utils.h"

namespace benchmark_adjacent_difference
{
	template<class Policy, class Function>
	static void benchmark_wrapper(benchmark::State & state, Function && F)
	{
		constexpr auto execution_policy = Policy{};

		const auto & size = state.range(0);

		auto input = pstl::generate_increment(execution_policy, size);

		auto output = input;
		std::fill(output.begin(), output.end(), 0);

		std::adjacent_difference(input.begin(), input.end(), output.begin());

		const auto solution = output.back();

		for (auto _ : state)
		{
			pstl::wrap_timing(state, std::forward<Function>(F), execution_policy, input, output);

			assert(output.back() == solution);
		}

		pstl::add_global_custom_statistics(state, input, output);
	}
} // namespace benchmark_adjacent_difference
