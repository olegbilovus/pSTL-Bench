#pragma once

#include <numeric>

#include <benchmark/benchmark.h>

#include "pstl/utils/utils.h"

namespace benchmark_set_intersection
{
	template<class Policy, class Function>
	static void benchmark_wrapper(benchmark::State & state, Function && F)
	{
		constexpr auto execution_policy = Policy{};

		const auto & size = state.range(0);

		auto data1 = pstl::generate_increment(execution_policy, size);
		auto data2 = pstl::generate_increment(execution_policy, size / 2, static_cast<pstl::elem_t>(size / 4),
		                                      static_cast<pstl::elem_t>(1));

		const auto max_size = std::min(data1.size(), data2.size());

		auto result = std::vector<pstl::elem_t>(max_size, std::numeric_limits<pstl::elem_t>::quiet_NaN());
		auto output = result;

		std::ignore = std::set_intersection(data1.begin(), data1.end(), data2.begin(), data2.end(), result.begin());
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
} // namespace benchmark_set_intersection
