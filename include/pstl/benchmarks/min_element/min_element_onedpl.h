#pragma once

#include <oneapi/dpl/algorithm>
#include <oneapi/dpl/execution>

namespace benchmark_min_element
{
	const auto min_element_onedpl = [](auto && policy, const auto & input) {
		return oneapi::dpl::min_element(oneapi::dpl::execution::dpcpp_default, input.begin(), input.end());
	};
} // namespace benchmark_min_element
