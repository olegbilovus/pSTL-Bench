#pragma once

#include <numeric>

#include <benchmark/benchmark.h>

#include "pstl/utils/utils.h"

namespace benchmark_min_element
{
	template<class Policy, class Function>
	static void benchmark_wrapper(benchmark::State & state, Function && F)
	{
		constexpr auto execution_policy = Policy{};

		const auto & size = state.range(0);

		auto input = pstl::generate_increment(execution_policy, size);
		std::shuffle(input.begin(), input.end(), std::mt19937{ std::random_device{}() });

		const auto solution = std::min_element(input.begin(), input.end());

		for (auto _ : state)
		{
			const auto output = pstl::wrap_timing(state, std::forward<Function>(F), execution_policy, input);

			assert(pstl::are_equivalent(solution, output));
		}

		pstl::add_global_custom_statistics(state, input);
	}
} // namespace benchmark_min_element
