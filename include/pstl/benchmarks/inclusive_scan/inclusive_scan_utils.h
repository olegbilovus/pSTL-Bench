#pragma once

#include <numeric>

#include <benchmark/benchmark.h>

#include "pstl/utils/utils.h"

namespace benchmark_inclusive_scan
{
	template<class Policy, class Function>
	static void benchmark_wrapper(benchmark::State & state, Function && F)
	{
		constexpr auto execution_policy = Policy{};

		const auto & size = state.range(0);

		auto input = pstl::generate_increment(execution_policy, size);

		auto output = input;
		std::fill(output.begin(), output.end(), 0);

		std::inclusive_scan(std::execution::seq, input.begin(), input.end(), output.begin());

		const auto solution = output.back();

		for (auto _ : state)
		{
			pstl::wrap_timing(state, std::forward<Function>(F), execution_policy, input, output);

			assert(pstl::are_equivalent(output.back(), solution));
		}

		pstl::add_global_custom_statistics(state, input);
	}
} // namespace benchmark_inclusive_scan
