#pragma once

#include <numeric>

#include <benchmark/benchmark.h>

#include "pstl/utils/utils.h"

namespace benchmark_inplace_merge
{
	template<class Policy, class Function>
	static void benchmark_wrapper(benchmark::State & state, Function && F)
	{
		constexpr auto execution_policy = Policy{};

		const auto & size = state.range(0);

		auto input = pstl::generate_increment(execution_policy, size);

		for (auto _ : state)
		{
			std::shuffle(input.begin(), input.end(), std::mt19937{ std::random_device{}() });

			auto middle = input.begin() + (input.size() / 2);

			std::sort(input.begin(), middle);
			std::sort(middle, input.end());

			pstl::wrap_timing(state, std::forward<Function>(F), execution_policy, input.begin(), middle, input.end());

			assert((std::is_sorted(input.begin(), input.end())));
		}

		pstl::add_global_custom_statistics(state, input);
	}
} // namespace benchmark_inplace_merge
