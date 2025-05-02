
#pragma once

#include <vector>

#include <oneapi/dpl/algorithm>
#include <oneapi/dpl/execution>

namespace benchmark_find
{
	const auto find_onedpl = [](auto && policy, const auto & input, const auto & find_val) {
		return oneapi::dpl::find(oneapi::dpl::execution::dpcpp_default, input.begin(), input.end(), find_val);
	};
} // namespace benchmark_find
