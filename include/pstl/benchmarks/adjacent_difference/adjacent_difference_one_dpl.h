#pragma once

#include <oneapi/dpl/algorithm>
#include <oneapi/dpl/execution>

namespace benchmark_adjacent_difference
{
	const auto adjacent_difference_one_dpl = [](auto & policy, const auto & input, auto & output) {
		oneapi::dpl::adjacent_difference(oneapi::dpl::execution::dpcpp_default, input.begin(), input.end(),
		                                 output.begin());
	};
} // namespace benchmark_adjacent_difference
