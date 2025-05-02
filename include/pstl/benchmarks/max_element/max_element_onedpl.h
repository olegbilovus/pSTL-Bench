#pragma once

#include <oneapi/dpl/algorithm>
#include <oneapi/dpl/execution>

namespace benchmark_max_element
{
	const auto max_element_onedpl = [](auto && policy, const auto & input) {
		return oneapi::dpl::max_element(oneapi::dpl::execution::dpcpp_default, input.begin(), input.end());
	};
} // namespace benchmark_max_element
