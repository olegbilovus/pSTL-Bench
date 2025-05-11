#pragma once

#include <numeric>

#include <benchmark/benchmark.h>

#include "pstl/utils/utils.h"

namespace benchmark_all_of
{
	template<class Policy, class Function>
	static void benchmark_wrapper(benchmark::State & state, Function && F)
	{
		constexpr auto execution_policy = Policy{};

		const auto & size = state.range(0);

		auto input = pstl::generate_increment(execution_policy, size);

		const auto condition = [](const auto & val) {
			return val > 0;
		};

		const auto solution = std::all_of(input.begin(), input.end(), condition);

		for (auto _ : state)
		{
			const auto output = pstl::wrap_timing(state, std::forward<Function>(F), execution_policy, input, condition);

			assert(pstl::are_equivalent(output, solution));
		}

		pstl::add_global_custom_statistics(state, input);
	}
} // namespace benchmark_all_of
