#pragma once

#include <cassert>
#include <random>

#include <benchmark/benchmark.h>

#include "pstl/utils/utils.h"

namespace benchmark_any_of
{
	template<class Policy, class Function>
	static void benchmark_wrapper(benchmark::State & state, Function && F)
	{
		constexpr auto execution_policy = Policy{};

		const auto & size = state.range(0);

		auto input = pstl::generate_increment(execution_policy, size);

		static auto rd = std::random_device{};

		// Choose a random number between 1 and size
		static std::minstd_rand               engine{ rd() };
		std::uniform_int_distribution<size_t> gen(0, input.size() - 1);

		for (auto _ : state)
		{
			const auto index = gen(engine);
			const auto value = input[index];

			const auto output = pstl::wrap_timing(state, std::forward<Function>(F), execution_policy, input,
			                                      [=](const auto & val) { return val == value; });

			assert(pstl::are_equivalent(output, true));
		}

		pstl::add_global_custom_statistics(state, input);
	}

} // namespace benchmark_any_of
