
#pragma once

#include <cmath>

#include "pstl/utils/utils.h"
#include <benchmark/benchmark.h>

namespace benchmark_transform
{
	const auto kernel = [](const auto & input) {
		return std::min(std::sin(input), std::tan(input));
	};

	template<class Policy, class Function>
	static void benchmark_wrapper(benchmark::State & state, Function && f)
	{
		constexpr auto execution_policy = Policy{};

		const auto & size = state.range(0);

		auto input = pstl::generate_increment(execution_policy, size);

		for (auto _ : state)
		{
			pstl::wrap_timing(state, std::forward<Function>(f), execution_policy, input, kernel);
		}

		pstl::add_global_custom_statistics(state, input);
	}
} // namespace benchmark_transform
