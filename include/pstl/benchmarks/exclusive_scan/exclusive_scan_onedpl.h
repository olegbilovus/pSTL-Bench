#pragma once

#include <oneapi/dpl/algorithm>
#include <oneapi/dpl/execution>

namespace benchmark_exclusive_scan
{
	const auto exclusive_scan_onedpl = [](auto && policy, const auto & input, auto & output) {
		oneapi::dpl::exclusive_scan(oneapi::dpl::execution::dpcpp_default, input.begin(), input.end(), output.begin(),
		                            0);
	};
} // namespace benchmark_exclusive_scan
