#pragma once

#include <oneapi/dpl/algorithm>
#include <oneapi/dpl/execution>

namespace benchmark_count
{
	const auto count_onedpl = [](auto && policy, const auto & input, const auto & value) {
		return oneapi::dpl::count(oneapi::dpl::execution::dpcpp_default, input.begin(), input.end(), value);
	};
} // namespace benchmark_count
