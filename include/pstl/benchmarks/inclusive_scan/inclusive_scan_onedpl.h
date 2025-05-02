#pragma once

#include <oneapi/dpl/algorithm>
#include <oneapi/dpl/execution>

namespace benchmark_inclusive_scan
{
	const auto inclusive_onedpl = [](auto && policy, const auto & input, auto & output) {
		oneapi::dpl::inclusive_scan(oneapi::dpl::execution::dpcpp_default, input.begin(), input.end(), output.begin());
	};
} // namespace benchmark_inclusive_scan
