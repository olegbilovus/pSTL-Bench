#pragma once

#include <numeric>

#include <benchmark/benchmark.h>

#include "pstl/utils/utils.h"

namespace benchmark_copy_if
{
	const auto condition = [](const auto & value) {
		// Check if the value is even
		if constexpr (std::is_integral_v<decltype(value)>) { return value % 2 == 0; }
		else { return static_cast<int>(value) % 2 == 0; }
	};

	template<class Policy, class Function>
	static void benchmark_wrapper(benchmark::State & state, Function && F)
	{
		constexpr auto execution_policy = Policy{};

		const auto & size = state.range(0);

		const auto input = pstl::generate_increment(execution_policy, size);

		auto output = input;

		for (auto _ : state)
		{
			pstl::wrap_timing(state, std::forward<Function>(F), execution_policy, input, output, condition);
		}

		pstl::add_global_custom_statistics(state, input, output);
	}
} // namespace benchmark_copy_if
