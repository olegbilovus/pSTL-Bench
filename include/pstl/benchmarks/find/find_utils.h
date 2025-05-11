#pragma once

#include <cassert>
#include <random>

#include <benchmark/benchmark.h>

#include "pstl/utils/utils.h"

namespace benchmark_find
{
	template<class Policy, class Function>
	static void benchmark_wrapper(benchmark::State & state, Function && F)
	{
		constexpr auto execution_policy = Policy{};

		const auto & size = state.range(0);

		// vector with values [0,size)
		auto input = pstl::generate_increment(execution_policy, size);

		// Seed with a fixed value for reproducibility
		const auto seed = 42;

		// Choose a random number between 1 and size
		std::minstd_rand engine(seed);

		// Random number generator
		std::uniform_int_distribution<size_t> gen(0, size - 1);

		const auto get_value = [&]() {
			const auto index = gen(engine);
			return input[index];
		};

		for (auto _ : state)
		{
			// random value in [0,size)
			const auto value = get_value();

			const auto output = pstl::wrap_timing(state, std::forward<Function>(F), execution_policy, input, value);

			// make sure the val is really found
			assert(output == std::find(input.begin(), input.end(), value));
		}

		pstl::add_global_custom_statistics(state, input);
	}
} // namespace benchmark_find
