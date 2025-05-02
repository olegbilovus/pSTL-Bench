#pragma once

#include <oneapi/dpl/algorithm>
#include <oneapi/dpl/execution>

namespace benchmark_is_sorted
{
	const auto is_sorted_onedpl = [](auto && policy, const auto & input) {
		return oneapi::dpl::is_sorted(oneapi::dpl::execution::dpcpp_default, input.begin(), input.end());
	};
} // namespace benchmark_is_sorted
