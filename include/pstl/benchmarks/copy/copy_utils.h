#pragma once

#include <numeric>

#include <benchmark/benchmark.h>

#include "pstl/utils/utils.h"

namespace benchmark_copy
{
	template<class Policy, class Function>
	static void benchmark_wrapper(benchmark::State & state, Function && F)
	{
		constexpr auto execution_policy = Policy{};

		const auto & size = state.range(0);

		const auto input = pstl::generate_increment(execution_policy, size);

		auto output = input;

		for (auto _ : state)
		{
			pstl::wrap_timing(state, std::forward<Function>(F), execution_policy, input, output);
		}

		state.SetBytesProcessed(pstl::computed_bytes(state, input, output));
	}
} // namespace benchmark_copy


