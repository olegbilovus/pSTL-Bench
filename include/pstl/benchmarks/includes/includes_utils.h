#pragma once

#include <numeric>

#include <benchmark/benchmark.h>

#include "pstl/utils/utils.h"

namespace benchmark_includes
{
	template<class Policy, class Function>
	static void benchmark_wrapper(benchmark::State & state, Function && F)
	{
		constexpr auto execution_policy = Policy{};

		const auto & size = state.range(0);

		const auto input = pstl::generate_increment(execution_policy, size);

		const auto subset = pstl::generate_increment(execution_policy, size / 2, static_cast<pstl::elem_t>(size / 4),
		                                             static_cast<pstl::elem_t>(1));

		const auto solution = std::includes(input.begin(), input.end(), subset.begin(), subset.end());

		for (auto _ : state)
		{
			const auto output = pstl::wrap_timing(state, std::forward<Function>(F), execution_policy, input, subset);
			assert(pstl::are_equivalent(output, solution));
		}

		pstl::add_global_custom_statistics(state, input, subset);
	}
} // namespace benchmark_includes
