#pragma once

#include <numeric>

#include <benchmark/benchmark.h>

#include "pstl/utils/utils.h"

namespace benchmark_partial_sort
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

			pstl::wrap_timing(state, std::forward<Function>(F), execution_policy, input.begin(), middle, input.end());

			assert((std::is_sorted(input.begin(), middle)));
		}

		state.SetBytesProcessed(pstl::computed_bytes(state, input));
	}
} // namespace benchmark_partial_sort
