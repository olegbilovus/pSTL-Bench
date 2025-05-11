
#pragma once

#include <cmath>

#include "pstl/utils/utils.h"
#include <benchmark/benchmark.h>

namespace benchmark_for_each
{
#ifndef PSTL_BENCH_DEFAULT_FOR_EACH_KERNEL_ITS
#define PSTL_BENCH_DEFAULT_FOR_EACH_KERNEL_ITS 1
#endif

	const auto kernel = [](auto & input, const auto Its) {
		volatile size_t I = Its;

		pstl::elem_t a{};

		for (auto i = 0; i < I; ++i)
		{
			a++;
		}

		input = a;
	};

	template<class Policy, class Function>
	static void benchmark_for_each_wrapper(benchmark::State & state, Function && f)
	{
		constexpr auto execution_policy = Policy{};

		const auto & size = state.range(0);

		auto data = pstl::generate_increment(execution_policy, size);

		// Read environment variable PSTL_FOR_EACH_KERNEL_ITS
		std::size_t its = PSTL_BENCH_DEFAULT_FOR_EACH_KERNEL_ITS;

		const char * env_p = std::getenv("PSTL_BENCH_FOR_EACH_KERNEL_ITS");
		if (env_p) { its = std::strtoul(env_p, nullptr, 10); }

		for (auto _ : state)
		{
			pstl::wrap_timing(state, std::forward<Function>(f), execution_policy, data,
			                  [=](auto & elem) { kernel(elem, its); });
		}

		pstl::add_global_custom_statistics(state, data);

		state.counters["kernel_its"] = static_cast<double>(its);
	}
} // namespace benchmark_for_each
