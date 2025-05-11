#pragma once

#include <numeric>

#include <benchmark/benchmark.h>

#include "pstl/utils/utils.h"

namespace benchmark_set_difference
{
	template<class Policy, class Function>
	static void benchmark_wrapper(benchmark::State & state, Function && F)
	{
		constexpr auto execution_policy = Policy{};

		const auto & size = state.range(0);

		auto data1 = pstl::generate_increment(execution_policy, size);
		auto data2 = pstl::generate_increment(execution_policy, size / 2, static_cast<pstl::elem_t>(size / 4),
		                                      static_cast<pstl::elem_t>(1));

		auto result = std::vector<pstl::elem_t>(size - size / 2, std::numeric_limits<pstl::elem_t>::quiet_NaN());
		auto output = result;

		std::ignore = std::set_difference(data1.begin(), data1.end(), data2.begin(), data2.end(), result.begin());
		std::sort(result.begin(), result.end());

		for (auto _ : state)
		{
			pstl::wrap_timing(state, std::forward<Function>(F), execution_policy, data1, data2, output);

			std::sort(output.begin(), output.end());

			assert(std::equal(result.begin(), result.end(), output.begin(), output.end()));

			std::fill(output.begin(), output.end(), std::numeric_limits<pstl::elem_t>::quiet_NaN());
		}

		pstl::add_global_custom_statistics(state, data1, data2);
	}
} // namespace benchmark_set_difference
