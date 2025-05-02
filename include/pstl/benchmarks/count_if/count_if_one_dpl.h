#pragma once

#include <oneapi/dpl/algorithm>
#include <oneapi/dpl/execution>

#include <benchmark/benchmark.h>

namespace benchmark_count_if
{
	const auto count_if_one_dpl = [](auto && policy, const auto & input, auto & condition) {
		return oneapi::dpl::count_if(oneapi::dpl::execution::dpcpp_default, input.begin(), input.end(), condition);
	};
} // namespace benchmark_count_if
