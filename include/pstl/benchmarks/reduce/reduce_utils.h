#pragma once

#include <benchmark/benchmark.h>

#include "pstl/utils/utils.h"

namespace benchmark_reduce
{
	template<class Policy, class Function>
	static void benchmark_wrapper(benchmark::State & state, Function && F)
	{
		constexpr auto execution_policy = Policy{};

		const auto & size = state.range(0);

		auto input = pstl::generate_increment(execution_policy, size);

		const auto solution = std::accumulate(input.begin(), input.end(), pstl::elem_t{});

		for (auto _ : state)
		{
			const auto output = pstl::wrap_timing(state, std::forward<Function>(F), execution_policy, input);

			assert(pstl::are_equivalent(output, solution));
		}

		pstl::add_global_custom_statistics(state, input);
	}
} // namespace benchmark_reduce
