#pragma once

#include <cmath>

#include "pstl/utils/utils.h"
#include <benchmark/benchmark.h>

namespace benchmark_transform_inclusive_scan
{
	const auto kernel = [](const auto & input) {
		return input * input;
	};

	template<class Policy, class Function>
	static void benchmark_wrapper(benchmark::State & state, Function && f)
	{
		constexpr auto execution_policy = Policy{};

		const auto & size = state.range(0);

		auto input = pstl::generate_increment(execution_policy, size);

		auto output = input;
		std::fill(output.begin(), output.end(), 0);

		const auto solution = std::transform_inclusive_scan(std::execution::seq, input.begin(), input.end(),
		                                                    output.begin(), std::plus<>(), kernel);

		for (auto _ : state)
		{
			const auto result =
			    pstl::wrap_timing(state, std::forward<Function>(f), execution_policy, input, output, kernel);
			assert(pstl::are_equivalent(result, solution));
		}

		pstl::add_global_custom_statistics(state, input);
	}
} // namespace benchmark_transform_inclusive_scan
