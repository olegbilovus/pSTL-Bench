#pragma once

#include <benchmark/benchmark.h>

#include "pstl/utils/utils.h"

namespace benchmark_sort
{
	template<class Policy, class Function>
	static void benchmark_wrapper(benchmark::State & state, Function && f)
	{
		constexpr auto execution_policy = Policy{};

		const auto & size = state.range(0);

		auto input = pstl::generate_increment(execution_policy, size);

		static std::random_device rd;
		static std::mt19937       generator(rd());

		for (auto _ : state)
		{
			std::shuffle(input.begin(), input.end(), generator);

			pstl::wrap_timing(state, std::forward<Function>(f), execution_policy, input);

			assert(std::is_sorted(input.begin(), input.end()));
		}

		pstl::add_global_custom_statistics(state, input);
	}
} // namespace benchmark_sort
