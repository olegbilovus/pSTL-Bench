#pragma once

#include <oneapi/dpl/algorithm>
#include <oneapi/dpl/execution>

namespace benchmark_adjacent_find
{
	const auto adjacent_find_onedpl = [](auto && policy, const auto & input) {
		return oneapi::dpl::adjacent_find(oneapi::dpl::execution::dpcpp_default, input.begin(), input.end());
	};
} // namespace benchmark_adjacent_find
